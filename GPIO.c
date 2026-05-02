
void Port_Initialization(void){
// Clocks
	SYSCTL->RCGCPWM |= 0x01;  // Enable clock to PWM module 0
	SYSCTL->RCGCGPIO |= 0x02; // Enable clock to Port B

// PWM clock configuration (/64 Divider from teammate's code)
	SYSCTL->RCC &= ~0x000E0000; // Clear the PWMDIV field
	SYSCTL->RCC |= 0x001A0000;  // Set USEPWMDIV and set divider to /64
   

}

void Servo_PB4_Init(void)
{	

	// Pins 
	GPIOB->AFSEL |= 0x10;    // Enable alternate function on PB7
	GPIOB->PCTL &= ~0x000F0000; // Clear PMC7 SLOT
	GPIOB->PCTL |= 0x00040000;  // Write 4 to PMC6 to assign PWM0 to PB6
	GPIOB->DEN |= 0x10;         // Enable digital functionality on PB6
	
	
	// Parameters
	PWM0->_1_CTL &= ~0x01;      // Disable generator 0 before using
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
	PWM0->_1_CTL |= 0x01;       // Start timer generator 0
	PWM0->ENABLE |= 0x04;       // Connect signal to the PB6 pin (PWM0EN)
}

void Servo_PB6_Init(void)
{
	// Pins 
	GPIOB->AFSEL |= 0x40;       // Enable alternate function on PB6
	GPIOB->PCTL &= ~0x0F000000; // Clear PMC6 SLOT
	GPIOB->PCTL |= 0x04000000;  // Write 4 to PMC6 to assign PWM0 to PB6
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
	PWM0->ENABLE |= 0x01;       // Connect signal to the PB6 pin (PWM0EN)
}

void Servo_PB5_Init(void)
{
	// Pins 
	GPIOB->AFSEL |= 0x20;       // Enable alternate function on PB6
	GPIOB->PCTL &= ~0x00F00000; // Clear PMC6 SLOT
	GPIOB->PCTL |= 0x00400000;  // Write 4 to PMC6 to assign PWM0 to PB6
	GPIOB->DEN |= 0x20;         // Enable digital functionality on PB6
	
	
	// Parameters
	PWM0->_1_CTL &= ~0x01;      // Disable generator 0 before using
	PWM0->_1_CTL &= ~0x02;      // Select standard count down mode
	
	// ACTLOAD = 0x3 (Drive High on Load), ACTCMPAD = 0x2 (Drive Low on CMPA)
	PWM0->_1_GENB = (0x03 << 2) | (0x02 << 6); 
	
	// Set the Period 
	// 16 MHz / 64 = 250,000 ticks. 250,000 / 50 Hz = 5000 ticks.
	PWM0->_1_LOAD = 5000 - 1;
	
	// Default to Center Position (1.5ms)
	// 1.5ms = 375 ticks. 5000 - 375 = 4625.
	PWM0->_1_CMPB = 4625;
	
	// Enable
	PWM0->_1_CTL |= 0x01;       // Start timer generator 0
	PWM0->ENABLE |= 0x08;       // Connect signal to the PB6 pin (PWM0EN)
}
