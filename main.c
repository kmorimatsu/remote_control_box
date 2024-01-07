/*
   This file is provided under the LGPL license ver 2.1
   https://github.com/kmorimatsu
*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "flash_counter.h"

int main() {
	/*// LED ON
	const uint LED_PIN = PICO_DEFAULT_LED_PIN;
	gpio_init(LED_PIN);
	gpio_set_dir(LED_PIN, GPIO_OUT);
	gpio_put(LED_PIN, 1);//*/
	
	// PWM port settings
	const uint port=0;
	const uint slice=0;
	const uint channel=PWM_CHAN_A;
	const float freq=50.0;
	const uint middle_position=75;
	const uint upper_position=40;
	const uint lower_position=110;
	gpio_init(port);
	gpio_set_function(port, GPIO_FUNC_PWM);
	pwm_set_clkdiv(slice,125000.0/65.0/freq);
	pwm_set_wrap(slice, 65000);
	pwm_set_chan_level(slice, channel, middle_position*65);
	pwm_set_enabled(slice, true);

	// Read flash counter
	int i=read_flash_counter();
	increment_flash_counter();
	
	// Move servo	
	if (i & 1) {
		//pwm_set_chan_level(slice, channel, upper_position*65);
		for(i=0;i<=65;i++){
			pwm_set_chan_level(slice, channel, i*upper_position+(65-i)*middle_position);
			sleep_ms(5);
		}
	} else {
		//pwm_set_chan_level(slice, channel, lower_position*65);
		for(i=0;i<=65;i++){
			pwm_set_chan_level(slice, channel, i*lower_position+(65-i)*middle_position);
			sleep_ms(5);
		}
	}
	pwm_set_chan_level(slice, channel, middle_position*65);
	sleep_ms(500);
	
	// Done. Power off
	gpio_init(1);
	gpio_set_dir(1, GPIO_OUT);
	gpio_put(1, 0);
	while(true) sleep_ms(1000);
}
