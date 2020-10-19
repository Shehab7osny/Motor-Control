#ifndef G_VARIABLES_H
#define	G_VARIABLES_H

int HallValue;
int Heart_Beat = 0;
int Duty_Cycle = 0;
int RPM;
int Max_Speed = 620;
int SpeedCalc = 0;
volatile int DesiredSpeed = 0;
unsigned int ADC_Offset;
unsigned int ADC_Value = 0;
int RunningFlag = 1;
unsigned int State_Table[] = {0x00, 0x21, 0x06, 0x24, 0x18, 0x09, 0x12, 0x00};

#endif
