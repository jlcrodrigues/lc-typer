#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include <minix/syslib.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (timer_unsubscribe_int)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

void (timer_int_handler)() {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint32_t word = (TIMER_RB_SEL(timer) | BIT(5) | TIMER_RB_CMD);
  sys_outb(TIMER_CTRL, word);
  //if (out != 0) return out;
  return util_sys_inb(TIMER_CTRL, st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
                      
  /*timer_print_config(timer, field, 
    timer_status_field_val(
      st,
      timer_init(

      )
    )
  )
  */

  return 1;
}
