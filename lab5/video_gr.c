#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

static char *video_mem; /* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;          /* Horizontal resolution in pixels */
static unsigned v_res;          /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

int (map_memory)(vbe_mode_info_t mode_info) {
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
  printf("dd");

  if (video_mem == MAP_FAILED)
    panic("couldn't map video memory");
  
  return 0;
}

void *(vg_init) (uint16_t mode) {
  printf("hello");
  reg86_t r86;

  vbe_mode_info_t mode_info;
  vbe_get_mode_info(mode, &mode_info);

  h_res = mode_info.XResolution;
  v_res = mode_info.YResolution;
  bits_per_pixel = mode_info.BitsPerPixel;
  if (map_memory(mode_info))
    return NULL;

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
