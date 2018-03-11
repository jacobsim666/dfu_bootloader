#ifndef __PLATFORM_H
#define __PLATFORM_H

#include "version.h"

#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/f1/memorymap.h>
#include <libopencm3/usb/usbd.h>

#define BOARD_IDENT       "Maple Mini (Firmware " FIRMWARE_VERSION ")"
#define BOARD_IDENT_DFU   "Maple Mini (Upgrade) (Firmware " FIRMWARE_VERSION ")"
#define BOARD_IDENT_UPD   "Maple Mini (DFU Upgrade) (Firmware " FIRMWARE_VERSION ")"
#define DFU_IDENT         "Maple Mini Firmware Upgrade"
#define DFU_IFACE_STRING  "@Internal Flash   /0x08000000/8*001Ka,56*001Kg"
#define UPD_IFACE_STRING  "@Internal Flash   /0x08000000/8*001Kg"

#define DEBUG(...)

extern uint16_t led_idle_run;

/* Use newlib provided integer only stdio functions */
#define sscanf siscanf
#define sprintf siprintf
#define vasprintf vasiprintf
#define snprintf sniprintf

#endif

