#include "TM4C123GH6PM.h"


void Servo_PB6_Init(void)
{
	//clocks
	
	SYSCTL -> RCGCPWM |= 0x01; //enable clokc to PWM module 0
	SYSCTL -> RCGCGPIO |= 0x02; //enable clock to port B
	
	//pmw clock conguration 
	SYSCTL -> RCC |= 0x0010000; //enable the usepwdiv bit
	SYSCTL -> RCC &= ~0x000E0000; // clear the PWMDIV fiel
	SYSCTL -> RCC |= 0x00060000; // set pwmdiv to 0x3 (divides system by 16)
	//(0x03 << 17)
	

	//pins 
	
	GPIOB->AFSEL |= 0x040; //enable alternate function on PB6
	GPIOB -> PCTL &= ~0x0F000000; //CLear PMC6 SLOT
	GPIOB -> PCTL |= 0x04000000; // write 4 to PMC6 to assign PM0 to PB6
	GPIOB -> DEN |= 0x40; //enable digital functionality on PB6
	
	//parameters
	PWM0 -> _0_CTL &= ~0x01;//diable generator 0 before using
	PWM0 -> _0_CTL &= ~0x02;//select standard count down mode
	
	PWM0 -> _0_GENA = (0x03 << 2) | (0x02 << 6); // ACLOAD = 0x03 (drive high when counter reloads), ACTMPAD= 0x2 DRIVE low when counter matches CMPA
	
	//set the frequency (the period)
	//3.125 MHZ clock/50Hz target = 62,500  ticks total
	
	//set the frequency or period
	//3.125 mhz clock/ 50 hx target = 62,500 ticks
	PWM0->_0_LOAD = 62500 -1;
	
	//set the duty cycle
	//for a 1.5ms pulse which is the neutral 90 degree position
	//1.5ms is 7.5% of 20ms 7.5% of 62500 is 4,688
	//since it counts down CMPA = LOAD - HIGH ticks (62500 - 4688)
	
	PWM0 -> _0_CMPA = 57812;
	
	//enable
	
	PWM0 -> _0_CTL |= (0x01 << 0); // start timer generator 0
	PWM0 -> ENABLE |= (0x01 << 0); // connect signalto the PB6 pin (PW0EN)
	
	
	
	
	
	
	
	
	
}