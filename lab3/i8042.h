#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

#define KEYBOARD_OUT_BUFF 0x60
#define KEYBOARD_STATUS 0x64

#define KEYBOARD_IRQ 1

#define BREAKCODE_ESC 0x81
#define FIRST_BYTE 0xE0

#define MSB BIT(7)

#define KEYBOARD_PARITY BIT(7)
#define KEYBOARD_TIMEOUT BIT(6)



#endif
