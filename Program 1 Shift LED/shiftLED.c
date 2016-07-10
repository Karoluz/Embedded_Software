/*  Shift LED  *
 * Description *
 * This program set the PORT1 to output   *
 * to turn on shift left LED if the PORT3 *
 * has a true value otherwise the shift   *
 * right is set to PORT1                 *
 * Created by: Carlos Ibarra              *
 */
//header files
#include <at89lp6440.h>
void init(void)
{
	//P1 port 1 configured as output push pull
	P1M0=0X00;
	P1M1=0XFF;
	//P3 port3 configured as input
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
	//Start Port1 with value 1
	P1=00000001;
	while(1)
	{
		//read the port3
		input1=P3_0;
		//If port3 is equal to 1
		if(input1==1)
		{
			//left shift bit to port1
			P1=P1<<1;
			delay();
			//if shift bit finish return to firs value
			if (P1==128)
			{
				P1=1;
			}
		}
		else
		{
			//right shift bit to port1
			P1=P1>>1;
			delay();
			if (P1==0)
			{
				P1=128;
			}
		}
	}
}