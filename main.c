#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"
// Function Declaration
static uint32_t adc_buffer[8];
void ADC_Sample(uint32_t buffer[]);
	
void ADC_Init(void);
int main(void){
	Port_Initialization();
	// 1. Initialize Servo
	Servo_PB4_Init();
	Servo_PB6_Init();
	//2. initialize ADC potentiometer
	ADC_Init();
	
	//initialize systick
	//SysTick_Delay_Init();
	
	//uint32_t adc_result;
	uint32_t high_ticks0;
	uint32_t high_ticks1;
	uint32_t new_compare0;
	uint32_t new_compare1;
	
	// 2. Main Loop Sweep the Servo
	while(1)
	{
    ADC_Sample(adc_buffer);
    
    high_ticks0 = 125 + ((adc_buffer[0] * 500) / 4095);
    high_ticks1 = 125 + ((adc_buffer[1] * 500) / 4095);

    // 6. Calculate CMPA (Since the timer counts DOWN)
    new_compare0 = 5000 - high_ticks0;
		new_compare1 = 5000 - high_ticks1;
    
    // 7. Update the PWM hardware to move the servo!
    PWM0->_1_CMPA = new_compare0;//PE2
		
    PWM0->_0_CMPA = new_compare1;//PE1
    //delay
		for(volatile int i = 0; i < 40000; i++);
	  //SysTick_Delay1ms(20);
	}
}