/*
 note

 maple mini uses PB9 to control USB-DP+ pull up.

 if you set PB9 to low, DP+ gets pulled up and USB is detected.
 if you set PB9 to high, DP+ gets pulled down and USB is disconnected.

 maple mini has single led which is connected to PB1

 PA1 is used o force bootloader mode

 -hkim-
*/

#include <string.h>
#include <libopencm3/cm3/systick.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/scb.h>

#include "usbdfu.h"

#define RCC_USB_DP_PULLDOWN         RCC_GPIOB
#define USB_DP_PULLDOWN_PORT        GPIOB
#define USB_DP_PULLDOWN_PIN         GPIO9

uint32_t app_address = 0x08002000;

void dfu_detach(void)
{
#if 0
  /* Disconnect USB cable by resetting USB Device and pulling USB_DP low*/
  rcc_periph_reset_pulse(RST_USB);
  rcc_periph_clock_enable(RCC_USB);
  rcc_periph_clock_enable(RCC_USB_DP_PULLDOWN);

  gpio_set(USB_DP_PULLDOWN_PORT, USB_DP_PULLDOWN_PIN);
  gpio_set_mode(USB_DP_PULLDOWN_PORT, GPIO_MODE_OUTPUT_2_MHZ,
      GPIO_CNF_OUTPUT_OPENDRAIN, USB_DP_PULLDOWN_PIN);
#endif
  scb_reset_system();
}

int main(void)
{
  /* Check the force bootloader pin*/
  rcc_periph_clock_enable(RCC_GPIOA);

  if(!gpio_get(GPIOA, GPIO1))
    dfu_jump_app_if_valid();

  dfu_protect(DFU_MODE);

  rcc_clock_setup_in_hse_8mhz_out_72mhz();
  systick_set_clocksource(STK_CSR_CLKSOURCE_AHB_DIV8);
  systick_set_reload(900000);

  /* Handle USB disconnect/connect */
  /* Just in case: Disconnect USB cable by resetting USB Device
   * and pulling USB_DP low
   * Device will reconnect automatically as Pull-Up is hard wired*/
  rcc_periph_reset_pulse(RST_USB);
  rcc_periph_clock_enable(RCC_USB);
  rcc_periph_clock_enable(RCC_USB_DP_PULLDOWN);
  gpio_clear(USB_DP_PULLDOWN_PORT, USB_DP_PULLDOWN_PIN);
  gpio_set_mode(USB_DP_PULLDOWN_PORT, GPIO_MODE_OUTPUT_2_MHZ,
      GPIO_CNF_OUTPUT_OPENDRAIN, USB_DP_PULLDOWN_PIN);

  // forf led
  gpio_set_mode(GPIOB, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);

  systick_interrupt_enable();
  systick_counter_enable();

  dfu_init(&st_usbfs_v1_usb_driver, DFU_MODE);

  dfu_main();
}

void dfu_event(void)
{
}

void sys_tick_handler(void)
{
  gpio_toggle(GPIOB, GPIO1);
}
