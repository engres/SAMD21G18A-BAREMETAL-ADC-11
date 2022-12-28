// DEFINES AND INCLUDES
#include <atmel_start.h>

#define ADC_11_channel								11
#define ADC_11_raw_buffer_size						2				
#define ADC_11_ave_buffer_size						100				//100
#define ADC_11_voltage_reference					2.229729729730	//VDC INTERNAL

#define ADC_16_bit__full_scale_resolution			32767 			//FULL SCALE RANGE FOR SIGNED 16 BIT VARIABLE
/*Integer, 16 Bit: Signed Integers ranging from -32768 to +32767.
Integer, 16 bit data type is used for numerical tags where variables
have the potential for negative or positive values.	*/

//PRESSURE MAPPING VALUES
#define max_adc_11_value		32008
#define min_adc_11_value		6320			

#define max_pressure			150				// PSI
#define min_pressure			0				// PSI
/*110 Ohm Shunt Resistor converts 4 - 20ma | 0 - 150 PSI pressure transmitter signal to a voltage range */
#define voltage_at_max			2.20			// VDC	(2.22 Calculated | XX Observed)
#define voltage_at_min			0.64			// VDC	(0.44 Calculated | 0.64 Observed)

// GLOBAL VARIABLES
uint16_t	ADC_11_value =		0;				// 16 BIT UNSIGNED INTEGER FOR SINGLE ENDED (ALWAYS POSITVE)
int values;
int size;

float		ADC_11_volts =		0;				// INITIALIZE AS 0
float		ADC_11_pressure =	0;				// INITIALIZE AS 0

float map(float x, float in_min, float in_max, float out_min, float out_max) { return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

int main(void)
{
	atmel_start_init();
	adc_sync_enable_channel(&ADC_0, ADC_11_channel);

	float average(int* values, int size){
		int sum = 0;
		for (int i = 0; i < size - 1; i++){
			sum += values[i];
		}
		return (float)sum / size;
	}

	void ADC_11_read(void)
	{
		/* //////////////////////////////////////////////////////
		 * ADC READ CONFIGURATION SUMMARY
		 * ADC CHANNEL:			11 (+) PB03/A7 
		 * ADC MODE:			SINGLE ENDED VS. GROUND	
		 * ADC CLOCK SOURCE:	GENERIC CLOCK 2 >> [OSC32K] HIGH-ACCURACY @ 1 kHz
		 * RESOLUTION:			16 BIT
		 * AVERAGED SAMPLES:	4
		 * REFERENCE:			2.23 VDC INTERNAL
		 *////////////////////////////////////////////////////////
		
		uint8_t ADC_11_raw_buffer[ADC_11_raw_buffer_size];						//Initializing a ADC buffer for raw outputs
		int ADC_11_ave_buffer[ADC_11_ave_buffer_size];							//Initializing an averaging buffer for the raw values	

		for (int i = 0; i < ADC_11_ave_buffer_size - 1; i++)
		{
			adc_sync_read_channel(&ADC_0, ADC_11_channel, ADC_11_raw_buffer, ADC_11_raw_buffer_size);
			ADC_11_value = ADC_11_raw_buffer[1];								//See adcbuff value
			ADC_11_value = ADC_11_value << 8;									//Moving to the upper 8 bits
			ADC_11_value = ADC_11_value | ADC_11_raw_buffer[0];					//Appending lower 8 bit value to previous value			//16-bit ADC value:
			
			ADC_11_ave_buffer[i] = ADC_11_value;
			delay_ms(1);
		}

		//CALCULATING AVERAGE ADC CHANNEL 11 VALUE
		ADC_11_value = average(ADC_11_ave_buffer, ADC_11_ave_buffer_size);
		printf("\nADC 11 Value: %i",ADC_11_value);								//print integer
		
		//CALCULATING VOLTAGE READING FOR THE ADC 11
		ADC_11_volts = ((float)ADC_11_value * (float)ADC_11_voltage_reference / (float)ADC_16_bit__full_scale_resolution);
		printf("%.2f",ADC_11_volts);											//print float
		
		//CALCULATING PRESSURE READING FOR THE ADC 11
		ADC_11_pressure = map(ADC_11_volts,voltage_at_min,voltage_at_max,min_pressure,max_pressure);
		
		//CONVERTING FLOAT TO STRING FOR READOUT
		//char out_str[30] = {0};     // string to print to and transmit
		//sprintf(out_str, "ADC 11 Value: %f\r\n", ADC_11_pressure);
		
		//UartTxStr(out_str);
		
		
	}//END ADC_11_READ

	char *setup_greeting = "\nSETUP COMPLETE!\n";	
	printf("\n%s"); //GREETING
	
	///////////////////////////END OF SETUP////////////////////////////////
	
	while (1)
	{
		LED_0_on();
		ADC_11_read();
		
		delay_ms(50);
		LED_0_off();
	}	//END OF APP LOOP
	

}//END OF MAIN

//************************************************************************