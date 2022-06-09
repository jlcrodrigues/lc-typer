#include "rtc.h"

static int hook_rtc = 0;
static uint8_t day, month, year;

int rtc_subscribe_int(uint8_t *bit_no) {
  hook_rtc = RTC_IRQ;
  *bit_no = RTC_IRQ;
  return sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &hook_rtc);
}

int rtc_unsubscribe_int() {
  return sys_irqrmpolicy(&hook_rtc);
}

int rtc_init() {
  uint8_t reg_b = 0;
  if (rtc_read_register(0xB, &reg_b)) return 1;
  reg_b |= UIE;
  if (rtc_write_register(0xB, reg_b)) return 1;
  rtc_read_data_reg();
  return 0;
}

void rtc_ih() {
  uint8_t reg = 0;
  do {
    if (rtc_read_register(0xA, &reg)) return;
  } while(reg & UIP);
  if (rtc_read_register(0xC, &reg)) return;
  if (!(reg & IRQF)) return;
  if (reg & UF) { // update
    if (rtc_read_data_reg()) return;
  }
}

int rtc_read_data_reg(void) {
  if (rtc_read_register(DAY_REG, &day)) return 0;
  if (rtc_read_register(MONTH_REG, &month)) return 0;
  if (rtc_read_register(YEAR_REG, &year)) return 0;
  return 0;
}

char* rtc_get_date_str(void) {
  char* date = malloc(DATE_STR_SIZE * sizeof(char));
  sprintf(date, "%02x/%02x/%02x", day, month, year);
  return date;
}

int (rtc_read_register)(uint8_t reg, uint8_t* byte) {
  if (sys_outb(RTC_ADDR_REG, reg)) return 1;
  if (util_sys_inb(RTC_DATA_REG, byte)) return 1;
  return 0;
}

int (rtc_write_register)(uint8_t reg, uint8_t byte) {
  if (sys_outb(RTC_ADDR_REG, reg)) return 1;
  if (sys_outb(RTC_DATA_REG, byte)) return 1;
  return 0;
}
