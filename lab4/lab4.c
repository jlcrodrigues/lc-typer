// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"

extern uint32_t count_interrupts;
extern bool mouse_read_ok;

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int (mouse_test_packet)(uint32_t cnt) {
  int ipc_status, r;
  message msg;
  uint8_t mouse = 0;
  if (mouse_subscribe_int(&mouse)) return 1;
  if (mouse_enable_data_reporting()) return 1;
  int irq_set = BIT(mouse);
  while (cnt) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            mouse_ih();
            if (mouse_read_ok) {
              cnt--;
              struct packet pp = parse_packets();
              mouse_print_packet(&pp);
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
  if (mouse_unsubscribe_int()) return 1;
  if (mouse_disable_data_reporting()) return 1;
  return 0;
}

int (mouse_test_async)(uint8_t idle_time) {
  const int freq = sys_hz();
  int ipc_status, r;
  message msg;
  uint8_t timer = 0, mouse = 0, time = idle_time;
  count_interrupts = 0;
  if (timer_subscribe_int(&timer)) return 1;
  if (mouse_subscribe_int(&mouse)) return 1;
  if (mouse_enable_data_reporting()) return 1;
  int irq_set_timer = BIT(timer);
  int irq_set_mouse = BIT(mouse);
  while (time) {
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
              time--;
            }
          }
          if (msg.m_notify.interrupts & irq_set_mouse) {
            mouse_ih();
            if (mouse_read_ok) {
              time = idle_time;
              count_interrupts = 0;
              struct packet pp = parse_packets();
              mouse_print_packet(&pp);
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
  if (timer_unsubscribe_int()) return 1;
  if (mouse_disable_data_reporting()) return 1;
  if (mouse_unsubscribe_int()) return 1;
  return 0;
}

int (mouse_test_gesture)(uint8_t x_len, uint8_t tolerance) {
    /* To be completed */
    printf("%s: under construction\n", __func__);
    return 1;
}

int (mouse_test_remote)(uint16_t period, uint8_t cnt) {
    /* This year you need not implement this. */
    printf("%s(%u, %u): under construction\n", __func__, period, cnt);
    return 1;
}
