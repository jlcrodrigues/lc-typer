#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include "keyboard.h"

#include <stdbool.h>
#include <stdint.h>

extern uint8_t buff;
extern uint8_t size;
extern uint8_t bytes[];
extern int read_error;
extern bool complete;

uint32_t cnt = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  int ipc_status, r;
  message msg;

  if (keyboard_subscribe_int()) return 1;

  while (buff != BREAKCODE_ESC) {

    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & KEYBOARD_IRQ) {
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

  if (keyboard_unsubscribe_int()) return 1;

  kbd_print_no_sysinb(cnt);

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
