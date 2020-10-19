#include "tm4c123gh6pm.h"

void Ports_Enable(void)
{
	SYSCTL_RCGCGPIO_R |= 0x3F;											//Enable the Clock to all the Ports (A, B, C, D, E & F)
	while((SYSCTL_PRGPIO_R & 0x0000003F) == 0);			//
	
	GPIO_PORTF_DIR_R |= 0x02;
	GPIO_PORTF_DEN_R |= 0x02;
	
	GPIO_PORTF_DIR_R |= 0x08;
	GPIO_PORTF_DEN_R |= 0x08;
}
