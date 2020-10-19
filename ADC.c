#include "tm4c123gh6pm.h"

extern unsigned int ADC_Offset;

void ADC0_Init()
{
	GPIO_PORTE_DIR_R   &= ~0x08;						// Input of Throttle is PE3 Pin
	GPIO_PORTE_DEN_R   &= ~0x08;						// Disable Digital I/O on PE4
	GPIO_PORTE_AFSEL_R |= 0x08;						// Enable Alternative Function to Pin PE4
	GPIO_PORTE_AMSEL_R |= 0x08;						// Enable Analog Function to Pin PE4
	
	SYSCTL_RCGC0_R  |= 0x10000;						// Activate ADC0 module
	SYSCTL_RCGC0_R  &= ~0x0300;						// Set the ADC0 Sampling Speed to 125K Samples/Second
	
	ADC0_SSPRI_R 	 = 0x0123;						// Sample Sequencer 3 (SS3) is highest priority
	ADC0_ACTSS_R	&= ~0x08;						// Disable Sample Sequencer 3 (SS3)
	ADC0_EMUX_R	&= ~0xF000;
	ADC0_SSMUX3_R	&= ~0x000F;
	ADC0_SSMUX3_R 	+= 0;
	ADC0_SSCTL3_R 	= 0x0006;
	ADC0_IM_R &	= ~0x0008;
	ADC0_ACTSS_R	|= 0x08;
	
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R & 0x08) == 0);
	ADC_Offset = (ADC0_SSFIFO3_R & 0xFFF) + 30;
	ADC0_ISC_R = 0x0008;
}

unsigned long ADC_Result()
{
	unsigned long Result;
	ADC0_PSSI_R = 0x0008;
	while((ADC0_RIS_R & 0x08) == 0);
	Result = ADC0_SSFIFO3_R & 0xFFF;
	ADC0_ISC_R = 0x0008;
	return Result;
}
