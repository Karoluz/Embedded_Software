/*
 * Alarm using a Timer Interrupt
 *
 * Description: Configure the micro to enable the
 * timer interrupt when the timer expire the alarm is set
 * an output in high that indicate the alarm is active.
 * 
 * Created by: Carlos Ibarra
 */
 
//header files
#include <at89lp6440.h>

typedef enum Timer_State_Tag
{
	TIMER_OFF,
	TIMER_ON
}
Timer_State_T;

typedef enum Alarm_State_Tag
{
	ALARM_DEACTIVE,
	ALARM_ACTIVE
}
Alarm_State_T;

unsigned int count;
void init(void)
{
	//Port 1_0 configured as output
	P1M0 &=0XFE;
	P1M1 |=0X01;
	//Priority
	IP |= 0x09; 
	IPH |= 0x0D;
	//Mode o for timer 1
	TMOD &=0X0F; //00001111
	//Enable Timer Interrupt
	ET1=1;
	//Initialize the Port 1_0
	P1_0 = 0;
	count = 0; //Initialize the counter
	IT0=1; //filo de bajada falling edge
	IT1=1;
	//Enable the interrupts
	EX0=1;
	EX1=1;
	EA=1;
	TR1 = TIMER_OFF; //Set timer/counter OFF
	TCONB =0x38;//Set the prescaler 8-bit
	CLKREG=0x00;
}
void main(void)
{
	init();
	while(1)
	{
		PCON |=0x01;
	}
}
void INT_Timer1(void) interrupt 3
{
	count ++;//increment the counter
	if(count == 1832)//10 second
	{
		P1_0 = ALARM_ACTIVE; //Active the Alarm
		TR1 = TIMER_OFF;  //Reset the timer
	}
}

void INT0_Int(void) interrupt 0 
{
		count = 0;//Reset the counter
		TR1 = TIMER_ON;  //Initialize the timer
	
}
void INT1_Int(void) interrupt 2
{
		TR1 = TIMER_OFF;  //Reset the timer
		P1_0 = ALARM_DEACTIVE; //Reset the Alarm
}
