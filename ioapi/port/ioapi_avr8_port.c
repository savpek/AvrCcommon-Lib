#include "ioapi/public/ioapi.h"
#include "utest/public/utest.h"
#include "gpio/public/gpio.h"

void ioapi_output_high_body( uint8_t pin_number ) {
//	ASSERT( gpio_is_it_output( pin_number) == SC_TRUE);
	gpio_set_high(pin_number);
}
void (*ioapi_output_high)(uint8_t pin_number) = ioapi_output_high_body;

void ioapi_output_low_body( uint8_t pin_number ) {
//	ASSERT( gpio_is_it_output( pin_number) == SC_TRUE);
	gpio_set_low(pin_number);
}
void (*ioapi_output_low)(uint8_t pin_number) = ioapi_output_low_body;

statusc_t ioapi_is_it_output( uint8_t pin_number) {
//	return gpio_is_it_output();
}

statusc_t ioapi_input_value( uint8_t pin_number ) {
	return gpio_get_input(pin_number);
}

statusc_t ioapi_is_it_input( uint8_t pin_number) {
//	if( gpio_is_it_output( pin_number) == SC_TRUE)
//		return SC_FALSE;
//	else
//		return SC_TRUE;
}

statusc_t ioapi_is_it_adc( uint8_t pin_number)
{
	
}

uint32_t ioapi_input_adc( uint8_t pin_number )
{
}
