/*
 * ioapi.h
 *
 * Created: 29.2.2012 9:01:20
 *  Author: savpek
 */


#ifndef IOAPI_H_
#define IOAPI_H_

#include "framework.h"

/*! @brief Set defined pin to high state. Pin must be initialized correctly beforehand.
 *
 *	@param uint8_t pin_number
 *
 * 	@return void */
extern void (*ioapi_output_high)( uint8_t pin_number);

/*! @brief Set defined pin output low. Pin must be initialized correctly beforehand.
 *
 *	@param uint8_t pin_number
 *
 * 	@return extern void: */
extern void (*ioapi_output_low)( uint8_t pin_number );


extern statusc_t ioapi_is_it_output( uint8_t pin_number);

/*! @brief Get pin current input value. Pin must be initialized correctly beforehand.
 *
 *	@param uint8_t pin_number
 *
 * 	@return extern statusc_t: SC_TRUE, SC_FALSE */
extern statusc_t ioapi_input_value( uint8_t pin_number );


extern statusc_t ioapi_is_it_input( uint8_t pin_number);

extern void ioapi_output_pwm( uint8_t pin_number, uint32_t pwm_percent );

extern statusc_t ioapi_is_it_pwm( uint8_t pin_number);

/*! @brief Get ADC value of pin, pin must be configured correctly before use
 *	 and ADC converter must be initalized correctly.
 *
 *	@param uint8_t pin_number :
 *
 * 	@return extern uint32_t : ADC value. */
extern uint32_t ioapi_input_adc( uint8_t pin_number );

extern statusc_t ioapi_is_it_adc( uint8_t pin_number);

typedef enum {
	IOAPI_OUTPUT =		0x01,
	IOAPI_INPUT  =		0x02,
	IOAPI_GPIO_USED =	0x04,
	IOAPI_PERIPHEAL_USED = 0x08,
	IOAPI_OUT_HIGH = 0x10,
	IOAPI_OUT_LOW  = 0x20,
	IOAPI_INPUT_HIGH  = 0x40,
	IOAPI_INPUT_LOW	  = 0x80,
	IOAPI_PULL_UP	  = 0x100
} ioapi_pin_status_t;

#endif /* IOAPI_H_ */