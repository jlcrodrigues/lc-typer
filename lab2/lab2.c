#include <lcom/lcf.h>
#include <lcom/lab2.h>

#include <stdbool.h>
#include <stdint.h>


extern uint32_t count_interrupts;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab2/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab2/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(timer_test_read_config)(uint8_t timer, enum timer_status_field field) {
  uint8_t conf = 0;
  if(timer_get_conf(timer, &conf)) return 1;

  if(timer_display_conf(timer, conf, field)) return 1;

  return 0;
}

int(timer_test_time_base)(uint8_t timer, uint32_t freq) {
  return timer_set_frequency(timer, freq);
}


int(timer_test_int)(uint8_t time) {
  const int freq = 60;
  int ipc_status, r;
  message msg;
  uint8_t timer = 0;
  count_interrupts = 0;
  if (timer_subscribe_int(&timer)) return 1;
  int irq_set = BIT(timer);
  while (time) {
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
      printf("driver_receive failed with %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & irq_set) {
            timer_int_handler();
            if (!(count_interrupts % freq)) {
              timer_print_elapsed_time();
              time--;
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
  return 0;
}
