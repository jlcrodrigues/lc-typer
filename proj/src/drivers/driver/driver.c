#include "driver.h"

static int ipc_status = 0, r;
static int irq_keyboard;
static int irq_timer;

extern int read_ok;

int(subscribe_interrupts)() {
  uint8_t bit_no = 0;
  if (keyboard_subscribe_int(&bit_no)) {
    printf("Unable to subscribe to keyboard interrupts.\n");
    return 1;
  }
  irq_keyboard = BIT(bit_no);

  if (timer_subscribe_int(&bit_no)) {
    printf("Unable to subscribe to timer interrupts.\n");
    return 1;
  }
  irq_timer = BIT(bit_no);

  return 0;
}

int(unsubscribe_interrupts)() {
  if (keyboard_unsubscribe_int()) {
    printf("Unable to subscribe keyboard interrupts.\n");
    return 1;
  }
  if (timer_unsubscribe_int()) {
    printf("Unable to subscribe timer interrupts.\n");
    return 1;
  }
  return 0;
}

LoopState(interrupt_handler)() {
  message msg;

  /* Get a request message. */
  if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
    printf("driver_receive failed with: %d", r);
    return CONTINUE;
  }
  if (is_ipc_notify(ipc_status)) { /* received notification */
    switch (_ENDPOINT_P(msg.m_source)) {
      case HARDWARE:                                  /* hardware interrupt notification */
        if (msg.m_notify.interrupts & irq_keyboard) { /* subscribed interrupt */
          kbc_ih();
          if (read_ok) return OVER;
        }
        break;
      default:
        break; /* no other notifications expected: do nothing */
    }
  }
  else { /* received a standard message, not a notification */
         /* no standard messages expected: do nothing */
  }
  return CONTINUE;
}
