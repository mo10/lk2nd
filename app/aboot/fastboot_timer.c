#include <stdlib.h>
#include "fastboot.h"
#include "fastboot_timer.h"
#include "fastboot_led.h"

#ifdef FASTBOOT_TIMER
bool stay_in_fastboot = false;

bool fastboot_stay_requested() 
{
    return stay_in_fastboot;
}

void set_fastboot_stay_flag(bool en) 
{
	stay_in_fastboot = en;

	if (stay_in_fastboot) {
		set_fastboot_led(FASTBOOT_LED_CONFIG_STAY);
	}
}

static void cmd_oem_stay(const char *arg, void *data, unsigned sz)
{
    stay_in_fastboot = true;
	set_fastboot_led(FASTBOOT_LED_CONFIG_STAY);
	fastboot_okay("");
}

void fastboot_timer_register_commands(void) {
	fastboot_register("oem stay", cmd_oem_stay);
}
#endif