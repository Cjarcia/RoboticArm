#include "TM4C123GH6PM.h"

void ADC_Init(void)
{   
    // Clocks
    SYSCTL->RCGCADC |= 0x01;  // Enable clock to ADC Module 0
    SYSCTL->RCGCGPIO |= 0x10; // Enable clock to Port E
    
    // Dumb delay for clock stabilization
    for(volatile int i = 0; i < 1000; i++); 
    
    // Pins (Configuring PE1 and PE2)
    GPIOE->DIR &= ~0x06;      // Set PE1 as an input  (Bit 1 = 0x02)
    GPIOE->AFSEL |= 0x06;     // Enable alternate function on PE1
    GPIOE->DEN &= ~0x06;      // Disable digital functionality on PE1
    GPIOE->AMSEL |= 0x06;     // Enable analog on PE1
    
    // Parameters
    ADC0->ACTSS &= ~0x01;     // Disable Sample Sequencer 3 (SS3) before setup
    ADC0->EMUX &= ~0x000F;   // Select software trigger for SS3 
    
    // Configure the multiplexer to route AIN2 (PE1) to SS3
    ADC0->SSMUX0 &= ~0xFFFFFFFF;
		ADC0->SSMUX0 |= 0x00000021; // Clear the 1st sample slot 
   
    
    // Configure the control bits for the 1st (and only) sample in SS3
     ADC0->SSCTL0 = 0x00000060;  
    
    // Enable
		ADC0->ACTSS |= 0x01;// Turn Sample Sequencer 3 (SS3) back on
}

void ADC_Sample(uint32_t buffer[])
{
    ADC0->PSSI = 0x01;            // trigger SS0
    while((ADC0->RIS & 0x01) == 0){}

    buffer[0] = ADC0->SSFIFO0 & 0xFFF;   // first sample PE2
    buffer[1] = ADC0->SSFIFO0 & 0xFFF;   // second sample PE1

    ADC0->ISC = 0x01;             // clear SS0 flag
}
