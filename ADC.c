#include "TM4C123GH6PM.h"
void delayMs(int n);

void Port_Initialization(void){
	// Clocks
	SYSCTL->RCGCPWM |= 0x03;  // Enable clock to PWM module 0 AND module 1
	SYSCTL->RCGCGPIO |= 0x22; // Enable clock to Port B and F
	
	// PWM clock configuration
	SYSCTL->RCC &= ~0x000E0000; // Clear the PWMDIV field
	SYSCTL->RCC |= 0x001A0000;  // Set USEPWMDIV and set divider to /64
	delayMs(100);
}

void Servo_PB4_Init(void)
{	
	// Pins 
	GPIOB->AFSEL |= 0x10;       // Enable alternate function on PB4
	GPIOB->PCTL &=~0x000F0000;  // Clear PMC4 slot
	GPIOB->PCTL |= 0x00040000;  // Write 4 to PMC4 to assign M0PWM2 to PB4
	GPIOB->DEN |= 0x10;         // Enable digital functionality on PB4
	
	// Parameters
	PWM0->_1_CTL &= ~0x01;      // Disable generator 1 before using
	PWM0->_1_CTL &= ~0x02;      // Select standard count down mode
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPAD = 0x2 (Drive Low on CMPA)
	PWM0->_1_GENA = (0x03 << 2) | (0x02 << 6); 
	
	// Set the Period 
	// 16 MHz / 64 = 250,000 ticks. 250,000 / 50 Hz = 5000 ticks.
	PWM0->_1_LOAD = 5000 - 1;
	
	// Default to Center Position (1.5ms)
	// 1.5ms = 375 ticks. 5000 - 375 = 4625.
	PWM0->_1_CMPA = 4625;
	
	// Enable
	PWM0->_1_CTL |= 0x01;       // Start timer generator 1
	PWM0->ENABLE |= 0x04;       // Connect signal to the PB4 pin (M0PWM2)
}

void Servo_PB5_Init(void)
{
	// Pins 
	GPIOB->AFSEL |= 0x20;       // Enable alternate function on PB5
	GPIOB->PCTL &= ~0x00F00000; // Clear PMC5 slot
	GPIOB->PCTL |= 0x00400000;  // Write 4 to PMC5 to assign M0PWM3 to PB5
	GPIOB->DEN |= 0x20;         // Enable digital functionality on PB5
	
	// Parameters
	PWM0->_1_CTL &= ~0x01;      // Disable generator 1 before using
	PWM0->_1_CTL &= ~0x02;      // Select standard count down mode
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPAD = 0x2 (Drive Low on CMPA)
	PWM0->_1_GENB = 0x0000080C; 
	
	// Set the Period 
	// 16 MHz / 64 = 250,000 ticks. 250,000 / 50 Hz = 5000 ticks.
	PWM0->_1_LOAD = 5000 - 1;
	
	// Default to Center Position (1.5ms)
	// 1.5ms = 375 ticks. 5000 - 375 = 4625.
	PWM0->_1_CMPB = 4625;
	
	// Enable
	PWM0->_1_CTL |= 0x01;       // Start timer generator 1
	PWM0->ENABLE |= 0x08;       // Connect signal to the PB5 pin (M0PWM3)
}

void Servo_PB6_Init(void)
{
	// Pins 
	GPIOB->AFSEL |= 0x40;       // Enable alternate function on PB6
	GPIOB->PCTL &= ~0x0F000000; // Clear PMC6 slot
	GPIOB->PCTL |= 0x04000000;  // Write 4 to PMC6 to assign M0PWM0 to PB6
	GPIOB->DEN |= 0x40;         // Enable digital functionality on PB6
	
	// Parameters
	PWM0->_0_CTL &= ~0x01;      // Disable generator 0 before using
	PWM0->_0_CTL &= ~0x02;      // Select standard count down mode
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPAD = 0x2 (Drive Low on CMPA)
	PWM0->_0_GENA = (0x03 << 2) | (0x02 << 6); 
	
	// Set the Period 
	// 16 MHz / 64 = 250,000 ticks. 250,000 / 50 Hz = 5000 ticks.
	PWM0->_0_LOAD = 5000 - 1;
	
	// Default to Center Position (1.5ms)
	// 1.5ms = 375 ticks. 5000 - 375 = 4625.
	PWM0->_0_CMPA = 4625;
	
	// Enable
	PWM0->_0_CTL |= 0x01;       // Start timer generator 0
	PWM0->ENABLE |= 0x01;       // Connect signal to the PB6 pin (M0PWM0)
}


