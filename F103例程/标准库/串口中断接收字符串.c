// 串口中断服务函数
void DEBUG_USART1_IRQHandler(void)
{
 static uint8_t ucTemp[20];static int num=0;static uint8_t sign=0;
	if(USART_GetITStatus(DEBUG_USART1,USART_IT_RXNE)!=RESET)
	{		
		*(ucTemp+num) = USART_ReceiveData(DEBUG_USART1);
		if(*ucTemp!='/')
			USART_SendData(DEBUG_USART1,*(ucTemp+num));
		else
		{
			sign=1;
			
		}
		if(sign)
		{
			if(num>20)
				printf("error"),num=0,sign=0;
			num++;
			if(*(ucTemp+num-1)== '\n')
			{				
				printf("%s",ucTemp);
				for(;num>0;num--)
				*(ucTemp+num)=0;
				sign=0;
			}

		}
	}
	 USART_SendData(DEBUG_USART1,'*'); 
}
