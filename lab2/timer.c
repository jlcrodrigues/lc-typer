#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include <minix/syslib.h>

#include "i8254.h"

int(timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(timer_subscribe_int)(uint8_t *bit_no) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void(timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int(timer_get_conf)(uint8_t timer, uint8_t *st) {
  if (st == NULL)
    return 1;
  uint32_t word = (TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ | TIMER_RB_CMD);
  if (sys_outb(TIMER_CTRL, word))
    return 1;
  int read_port;
  switch(timer) {
      case 0: read_port = TIMER_0; break;
      case 1: read_port = TIMER_1; break;
      case 2: read_port = TIMER_2; break;
      default: return 1;
  }
  return util_sys_inb(read_port, st);
}

int(timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  uint8_t in_mode;
  union timer_status_field_val conf;
  switch (field) {
    case tsf_all:
      conf.byte = st;
      break;
    case tsf_initial:
      in_mode = (st & MASK_INITIAL) >> 4;
      switch (in_mode) {
        case 0: conf.in_mode = INVAL_val; break;
        case 1: conf.in_mode = LSB_only; break;
        case 2: conf.in_mode = MSB_only; break;
        case 3: conf.in_mode = MSB_after_LSB; break;
        default: return 1;
      }
      break;
    case tsf_mode:
      conf.count_mode = (st & MASK_MODE) >> 1;
      if (conf.count_mode == 0x6 || conf.count_mode == 0x7)
        conf.count_mode &= 0x03;
      break;
    case tsf_base:
      conf.count_mode = st & 1;
      break;
  }
  if (timer_print_config(timer, field, conf))
    return 1;

  return 0;
}
