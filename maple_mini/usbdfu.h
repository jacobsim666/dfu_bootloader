#ifndef __USBDFU_H
#define __USBDFU_H

#include <libopencm3/usb/usbd.h>

/* Commands sent with wBlockNum == 0 as per ST implementation. */
#define CMD_SETADDR 0x21
#define CMD_ERASE 0x41

extern uint32_t app_address;

typedef enum {
    DFU_MODE = 0,
    UPD_MODE = 1
} dfu_mode_t;

/* dfucore.c - DFU core, common to libopencm3 platforms. */
void dfu_init(const usbd_driver *driver, dfu_mode_t mode);
void dfu_main(void);

/* Device specific functions */
void dfu_check_and_do_sector_erase(uint32_t sector);
void dfu_flash_program_buffer(uint32_t baseaddr, void *buf, int len);
uint32_t dfu_poll_timeout(uint8_t cmd, uint32_t addr, uint16_t blocknum);
void dfu_protect(dfu_mode_t mode);
void dfu_jump_app_if_valid(void);
void dfu_event(void);

/* Platform specific function */
void dfu_detach(void);

#endif /* __USBDFU_H */
