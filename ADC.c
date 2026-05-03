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
	
	  // Pins (Configuring PE3 and PE4)
    GPIOE->DIR &= ~0x18; // Set PE3 and PE4 as inputs (Bit 3 & 4 = 0x18)
    GPIOE->AFSEL |= 0x18; // Enable alternate function on PE3 and PE4
    GPIOE->DEN &= ~0x18;  // Disable digital functionality on PE3 and PE4
    GPIOE->AMSEL |= 0x18; // Enable analog on PE3 and PE4
	
	  // Configure PE5 and PE0
    GPIOE->DIR &= ~0x21; // Set PE5 as input (Bit 5 = 0x20)
    GPIOE->AFSEL |= 0x21; // Enable alternate function on PE5
    GPIOE->DEN &= ~0x21;  // Disable digital functionality on PE5
    GPIOE->AMSEL |= 0x21; // Enable analog on PE5
	   
	  // Parameters
     ADC0->ACTSS &= ~0x01;        // Disable Sample Sequencer 0 (SS0) before setup
     ADC0->EMUX &= ~0x000F;       // Select software trigger for SS0 

     // Configure the multiplexer to route 4 pins to SS0
     ADC0->SSMUX0 &= ~0xFFFFFFFF; // Clear all slots
     ADC0->SSMUX0 |= 0x00389021;  // Route PE2, PE1, PE3, PE4, PE5, PE0 (AIN1, AIN2, AIN0, AIN9, AIN8, AIN3)

     // Configure the control bits for the 6th sample in SS0
     ADC0->SSCTL0 = 0x00600000;   // Set IE3 and END3 (Stop after 6th sample)

     // Enable
     ADC0->ACTSS |= 0x01;         // Turn Sample Sequencer 0 (SS0) back on
    
    
}

void ADC_Sample(uint32_t buffer[])
{
    ADC0->PSSI = 0x01;            // Trigger SS0
    while((ADC0->RIS & 0x01) == 0){} // Wait for the flag

    // Must be read in the order defined by SSMUX0 (1, 2, 0, 9)
    buffer[0] = ADC0->SSFIFO0 & 0xFFF;   // 1st sample: AIN1 (PE2)
    buffer[1] = ADC0->SSFIFO0 & 0xFFF;   // 2nd sample: AIN2 (PE1)
    buffer[2] = ADC0->SSFIFO0 & 0xFFF;   // 3rd sample: AIN0 (PE3)
    buffer[3] = ADC0->SSFIFO0 & 0xFFF;   // 4th sample: AIN9 (PE4)
		buffer[4] = ADC0->SSFIFO0 & 0xFFF;   // 5th sample: AIN8 (PE5)
		buffer[5] = ADC0->SSFIFO0 & 0xFFF;   // 6th sample: AIN3 (PE0)
			

    ADC0->ISC = 0x01;             // Clear SS0 flag
}
