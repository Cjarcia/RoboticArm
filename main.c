#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
uint32_t adc_result;
uint32_t high_ticks;
uint32_t new_cmpa;

int main(void){
	
	
	while(1)
	{
		
		uint32_t adc_result;
uint32_t high_ticks;
uint32_t new_cmpa;

while(1)
{
    // 1. Tell the ADC to take a reading (Software Trigger)
    ADC0->PSSI |= 0x0008;// Trigger Sample Sequencer 3 (SS3)
    
    // 2. Wait until the reading is finished (Polling)
    while((ADC0->RIS & 0x08) == 0); // Trapped until Bit 3 flips to 1
    
    // 3. Grab the data from the FIFO (Value will be 0 to 4095)
    adc_result = ADC0->SSFIFO3 & 0xFFF; 
    
    // 4. Clear the flag so the ADC can take another reading later
    ADC0->ISC = 0x0008; 
    
    // 5. Map 0-4095 to our 3125-6250 tick range
    high_ticks = 3125 + ((adc_result * 3125) / 4095);
    
    // 6. Calculate CMPA (Since the timer counts DOWN)
    new_cmpa = 62500 - high_ticks;
    
    // 7. Update the PWM hardware to move the servo!
    PWM0->_0_CMPA = new_cmpa;
    
    //delay
		SysTick_Delay1ms(1000);
}

	}
	
}