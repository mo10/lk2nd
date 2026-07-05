#include <debug.h>
#include <stdlib.h>
#include <string.h>
#include <pm8x41.h>

#include "fastboot.h"
#include "fastboot_led.h"

#ifdef FASTBOOT_LED
static bool fastboot_led_ready = false;

static void set_fastboot_mpp(uint32_t base, bool enabled)
{
	struct pm8x41_mpp mpp = {
		.base = base,
		.vin = MPP_VIN0,
		.mode = enabled ? MPP_LOW : MPP_HIGH,
	};

	pm8x41_config_output_mpp(&mpp);
	pm8x41_enable_mpp(&mpp, MPP_ENABLE);
}

void set_fastboot_led(bool red, bool green, bool blue)
{
	if(!fastboot_led_ready) {
		fastboot_led_init();
	}

	set_fastboot_mpp(FASTBOOT_LED_RED_MPP_BASE, red);
	set_fastboot_mpp(FASTBOOT_LED_GREEN_MPP_BASE, green);
	set_fastboot_mpp(FASTBOOT_LED_BLUE_MPP_BASE, blue);
}

bool fastboot_led_init()
{
	set_fastboot_mpp(FASTBOOT_LED_RED_MPP_BASE, false);
	set_fastboot_mpp(FASTBOOT_LED_GREEN_MPP_BASE, false);
	set_fastboot_mpp(FASTBOOT_LED_BLUE_MPP_BASE, false);

	fastboot_led_ready = true;
	return fastboot_led_ready;
}

static void cmd_oem_led(const char *arg, void *data, unsigned sz)
{
	if (!strcmp(arg, "red")) {
		set_fastboot_led(true, false, false);
	} else if (!strcmp(arg, "green")) {
		set_fastboot_led(false, true, false);
	} else if (!strcmp(arg, "blue")) {
		set_fastboot_led(false, false, true);
	} else if (!strcmp(arg, "off")) {
		set_fastboot_led(false, false, false);
	} else if (!strcmp(arg, "white") || !strcmp(arg, "on")) {
		set_fastboot_led(true, true, true);
	} else {
		fastboot_fail("usage: oem led red|green|blue|white|on|off");
		return;
	}

	fastboot_okay("");
}

void fastboot_led_register_commands(void) {
	fastboot_register("oem led", cmd_oem_led);
}
#endif