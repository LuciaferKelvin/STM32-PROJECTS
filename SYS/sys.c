#include "sys.h" 
#include "usart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32F4工程模板-库函数版本
//淘宝店铺：http://mcudev.taobao.com	
//********************************************************************************
//修改说明
//无
//////////////////////////////////////////////////////////////////////////////////  


int fputc(int ch,FILE *f)
{
    uint32_t temp = ch;
 
    HAL_UART_Transmit(&huart1,(uint8_t *)&temp,1,1000);        //huart3??????
    HAL_Delay(2);
 
    return ch;
}


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
__asm void WFI_SET(void)
{
	WFI;		  
}
//关闭所有中断(但是不包括fault和NMI中断)
__asm void INTX_DISABLE(void)
{
	CPSID   I
	BX      LR	  
}
//开启所有中断
__asm void INTX_ENABLE(void)
{
	CPSIE   I
	BX      LR  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
	MSR MSP, r0 			//set Main Stack value
	BX r14
}
















