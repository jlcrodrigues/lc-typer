#include <lcom/lcf.h>

#include <lcom/lab3.h>
//#include <lcom/lab2.h>

#include "keyboard.h"

#include <stdbool.h>
#include <stdint.h>
#include <minix/syslib.h>

extern uint8_t buff;
extern uint8_t size;
extern uint8_t bytes[];
extern int read_error;
extern bool complete;

extern uint32_t count_interrupts;

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
  uint8_t keyboard = 0;
  message msg;

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

  kbd_print_no_sysinb(cnt);

  return 0;
}

int(kbd_test_poll)() {
  while (buff != BREAKCODE_ESC) {
    kbc_ih();

    if (complete && !read_error) {
      bool make = !(buff & MSB);

      kbd_print_scancode(make, size, bytes);
    }
  }

  kbd_print_no_sysinb(cnt);

  uint8_t kbc = 0;
  sys_outb(KEYBOARD_STATUS, READ_COMMAND_BYTE);
  util_sys_inb(KEYBOARD_OUT_BUFF, &kbc);

  kbc |= INTERRUPT_KEYBOARD_OBF;

  sys_outb(KEYBOARD_STATUS, WRITE_COMMAND_BYTE);
  sys_outb(KEYBOARD_OUT_BUFF, kbc);

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  const int freq = 60;
  int ipc_status, r;
  message msg;
  uint8_t time = n;
  uint8_t timer = 0;
  uint8_t keyboard = 0;
  count_interrupts = 0;

  if (timer_set_frequency(0, freq)) return 1;
  if (timer_subscribe_int(&timer)) return 1;
  if (keyboard_subscribe_int(&keyboard)) return 1;
  int irq_set_timer = BIT(timer);
  int irq_set_keyboard = BIT(keyboard);

  while (buff != BREAKCODE_ESC && time > 0) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if (!(count_interrupts % freq)) {
              //timer_print_elapsed_time();
              time--;
              //printf("%d", time);
            }
          }
          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();

            if (complete) {
              bool make = !(buff & MSB);

              kbd_print_scancode(make, size, bytes);
              time = n;
              count_interrupts = 0;
              //printf("time%d", time);
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
  if (timer_unsubscribe_int()) return 1;

  //kbd_print_no_sysinb(cnt);

  return 0;
}
