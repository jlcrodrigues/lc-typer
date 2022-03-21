#include <lcom/lcf.h>

#include <stdint.h>

#include <minix/syslib.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if (value == NULL) return -1;
  uint32_t value_32 = 0;
  int res = sys_inb(port, &value_32);
  if (res != 0) return res;
  *value = value_32;
  return 0;
}
