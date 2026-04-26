#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"

void ADC_Init(void)
{   
	  //clocks
	  SYSCTL->RCGCADC |= 0x01;// Enable clock to ADC Module 0
    SYSCTL->RCGCGPIO |= 0x10;// Enable clock to Port E
    SysTick_Delay1ms(1);// Give clocks time to stabilize
	
	//pins
	//Configuring PE2 (which is mapped to ADC Channel AIN1)
    GPIOE->DIR &= ~0x04;// Set PE2 as an input 
    GPIOE->AFSEL |= 0x04;// Enable alternate function on PE2
    GPIOE->DEN &= ~0x04;// Disable digital functionality on PE2
    GPIOE->AMSEL |= 0x04;//Enable analog on PE2
	
	//PARAMETERS
    ADC0->ACTSS &= ~0x08;// Disable Sample Sequencer 3 (SS3) before setup
    ADC0->EMUX &= ~0xF000;// Select software trigger for SS3 (Bits 15:12 to 0)
    
    // Configure the multiplexer to route AIN1 (PE2) to SS3
    ADC0->SSMUX3 &= ~0x000F;// Clear the 1st sample slot 
    ADC0->SSMUX3 |= 0x0001;// Write a '1' to select Channel AIN1
    
    // Configure the control bits for the 1st (and only) sample in SS3
    // Set IE0 (Bit 2) to trigger the flag, and END0 (Bit 1) to mark end of sequence
    ADC0->SSCTL3 = 0x0006;       
    
    //enable
    ADC0->ACTSS |= 0x08;// Turn Sample Sequencer 3 (SS3) back on
	
	
}