/*
 * Rotation Control DC Motor
 * Description:
 * This program control a DC motor
 * connected in a H bridge, when the External
 * interrup INT0 is active the motor goes to
 * right direction or the interruption INT1 is
 * active the motor goes to left direction.
 */
//header files
#include <at89lp6440.h>

typedef enum Motor_State_Tag
{
	MOTOR_STOP,
	MOTOR_FORWARD,
	MOTOR_REVERSE
}
Motor_State_t;

typedef enum System_Enable_Tag
{
	SYS_DISABLE,
	SYS_ENABLE
}
Sys_Enable_t;

void init(void)
{
	//P1.0, .1, .2, .3 configured as output push pull
	P1M0 &=16;
	P1M1|=15;
	//Reset the P1
	P1 = 0;
	//Enable system
	P1_4 = SYS_ENABLE;//0001 0000
	//Config External Interrup
	IT0=1; //Enable falling edge for both interrup
	IT1=1;
	//priority level
	IP |=0x01;
	IPH|=0x05;
	//Enable interrupt
	EX0=1;
	EX1=1;
	EA=1;
}
void stop(void)
{
	P1_0=0;
	P1_1=0;
	P1_2=1;
	P1_3=1;
}
void forward(void)
{
	P1_0=1;
	P1_1=0;
	P1_2=0;
	P1_3=1;
}
void reverse(void)
{
	P1_0=0;
	P1_1=1;
	P1_2=1;
	P1_3=0;
}
void delay(void)
{
	unsigned int i;
	for(i=0;i<65000;i++)
	{}
}
Motor_State_t Motor_State = MOTOR_STOP;
//Initialize the Motor State in STOP
void main(void)
{
	init();
	while(1)
	{
			if(P1_4==SYS_ENABLE)
			{	
				//PCON |=0x01;
				delay();
			}
			else
			{
				stop();
			}
	}
}
//ISR to External Interrup INT0
void INT0_Int(void) interrupt 0
{
	if (P1_4 == SYS_ENABLE)
	{
		if ((Motor_State == MOTOR_REVERSE) || (Motor_State == MOTOR_STOP))
		{
			stop();
			delay();
			delay();
			forward();
			Motor_State = MOTOR_FORWARD;
		}
		else
		{
			//remaing the same state
		}
	}
	else
	{
		stop();
	}
}
void INT1_Int(void) interrupt 2
{
	if (P1_4 == SYS_ENABLE)
	{
		if ((Motor_State == MOTOR_FORWARD) || (Motor_State == MOTOR_STOP))
		{
			stop();
			delay();
			delay();
			reverse();
			Motor_State = MOTOR_REVERSE;
		}
		else
		{
			//remain the same state
		}
	}
	else
	{
		stop();
	}
}
