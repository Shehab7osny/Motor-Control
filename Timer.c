#include "tm4c123gh6pm.h"

extern int Heart_Beat;                                  //counter to toggle led every second 
                                
extern volatile int RPM;                                //actual speed
extern volatile int Duty_Cycle;                                //actual speed
extern volatile int SpeedCalc;                          //how often cn is entered every second
extern volatile int DesiredSpeed;                       //throttle
extern volatile int Max_Speed;                          //620

extern volatile unsigned int HallValue;                 //to get hall sensor readings
extern volatile unsigned int State_Table[];      //state table
extern unsigned int ADC_Offset;
extern unsigned int ADC_Value;
extern unsigned long ADC_Result(void);
extern void SetDutyCycle(int duty_cycle);

void Timer3_Init(float Period)
{
	SYSCTL_RCGCTIMER_R |= 0x08;					// Timer3 = 1 0 0 0 = 0x08
	TIMER3_CTL_R   = 0x00000000;					// Initially Disable the timer
	TIMER3_CFG_R   = 0x00000000;					// 32-bit Timer
	TIMER3_TAMR_R  = 0x00000002;					// Periodic Mode (Not One Shot)
	TIMER3_TAILR_R = (Period * 80000000) - 1;					// Period = (Delay Time Needed in seconds) / (12.5 x 10^-9)
	TIMER3_TAPR_R  = 0x00000000;					// Decrement 1 in the previous line every clock cycle (as default)
	TIMER3_ICR_R   = 0x00000001;					// Clear Flag
	TIMER3_IMR_R   = 0x00000001;					// Ready to execute an interrupt
	NVIC_PRI8_R    = (NVIC_PRI8_R & 0x00FFFFFF) | 0x80000000;	// Priority = 4
	NVIC_EN1_R     = 1 << (35-32);
	TIMER3_CTL_R   = 0x00000001;
}

void TIMER3A_Handler()
{
	TIMER3_ICR_R   = 0x01;
	
	Heart_Beat++; 
	
	
	if(Heart_Beat == 10)
	{
		GPIO_PORTF_DATA_R ^= 0x02;
		Heart_Beat = 0;
	}
	
	RPM = (((float)(SpeedCalc)*(10))/138)*60;                           //Actual Speed Calculation
	
	SpeedCalc = 1;                                                      //Reset SpeedCalc

	ADC_Value = ADC_Result();

	if(ADC_Value > ADC_Offset)
	{
		HallValue = (GPIO_PORTA_DATA_R & 0x1C) >> 2;
		
		PWM0_ENABLE_R = State_Table[HallValue];
		
		DesiredSpeed = ((float)Max_Speed/(4095 - ADC_Offset))*(ADC_Value - ADC_Offset);
		
		Duty_Cycle = (ADC_Result() * 100) / 4095;
		
		SetDutyCycle(Duty_Cycle);
	}
	
	else
	{
		DesiredSpeed = 0;
		PWM0_ENABLE_R = 0x00;
	}
}
