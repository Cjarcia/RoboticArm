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
	Servo_PB5_Init();
	Servo_PF1_Init();
	Servo_PF0_Init();
	Servo_PF3_Init();
	//2. initialize ADC potentiometer
	ADC_Init();
	
	//initialize systick
	//SysTick_Delay_Init();
	
	//uint32_t adc_result;
	uint32_t high_ticks0;
	uint32_t high_ticks1;
	uint32_t high_ticks2;
	uint32_t high_ticks3;
	uint32_t high_ticks4;
	uint32_t high_ticks5;
	uint32_t new_compare0;
	uint32_t new_compare1;
	uint32_t new_compare2;
	uint32_t new_compare3;
	uint32_t new_compare4;
	uint32_t new_compare5;
	
	// 2. Main Loop Sweep the Servo
	while(1)
	{
    ADC_Sample(adc_buffer);
    
    high_ticks0 = 125 + ((adc_buffer[0] * 500) / 4095);
    high_ticks1 = 125 + ((adc_buffer[1] * 500) / 4095);
		high_ticks2 = 125 + ((adc_buffer[2] * 500) / 4095);
		high_ticks3 = 125 + ((adc_buffer[3] * 500) / 4095);
		high_ticks4 = 125 + ((adc_buffer[4] * 500) / 4095);
		high_ticks5 = 125 + ((adc_buffer[5] * 500) / 4095);

    // 6. Calculate CMPA (Since the timer counts DOWN)
    new_compare0 = 5000 - high_ticks0;
		new_compare1 = 5000 - high_ticks1;
		new_compare2 = 5000 - high_ticks2;
		new_compare3 = 5000 - high_ticks3;
		new_compare4 = 5000 - high_ticks4;
		new_compare5 = 5000 - high_ticks5;
    
    // 7. Update the PWM hardware to move the servo!
    PWM0->_1_CMPA = new_compare0;//PE2 with PB4
		
    PWM0->_1_CMPB = new_compare1;//PE1 with PB5
		
		PWM0->_0_CMPA = new_compare2;//PE3 with PB6 something wrong..
		
		PWM1->_3_CMPB = new_compare3;//PE4 with PF3
		
		PWM1->_2_CMPA = new_compare4;//PE5 with PF0
		
		PWM1->_2_CMPB = new_compare5;//PE0 with PF1
    //delay
		for(volatile int i = 0; i < 40000; i++);
	  //SysTick_Delay1ms(20);
	}
}