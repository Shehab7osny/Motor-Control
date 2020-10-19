#include <stdint.h>
#include "tm4c123gh6pm.h"

void PWM_Init()
{
	SYSCTL_RCGCPWM_R |= 0x01;
	
	SYSCTL_RCC_R &= ~(1 << 20);
	
	GPIO_PORTB_DIR_R |= 0xF0;
	GPIO_PORTE_DIR_R |= 0x30;
	
	GPIO_PORTB_AFSEL_R |= 0xF0;
	GPIO_PORTE_AFSEL_R |= 0x30;
	
	GPIO_PORTB_PCTL_R = (GPIO_PORTF_PCTL_R & 0x0000FFFF) | (0x44440000);
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R & 0xFF00FFFF) | (0x00440000);
	
	GPIO_PORTB_DEN_R |= 0xF0;
	GPIO_PORTE_DEN_R |= 0x30;
	
	PWM0_0_CTL_R &= ~0x03;
	PWM0_1_CTL_R &= ~0x03;
	PWM0_2_CTL_R &= ~0x03;
	
	PWM0_0_GENA_R = 0x8C;
	PWM0_0_GENB_R = 0x80C;
	PWM0_1_GENA_R = 0x8C;
	PWM0_1_GENB_R = 0x80C;
	PWM0_2_GENA_R = 0x8C;
	PWM0_2_GENB_R = 0x80C;
	
	PWM0_0_LOAD_R = 8000 - 1;
	PWM0_1_LOAD_R = 8000 - 1;
	PWM0_2_LOAD_R = 8000 - 1;
	
	PWM0_0_CMPA_R = 8000 - 1;
	PWM0_0_CMPB_R = 8000 - 2;
	PWM0_1_CMPA_R = 8000 - 1;
	PWM0_1_CMPB_R = 8000 - 2;
	PWM0_2_CMPA_R = 8000 - 1;
	PWM0_2_CMPB_R = 8000 - 2;
	
	PWM0_0_CTL_R |= 0x01;
	PWM0_1_CTL_R |= 0x01;
	PWM0_2_CTL_R |= 0x01;
	
	PWM0_ENABLE_R = 0x00;
}

void SetDutyCycle(int duty_cycle)
{
	if(duty_cycle >= 100)
	{
		PWM0_0_CMPB_R = 8000 - 1;
		PWM0_1_CMPB_R = 8000 - 1;
		PWM0_2_CMPB_R = 8000 - 1;
	}
	
	else if(duty_cycle <= 0)
	{
		PWM0_0_CMPB_R = 8000 - 2;
		PWM0_1_CMPB_R = 8000 - 2;
		PWM0_2_CMPB_R = 8000 - 2;
	}
		
	else
	{
		PWM0_0_CMPB_R = (uint16_t)((8000 - ((8000 * duty_cycle) / 100)) - 1);
		PWM0_1_CMPB_R = (uint16_t)((8000 - ((8000 * duty_cycle) / 100)) - 1);
		PWM0_2_CMPB_R = (uint16_t)((8000 - ((8000 * duty_cycle) / 100)) - 1);
	}
}
