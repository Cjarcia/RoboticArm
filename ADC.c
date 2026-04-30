#include "TM4C123GH6PM.h"

void ADC_Init(void)
{   
    // Clocks
    SYSCTL->RCGCADC |= 0x01;  // Enable clock to ADC Module 0
    SYSCTL->RCGCGPIO |= 0x10; // Enable clock to Port E
    
    // Dumb delay for clock stabilization
    for(volatile int i = 0; i < 1000; i++); 
    
    // Pins (Configuring PE1)
    GPIOE->DIR &= ~0x02;      // Set PE1 as an input  (Bit 1 = 0x02)
    GPIOE->AFSEL |= 0x02;     // Enable alternate function on PE1
    GPIOE->DEN &= ~0x02;      // Disable digital functionality on PE1
    GPIOE->AMSEL |= 0x02;     // Enable analog on PE1
    
    // Parameters
    ADC0->ACTSS &= ~0x08;     // Disable Sample Sequencer 3 (SS3) before setup
    ADC0->EMUX &= ~0xF000;    // Select software trigger for SS3 
    
    // Configure the multiplexer to route AIN2 (PE1) to SS3
    ADC0->SSMUX3 &= ~0x000F;  // Clear the 1st sample slot 
    ADC0->SSMUX3 |= 0x0002;   // Write a '2' to select Channel AIN2 (PE1)
    
    // Configure the control bits for the 1st (and only) sample in SS3
    ADC0->SSCTL3 = 0x0006;       
    
    // Enable
    ADC0->ACTSS |= 0x08;      // Turn Sample Sequencer 3 (SS3) back on
}