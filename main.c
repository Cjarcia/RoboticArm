//The main for PWM Example with PB6 for PWM, duty cycle is 50%
//PB6 is connected to PWM module 0
//sytem clock is 16MHz
#include "TM4C123GH6PM.h"
void delayMs(int n);

int main(void){
//make pulses 
//gpio conifiguration
	SYSCTL -> RCGCGPIO |= 0x20; //enable port F clock
	SYSCTL -> RCGCPWM |= 0x02; //enable clock to PWM1
	SYSCTL -> RCC &= ~0x000E0000;//clear divider
	//we will be using systemclk/64
	SYSCTL -> RCC |= 0x001A0000; //set bit 20 for system clock/64
	GPIOF -> AFSEL |= 0x08; //PF3 uses PWM7 apart of generator 3
	GPIOF -> PCTL &= ~0x0000F000; 
	GPIOF -> PCTL |= 0x00005000; 
	GPIOF -> DEN |= 0x08;
	 
	//PWM Configuration
	PWM1 -> _3_CTL = 0; //disable PWM block for configuration, count down mode
	//make load up point and comparator down point by setting 0x2 to bit 7 6 and 0x3 to bits 3 2
	PWM1 -> _3_GENB &= ~0x00000FFF;
	PWM1 -> _3_GENB |= 0x0000080C;
	PWM1->_3_LOAD = 5000-1;       // 20 ms period = 50 Hz
  //PWM1->_3_CMPB = 5000 - 250;           // 1.5ms pulse position 0

  PWM1->_3_CTL = 1;               // enable counter
  PWM1->ENABLE |= 0x80;           // enable PWM7 output
	
	while(1){
	PWM1->_3_CMPB = 4750;   // ~1.0 ms
	delayMs(1000);

	PWM1->_3_CMPB = 4625;   // ~1.5 ms
	delayMs(1000);

	PWM1->_3_CMPB = 4500;   // ~2.0 ms
	delayMs(1000);
}

}
	void delayMs(int n){
	
		int i,j;
		for(i = 0; i<n; i++){
			for(j=0; j<3000; j++){
				//do nothing
			}
		
		}
	}
	
