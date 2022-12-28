/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

#include <hpl_adc_base.h>

struct adc_sync_descriptor ADC_0;

struct usart_sync_descriptor TARGET_IO;

void ADC_0_PORT_init(void)
{
	// Disable digital pin circuitry
	gpio_set_pin_direction(PB03, GPIO_DIRECTION_OFF);

	gpio_set_pin_function(PB03, PINMUX_PB03B_ADC_AIN11);
}

void ADC_0_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, ADC);
	_gclk_enable_channel(ADC_GCLK_ID, CONF_GCLK_ADC_SRC);
}

void ADC_0_init(void)
{
	ADC_0_CLOCK_init();
	ADC_0_PORT_init();
	adc_sync_init(&ADC_0, ADC, (void *)NULL);
}

void TARGET_IO_PORT_init(void)
{
	//PORT A THROUGH THE USB
	//gpio_set_pin_function(PA24, PINMUX_PA24D_SERCOM5_PAD2);						//GPIO 'TX' PIN CONFIGURATION WITH PB23 PORT DEFINITION FOR SERCOM5 PERIPHERAL
	//gpio_set_pin_function(PA25, PINMUX_PA25D_SERCOM5_PAD3);						//GPIO 'RX' PIN CONFIGURATION WITH PB22 PORT DEFINITION FOR SERCOM5 PERIPHERAL
	
	//PORT B THROUGH THE TX/RX Pins
	gpio_set_pin_function(PB22, PINMUX_PB22D_SERCOM5_PAD2);						//GPIO 'TX' PIN CONFIGURATION WITH PB23 PORT DEFINITION FOR SERCOM5 PERIPHERAL
	gpio_set_pin_function(PB23, PINMUX_PB23D_SERCOM5_PAD3);						//GPIO 'RX' PIN CONFIGURATION WITH PB22 PORT DEFINITION FOR SERCOM5 PERIPHERAL
}

void TARGET_IO_CLOCK_init(void)
{
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM5);									//POWER MANAGEMENT BUS APB BASE ADDRESS TO SERCOM5 
	_gclk_enable_channel(SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC);		//PORT DEFINITION FOR SERCOM5 PERIPHERAL INSTANCE SOURCED W/ GCLK:0
}

void TARGET_IO_init(void)
{
	TARGET_IO_CLOCK_init();
	usart_sync_init(&TARGET_IO, SERCOM5, (void *)NULL);
	TARGET_IO_PORT_init();
}

void stdio_redirect_init(void)
{
	usart_sync_enable(&TARGET_IO);
	stdio_io_init(&TARGET_IO.io);
}

void delay_driver_init(void)
{
	delay_init(SysTick);
}

void system_init(void)
{
	init_mcu();

	ADC_0_init();

	TARGET_IO_init();

	delay_driver_init();

	LED_0_init();
	PUMP_init();
	VALVE_0_init();
	VALVE_1_init();
}

///////////////////////////////////////////
// ONBOARD LED INITIALIZATION
///////////////////////////////////////////
void LED_0_init(void)
{	//CONFIGURE GPIO ON PA17 TO FUNCTION AS ONBOARD LED INDICATOR
	gpio_set_pin_direction(LED_BUILTIN, GPIO_DIRECTION_OUT);
	gpio_set_pin_pull_mode(LED_BUILTIN, GPIO_PULL_OFF);
	gpio_set_pin_function(LED_BUILTIN, GPIO_PIN_FUNCTION_OFF);
	gpio_set_pin_level(LED_BUILTIN,true);
}

void LED_0_on(void)
{
	gpio_set_pin_level(LED_BUILTIN,true);
}
void LED_0_off(void)
{
	gpio_set_pin_level(LED_BUILTIN,false);
}

void LED_0_toggle(void)
{
	gpio_toggle_pin_level(LED_BUILTIN);
}

///////////////////////////////////////////
// PUMP DRIVER INTILIZATION
///////////////////////////////////////////
void PUMP_init(void)
{
	//SET PIN DIRECTION (3 - Different expressions)
	gpio_set_pin_direction(PUMP_0_PIN, GPIO_DIRECTION_OUT);
	//SET PIN FUNCTION
	gpio_set_pin_function(PUMP_0_PIN, GPIO_PIN_FUNCTION_OFF);
	//CONFIGURE GPIO TO FUNCTION AS A RELAY OUTPUT FOR THE PUMP
	gpio_set_pin_level(PUMP_0_PIN,false);
}
void PUMP_off(void)
{
	//SET PIN FUNCTION
	gpio_set_pin_level(PUMP_0_PIN, false);
};
void PUMP_on(void)
{
	//SET PIN FUNCTION
	gpio_set_pin_level(PUMP_0_PIN, true);
};

///////////////////////////////////////////
// VALVE DRIVER INTILIZATION
///////////////////////////////////////////
void VALVE_0_init(void)
{
	gpio_set_pin_direction(VALVE_0_PIN, GPIO_DIRECTION_OUT);	//SET PIN AS AN OUTPUT ->
	gpio_set_pin_function(VALVE_0_PIN, GPIO_PIN_FUNCTION_OFF);	//SET PIN FUNCTION OFF
	gpio_set_pin_level(VALVE_0_PIN,false);						//START IN THE OFF POSITION
}

void VALVE_0_off(void)
{
	gpio_set_pin_level(VALVE_0_PIN, false);						//CYCLE OFF
}

void VALVE_0_on(void)
{
	gpio_set_pin_level(VALVE_0_PIN, true);						//CYCLE ON
}

void VALVE_1_init(void)
{
	gpio_set_pin_direction(VALVE_1_PIN, GPIO_DIRECTION_OUT);	//SET PIN AS AN OUTPUT ->
	gpio_set_pin_function(VALVE_1_PIN, GPIO_PIN_FUNCTION_OFF);	//SET PIN FUNCTION OFF
	gpio_set_pin_level(VALVE_1_PIN,false);						//START IN THE OFF POSITION
}

void VALVE_1_off(void)
{	//SET PIN FUNCTION
	gpio_set_pin_level(VALVE_1_PIN, false);
}

void VALVE_1_on(void)
{
	//SET PIN FUNCTION
	gpio_set_pin_level(VALVE_1_PIN, true);
}

