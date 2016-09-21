
#include <stddef.h>
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_flash.h"
#include "misc.h"

#define STM32F10X_LD_VL
void delay(__IO uint32_t ncount);
//void SetSysClockHSI(void);
int led=0;
void init(void)
{
	GPIO_InitTypeDef gpio;
	EXTI_InitTypeDef exti;
	NVIC_InitTypeDef nvic;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	gpio.GPIO_Pin=GPIO_Pin_0;
	gpio.GPIO_Mode=GPIO_Mode_IPU;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);

	gpio.GPIO_Pin=GPIO_Pin_1;
	gpio.GPIO_Mode=GPIO_Mode_Out_PP;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_Pin_0);
	exti.EXTI_Line=EXTI_Line0;
	exti.EXTI_LineCmd=ENABLE;
	exti.EXTI_Mode=EXTI_Mode_Interrupt;
	exti.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&exti);

	NVIC_SetVectorTable(NVIC_VectTab_FLASH,0x00);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	nvic.NVIC_IRQChannel=EXTI0_IRQn;
	nvic.NVIC_IRQChannelCmd=ENABLE;
	nvic.NVIC_IRQChannelPreemptionPriority=0;
	nvic.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&nvic);
}

int main(void)
{
	//SetSysClockHSI();
//	SystemInit();
	init();
	for (led = 0; led <= 5;led++) {
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		delay(250);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		delay(250);
	}

  while (1)
  {

	  GPIO_ResetBits(GPIOA,GPIO_Pin_1);
  }
}/*
void SetSysClockHSI(void)
{
	(*((int*)0xE000ED88))|=0x0F00000;
	for (i=0;i<0x00100000;i++);
	RCC->CR |=0x01010000;
	RCC->CFGR |= 0x043D1C00;
	//burada kaldýk
	while (!(RCC->CR & 0x00020000));


}*/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetFlagStatus(EXTI_Line0) !=RESET){
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	delay(500);
	EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void delay(__IO uint32_t num)
{
	__IO uint32_t icindeki=0;
	for(icindeki=(7200*num);icindeki!=0;icindeki--)
	{}
}

