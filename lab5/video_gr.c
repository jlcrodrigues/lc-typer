#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video.h"

static char *video_mem; /* Process (virtual) address to which VRAM is mapped */
static vbe_mode_info_t mode_info;

static unsigned h_res;          /* Horizontal resolution in pixels */
static unsigned v_res;          /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel;

int(map_memory)(vbe_mode_info_t mode_info) {
  struct minix_mem_range mr;
  int r;

  /* Use VBE function 0x01 to initialize vram_base and vram_size */
  unsigned int vram_base = mode_info.PhysBasePtr;
  unsigned int vram_size = ((bits_per_pixel + 8 - 1) / 8) * h_res * v_res;

  /* Allow memory mapping */

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);

  /* Map memory */

  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED)
    panic("couldn't map video memory");

  return 0;
}

void *(set_mode) (uint16_t mode) {
  reg86_t r86;
  /* Specify the appropriate register values */
  memset(&r86, 0, sizeof(r86)); /* zero the structure */

  r86.intno = 0x10; /* BIOS video services */
  r86.ah = 0x4F;    /* Set Video Mode function */
  r86.al = 0x02;    /* set video mode  */
  r86.bx = mode | BIT(14);

  /* Make the BIOS call */

  if (sys_int86(&r86) != OK) {
    printf("\tvg_init(): sys_int86() failed \n");
    video_mem = NULL;
  }
  return video_mem;
}

void *(vg_init) (uint16_t mode) {
  vbe_get_mode_info(mode, &mode_info);

  h_res = mode_info.XResolution;
  v_res = mode_info.YResolution;
  bits_per_pixel = mode_info.BitsPerPixel;
  bytes_per_pixel = bits_per_pixel / 8;
  if (map_memory(mode_info))
    return NULL;

  return set_mode(mode);
}

int(draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x >= h_res || y >= v_res) {
    return 1;
  }
  unsigned int pos = (x + y * h_res) * bytes_per_pixel;
  memcpy((void *) ((unsigned int) video_mem + pos), &color, bytes_per_pixel);
  video_mem[pos] = color;
  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (uint16_t i = 0; i < len; i++) {
    if (draw_pixel(x + i, y, color))
      return 1;
  }
  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width,
                       uint16_t height, uint32_t color) {
  for (uint16_t i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color))
      return 1;
  }
  return 0;
}

int(draw_pattern)(uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint16_t width = h_res / no_rectangles;
  uint16_t height = v_res / no_rectangles;

  uint32_t color = 0;

  for (uint8_t i = 0; i < no_rectangles; i++) {
    for (uint8_t j = 0; j < no_rectangles; j++) {
      if (bytes_per_pixel == 1) {
        color = (first + (i * no_rectangles + j) * step) % (1 << bits_per_pixel);
      }
      else {
        uint32_t red = ((RED(first) + j * step) % (1 << mode_info.RedMaskSize)) << 16;
        uint32_t green = ((GREEN(first) + i * step) % (1 << mode_info.GreenMaskSize)) << 8;
        uint32_t blue = (BLUE(first) + (j + i) * step) % (1 << mode_info.BlueMaskSize);
        color = red + green + blue;
      }

      vg_draw_rectangle(width * j, height * i, width, height, color);
    }
  }

  return 0;
}
