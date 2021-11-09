#include "tm4c123gh6pm.h"

extern int SpeedCalc;
extern int RunningFlag;
extern unsigned int HallValue;
extern unsigned int ADC_Offset;
extern unsigned int State_Table[];
extern unsigned long ADC_Result(void);

void EdgeInterrupt_Init(void)
{
	//Hall Sensors are connected to Pins PA2, PA3 & PA4 (Set those pins as Input Pins)
	GPIO_PORTA_DIR_R   &= ~0x1C;
	
	//Set those Input Pins to be Digital
	GPIO_PORTA_DEN_R   |= 0x1C;
	
	//Disable Alternative Function to those Pins
	GPIO_PORTA_AFSEL_R &= ~0x1C;
	
	//Disable Analog Function to those Pins
	GPIO_PORTA_AMSEL_R &= ~0x1C;
	
	//Configure Hall Sensor Pins (PA2, PA3 & PA4) as GPIO Pins
	GPIO_PORTA_PCTL_R  &= ~0x000FFF00;
	
	//Enable the Internal Pullup Resistors for Hall Sensor Pins (PA2, PA3 & PA4)
	//GPIO_PORTA_PUR_R   |= 0x1C;
	
	//Set the Interrupt to be an Edge-Triggered
	GPIO_PORTA_IS_R    &= ~0x1C;
	
	//Interrupt Triggers on Both Edges (Rising & Falling Edge)
	GPIO_PORTA_IBE_R   |= 0x1C;
	
	//Clear the Interrupt Acknowledgement bit
	GPIO_PORTA_ICR_R    = 0x1C;
	
	//Set the Hall Sensor Pins (PA2, PA3 & PA4) to be ready to execute the interrupt
	GPIO_PORTA_IM_R     = 0x1C;

	//Interrput Properties Configuration
	
	//Set the Highest Priority for this Interrupt (Priority 0)
	NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF0F) | 0x00000000;
	
	//Enable Interrupt of Port A (IRQ Number = Bit Number 0)
	NVIC_EN0_R = 0x00000001;
}

void GPIOA_Handler(void)
{
	//Check that Interrupt is triggered because of Hall Sensors
	if((GPIO_PORTA_RIS_R & 0x1C) != 0)
	{
		//Clear the Interrupt Acknowledgement bit
		GPIO_PORTA_ICR_R    = 0x1C;
	
		SpeedCalc++;
		
		HallValue = (GPIO_PORTA_DATA_R & 0x1C) >> 2;
		
		if(!RunningFlag)
			PWM0_ENABLE_R = 0x00;
		
		else if((ADC_Result() > ADC_Offset) && (RunningFlag))
			PWM0_ENABLE_R = State_Table[HallValue];
	}
}
