/*
 * Shift Bidirectional LED *
 * Description:
 * This program set the PORT1 as output
 * to turn on shift left LED if the PORT3
 * has a true value otherwise the shift
 * right.
 * Created by: Carlos Ibarra              *
 */
//header files
#include <at89lp6440.h>
void init(void)
{
	//P1 configured as outputcpush pull
	P1M0=0X00;
	P1M1=0XFF;
	//P3 config as input
	P3M0=0XFF;
	P3M1=0X00;
}
void delay(void)
{
	unsigned int i;
	for(i=0;i<65000;i++)
	{}
}
void main (void)
{
	bit input1;
	init();
	P1=000000001;//initialize the output
	while(1)
	{
		input1=P3_0;//Read the input PORT3_0
		//The input is pressed
		if(input1==1)
		{
			delay();
			P1=P1<<1;//shift left
			delay();
			//if has a overflow return to first value
			if (P1==128)
			{
				P1=1;//initialize the output
			}
		}
		//the input is not pressed
		else
		{
			delay();
			P1=P1>>1;//shift right
			delay();
			//if has a underflow return to last value
			if (P1==0)
			{
				P1=128;
			}
		}
	}
}
