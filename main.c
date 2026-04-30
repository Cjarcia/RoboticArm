#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"

// Function Declaration
void Servo_PB6_Init(void);
void ADC_Init(void);

int main(void){
	
	// 1. Initialize Servo
	Servo_PB6_Init();
	
	//2. initialize ADC potentiometer
	ADC_Init();
	
	//initialize systick
	//SysTick_Delay_Init();
	
	uint32_t adc_result;
	uint32_t high_ticks;
	uint32_t new_cmpa;
	
	// 2. Main Loop Sweep the Servo
	while(1)
	{
		// Move to Left (~1.0ms pulse)
		//PWM0->_0_CMPA = 4750;
		//for(volatile int i = 0; i < 1000000; i++); 
		// Move to Center (~1.5ms pulse)
		//PWM0->_0_CMPA = 4625;
		//for(volatile int i = 0; i < 1000000; i++); 
		// Move to Right (~2.0ms pulse)
		//PWM0->_0_CMPA = 4500;
		//for(volatile int i = 0; i < 1000000; i++); 
		// Move back to Center
		//PWM0->_0_CMPA = 4625;
		//for(volatile int i = 0; i < 1000000; i++); 
		
		// 1. Tell the ADC to take a reading (Software Trigger)
    ADC0->PSSI |= 0x0008;// Trigger Sample Sequencer 3 (SS3)
    
    // 2. Wait until the reading is finished (Polling)
    while((ADC0->RIS & 0x08) == 0); // Trapped until Bit 3 flips to 1
    
    // 3. Grab the data from the FIFO (Value will be 0 to 4095)
    adc_result = ADC0->SSFIFO3 & 0xFFF; 
    
    // 4. Clear the flag so the ADC can take another reading later
    ADC0->ISC = 0x0008; 
    
    // 5. Map 0-4095 to our 3125-6250 tick range
    high_ticks = 250 + ((adc_result * 250) / 4095);
    
    // 6. Calculate CMPA (Since the timer counts DOWN)
    new_cmpa = 5000 - high_ticks;
    
    // 7. Update the PWM hardware to move the servo!
    PWM0->_0_CMPA = new_cmpa;
    
    //delay
		for(volatile int i = 0; i < 40000; i++);
	  //SysTick_Delay1ms(20);
	}
}