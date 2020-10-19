#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Ports_Enable.h"
#include "PWM.h"
#include "ADC.h"
#include "CN.h"
#include "PLL.h"
#include "G_Variables.h"
#include "Timer.h"

int main()
{
	//Enable all the Ports
	Ports_Enable();
	
	//Enable ADC module
	ADC0_Init();
	
	//Setting Clock Frequency to 80 MHz
	PLL_Init();
	
	//Enable Change Notification Interrupt
	EdgeInterrupt_Init();
	
	//Enable PWM module
	PWM_Init();
	
	//Enable the Timer module
	Timer3_Init(0.1);
	
	while(1);
}
