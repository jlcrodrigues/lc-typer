#include <lcom/lcf.h>
#include "i8042.h"

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (mouse_disable_data_reporting)();

struct packet (parse_packets)();

int (send_mouse_cmd)(uint32_t cmd);

int (mouse_read)(uint8_t *byte);
