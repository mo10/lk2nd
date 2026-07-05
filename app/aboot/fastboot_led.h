#ifndef __APP_FASTBOOT_LED_H
#define __APP_FASTBOOT_LED_H

#include <sys/types.h>

#if FASTBOOT_LED

#define FASTBOOT_LED_CONFIG_STAY 1, 0, 1 // Magenta
#define FASTBOOT_LED_CONFIG_BOOT 1, 1, 0 // Yellow

#define FASTBOOT_LED_RED_MPP_BASE PM8x41_MMP2_BASE
#define FASTBOOT_LED_GREEN_MPP_BASE PM8x41_MMP4_BASE
#define FASTBOOT_LED_BLUE_MPP_BASE PM8x41_MMP6_BASE

#define FASTBOOT_LED_ON 0
#define FASTBOOT_LED_OFF 1

void fastboot_led_register_commands(void);
void set_fastboot_led(bool red, bool green, bool blue);
bool fastboot_led_init();
#endif

#endif
