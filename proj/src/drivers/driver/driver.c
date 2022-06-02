#include "driver.h"

static int ipc_status = 0, r;
static int irq_keyboard;
static int irq_timer;
static int irq_mouse;

extern int read_ok;

/** @brief Last event generated. */
static Event event;

int(subscribe_interrupts)() {
  if (mouse_set_data_reporting(1)) {
    printf("Unable to enable mouse data reporting.\n");
    return 1;
  }

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

  if (mouse_subscribe_int(&bit_no)) {
    printf("Unable to subscribe to mouse interrupts.\n");
    return 1;
  }
  irq_mouse = BIT(bit_no);

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
  if (mouse_unsubscribe_int()) {
    printf("Unable to subscribe mouse interrupts.\n");
    return 1;
  }
  if (mouse_set_data_reporting(0)) {
    printf("Unable to disable mouse data reporting.\n");
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
          if (keyboard_is_complete()) {
            event = keyboard_get_event();
            return EVENT;
          }
        }
        if (msg.m_notify.interrupts & irq_mouse) {
          mouse_ih();
          if (get_packets_count() == 3) {
            event = mouse_get_event();
            return EVENT;
          }
        }
        if (msg.m_notify.interrupts & irq_timer) { /* subscribed interrupt */
          timer_ih();
          event = timer_get_event();
          return EVENT;
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

Event get_event() {
  Event temp = event;
  event.type = BLANK;
  return temp;
}
