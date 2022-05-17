#include "mouse.h"

static int hook_mouse = 0;
static uint8_t buff = 0;
static int packets_count = 0;
uint8_t packets[PACKET_NUMBER];
bool mouse_read_ok = 0;

int (mouse_subscribe_int)(uint8_t *bit_no) {
  hook_mouse = MOUSE_IRQ;
  *bit_no = MOUSE_IRQ;
  return sys_irqsetpolicy(
    MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_mouse);
}

int (mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&hook_mouse);
}

int (mouse_disable_data_reporting)() {
  //uint8_t minix_kbc	= minix_get_dflt_kbc_cmd_byte();
  //if (send_mouse_cmd(MOUSE_WRITE_COMMAND_BYTE)) return 1;
  //if (send_mouse_cmd(DISABLE_DATA_REPORTING)) return 1;
  if (send_mouse_cmd(DISABLE_DATA_REPORTING)) return 1;
  return 0;
}

void (mouse_ih)() {
  uint8_t value = 0;
  mouse_read_ok = 0;
  util_sys_inb(KEYBOARD_STATUS, &value);

  if ((value & MOUSE_READ_MASK) == MOUSE_READ_MASK) {
    util_sys_inb(KEYBOARD_OUT_BUFF, &buff);
    packets[packets_count] = buff;
    packets_count++;
  }

  if (packets_count == 3) {
    packets_count = 0;
    mouse_read_ok = 1;
  }
}

struct packet (parse_packets)() {
  struct packet p;
  memcpy(p.bytes, packets, PACKET_NUMBER);
  p.rb = packets[0] & RIGHT_BYTE;
  p.lb = packets[0] & LEFT_BYTE;
  p.mb = packets[0] & MIDDLE_BYTE;
  p.delta_x = packets[1];
  if (packets[0] & SIGN_X){
      p.delta_x |= COMPLETE_SIGNAL;
  }
  p.delta_y = packets[2];
  if (packets[0] & SIGN_Y){
      p.delta_y |= COMPLETE_SIGNAL;
  }
  p.x_ov = packets[0] & OVFL_X;
  p.y_ov = packets[0] & OVFL_Y;
  return p;
}

int (send_mouse_cmd)(uint32_t cmd) {
  uint8_t st = 0, ack = 0;
  for (int i = 0; i < 10; i++) {
      if (util_sys_inb(KEYBOARD_STATUS, &st)) return 1;
      if ((st & KEYBOARD_INB) == 0) {
        if (sys_outb(KEYBOARD_STATUS, MOUSE_WRITE_COMMAND_BYTE)) return 1;
      }
      if (util_sys_inb(KEYBOARD_STATUS, &st)) return 1;
      if ((st & KEYBOARD_INB) == 0) {
        if (sys_outb(WRITE_COMMAND_BYTE, cmd)) return 1;
      }
      if (mouse_read(&ack)) return 1;
      if (ack == ACK_SUCCESS) return 0;
      tickdelay(20);
  }
  return 1;
}

int (mouse_read)(uint8_t *byte) {
  uint8_t st = 0;
  if(util_sys_inb(KEYBOARD_STATUS, &st)) return 1;
  if((st & BUFFER_FULL) && (st & AUX)) {
      if (st & (KEYBOARD_PARITY | KEYBOARD_TIMEOUT)) return 1;
      if (util_sys_inb(KEYBOARD_OUT_BUFF, byte)) return 1;
      else return 0;
  }
  tickdelay(20);
  return 1;
}
