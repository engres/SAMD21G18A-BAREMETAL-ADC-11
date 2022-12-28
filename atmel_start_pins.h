/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

//PORT DEFINITIONS
#define PA24			GPIO(GPIO_PORTA, 24)		//ADC 11 (+) PRESSURE SENSOR
#define PA25			GPIO(GPIO_PORTA, 25)		//ADC 11 (+) PRESSURE SENSOR

#define PB03			GPIO(GPIO_PORTB, 3)			//ADC 11 (+) PRESSURE SENSOR
#define PB22			GPIO(GPIO_PORTB, 22)		//TX
#define PB23			GPIO(GPIO_PORTB, 23)		//RX

#define PUMP_0_PIN		GPIO(GPIO_PORTB, 10)		// PUMP RELAY							DIGITAL OUTPUT		(D2)
#define VALVE_0_PIN		GPIO(GPIO_PORTB, 11)		// VALVE 1 RELAY						DIGITAL OUTPUT		(D3)
#define VALVE_1_PIN		GPIO(GPIO_PORTA, 7)			// VALVE 2 RELAY						DIGITAL OUTPUT		(D4)

#define LED_BUILTIN		GPIO(GPIO_PORTA, 17)		// FLASHER								DIGITAL OUTPUT		(D13)
#define LOW_LVL_PIN		GPIO(GPIO_PORTB, 3)			// LOW LEVEL FLOAT SWITCH 				DIGITAL INPUT		(D21/A7)	DRY-CONTACT CLOSE TO ALARM

#endif // ATMEL_START_PINS_H_INCLUDED