void Servo_PF3_Init(void){
	// Pins
	GPIOF -> AFSEL |= 0x08;     // Enable alternate function on PF3
	GPIOF -> PCTL &= ~0x0000F000; // Clear PMC3 slot
	GPIOF -> PCTL |= 0x00005000;  // Write 5 to PMC3 to assign M1PWM7 to PF3
	//GPIOF->AMSEL &= ~0x08;
	GPIOF -> DEN |= 0x08;       // Enable digital functionality on PF3
	 
	// PWM Configuration
	PWM1 -> _3_CTL = 0;         // Disable generator 3 before using, standard count down mode
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPBD = 0x2 (Drive Low on CMPB)
	PWM1 -> _3_GENB &= ~0x00000FFF;
	PWM1 -> _3_GENB |= 0x0000080C;
	
	// Set Period and Default Compare
	PWM1->_3_LOAD = 5000 - 1;
	PWM1->_3_CMPB = 4625;
	
	// Enable
	PWM1->_3_CTL = 1;           // Start timer generator 3
	PWM1->ENABLE |= 0x80;       // Connect signal to the PF3 pin (M1PWM7)
}

void Servo_PF0_Init(void){
	// PF0 is locked by default (NMI pin), so we must unlock it first
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->CR |= 0x01;
	
	// Pins
	GPIOF -> AFSEL |= 0x01;     // Enable alternate function on PF0
	GPIOF -> PCTL &= ~0x0000000F; // Clear PMC0 slot
	GPIOF -> PCTL |= 0x00000005;  // Write 5 to PMC0 to assign M1PWM4 to PF0
	GPIOF -> DEN |= 0x01;       // Enable digital functionality on PF0
	
	// PWM Configuration
	PWM1 -> _2_CTL = 0;         // Disable generator 2 before using
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPAD = 0x2 (Drive Low on CMPA)
	PWM1 -> _2_GENA &= ~0x00000FFF;
	PWM1->_2_GENA = (0x03 << 2) | (0x02 << 6); 
	
	// Set Period and Default Compare
	PWM1->_2_LOAD = 5000 - 1;
	PWM1->_2_CMPA = 4625;
	
	// Enable
	PWM1->_2_CTL |= 1;          // Start timer generator 2
	PWM1->ENABLE |= 0x10;       // Connect signal to the PF0 pin (M1PWM4)
}

void Servo_PF1_Init(void){
	// Pins
	GPIOF -> AFSEL |= 0x02;     // Enable alternate function on PF1
	GPIOF -> PCTL &= ~0x000000F0; // Clear PMC1 slot
	GPIOF -> PCTL |= 0x00000050;  // Write 5 to PMC1 to assign M1PWM5 to PF1
	GPIOF -> DEN |= 0x02;       // Enable digital functionality on PF1
	
	// PWM Configuration
	PWM1 -> _2_CTL = 0;         // Disable generator 2 before using
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPBD = 0x2 (Drive Low on CMPB)
	PWM1 -> _2_GENB &= ~0x00000FFF;
	PWM1 -> _2_GENB |= 0x0000080C;
	
	// Set Period and Default Compare
	PWM1->_2_LOAD = 5000 - 1;
	PWM1->_2_CMPB = 4625;
	
	// Enable
	PWM1->_2_CTL |= 1;          // Start timer generator 2
	PWM1->ENABLE |= 0x20;       // Connect signal to the PF1 pin (M1PWM5)
}

// Basic nested loop delay
void delayMs(int n){
	int i,j;
	for(i = 0; i<n; i++){
		for(j=0; j<3000; j++){
			//do nothing
		}
	}
}