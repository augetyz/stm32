#include "breathelight.h"

void breathelight(void)
{
	extern int m,n,i;
if(i)
{
	if(n>m)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		m++;
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		m++;
	}
	if(m==50)
	{
		n++;
		m=0;
	}
	if(n==50)
	{
		i=0;
		n=1;
		m=0;
	}
}
	
else
{
	if(n>m)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		m++;
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		m++;
	}
	if(m==50)
	{
		n++;
		m=0;
	}
	if(n==50)
	{
		i=1;
		n=1;
		m=0;
	}
}
}

