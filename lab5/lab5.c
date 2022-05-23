// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "keyboard.h"
#include "video.h"

extern uint8_t buff;
extern uint8_t size;
extern uint8_t bytes[];
extern int read_error;
extern bool complete;

extern int count_interrupts;

static int count_frames = 0;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {

  vg_init(mode);

  sleep(delay);

  vg_exit();
  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  int ipc_status, r;
  uint8_t keyboard = 0;
  message msg;
  vg_init(mode);
  vg_draw_rectangle(x, y, width, height, color);
  if (vg_refresh())
    return 1;

  if (keyboard_subscribe_int(&keyboard))
    return 1;
  int irq_set_keyboard = BIT(keyboard);

  while (buff != BREAKCODE_ESC) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();

            if (complete && !read_error) {
              bool make = !(buff & MSB);

              kbd_print_scancode(make, size, bytes);
            }
          }
          break;
        default:
          break;
      }
    }
    else {
    }
  }

  if (keyboard_unsubscribe_int())
    return 1;

  vg_exit();

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  int ipc_status, r;
  uint8_t keyboard = 0;
  message msg;
  vg_init(mode);
  if (draw_pattern(no_rectangles, first, step))
    return 1;
  if (vg_refresh())
    return 1;

  if (keyboard_subscribe_int(&keyboard))
    return 1;
  int irq_set_keyboard = BIT(keyboard);

  while (buff != BREAKCODE_ESC) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();

            if (complete && !read_error) {
              bool make = !(buff & MSB);

              kbd_print_scancode(make, size, bytes);
            }
          }
          break;
        default:
          break;
      }
    }
    else {
    }
  }

  if (keyboard_unsubscribe_int())
    return 1;

  vg_exit();

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  int ipc_status, r;
  uint8_t keyboard = 0;
  message msg;

  vg_init(0x105);

  if (draw_sprite(xpm, x, y)) {
    vg_exit();
    return 1;
  }
  if (vg_refresh())
    return 1;

  if (keyboard_subscribe_int(&keyboard))
    return 1;
  int irq_set_keyboard = BIT(keyboard);

  while (buff != BREAKCODE_ESC) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();

            if (complete && !read_error) {
              bool make = !(buff & MSB);

              kbd_print_scancode(make, size, bytes);
            }
          }
          break;
        default:
          break;
      }
    }
    else {
    }
  }

  if (keyboard_unsubscribe_int())
    return 1;

  vg_exit();

  return 0;
}

void(get_coords)(uint16_t* xi, uint16_t* yi, uint16_t* xf, uint16_t* yf,
                 int16_t speed) {
  if (*xi < *xf) {
    if (speed >= 0) {
      *xi += speed;
      if (*xi > *xf) *xi = *xf;
    }
    else {
      count_frames++;
      if (count_frames == 0 - speed) {
        *xi += 1;
        count_frames = 0;
      }
    }
  }
  if (*xi > *xf) {
    if (speed >= 0) {
      *xi -= speed;
      if (*xi < *xf) *xi = *xf;
    }
    else {
      count_frames++;
      if (count_frames == 0 - speed) {
        *xi -= 1;
        count_frames = 0;
      }
    }
  }
  if (*yi < *yf) {
    if (speed >= 0) {
      *yi += speed;
      if (*yi > *yf) *yi = *yf;
    }
    else {
      count_frames++;
      if (count_frames == 0 - speed) {
        *yi += 1;
        count_frames = 0;
      }
    }
  }
  if (*yi > *yf) {
    if (speed >= 0) {
      *yi -= speed;
      if (*yi < *yf) *yi = *yf;
    }
    else {
      count_frames++;
      if (count_frames == 0 - speed) {
        *yi -= 1;
        count_frames = 0;
      }
    }
  }
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  const int freq = fr_rate;
  int ipc_status, r;
  message msg;
  uint8_t timer = 0;
  uint8_t keyboard = 0;

  vg_init(0x105);
  if (draw_sprite(xpm, xi, yi)) {
    vg_exit();
    return 1;
  };
  if (vg_refresh())
    return 1;

  if (timer_set_frequency(0, freq))
    return 1;
  if (timer_subscribe_int(&timer))
    return 1;
  if (keyboard_subscribe_int(&keyboard))
    return 1;
  int irq_set_timer = BIT(timer);
  int irq_set_keyboard = BIT(keyboard);

  while (buff != BREAKCODE_ESC) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) {
            clear_screen();
            get_coords(&xi, &yi, &xf, &yf, speed);
            draw_sprite(xpm, xi, yi);
            if (vg_refresh())
              return 1;
          }
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();
          }

          break;
        default:
          break;
      }
    }
    else {
    }
  }

  if (keyboard_unsubscribe_int()) {
    vg_exit();
    return 1;
  }
  if (timer_unsubscribe_int()) {
    vg_exit();
    return 1;
  }
  vg_exit();
  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
