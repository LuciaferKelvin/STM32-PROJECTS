/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"

/* USER CODE BEGIN 0 */
LED_t LED = {0};
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
static void HSV_ValueCheck(LED_t * LED)
{
		if(LED->LightH >= 360)
			LED->LightH %= 360;
		if(LED->LightS >= 101)
			LED->LightV %= 100;
		if(LED->LightV >= 101)
			LED->LightV %= 100;
}

void HSVtoRGB(LED_t * LED)
{
    // R,G,B from 0-255, H from 0-360, S,V from 0-100
	int i;
	float RGB_min, RGB_max;
	
	HSV_ValueCheck(LED);
	
	RGB_max =  LED->LightV*2.55f;
	RGB_min = RGB_max*(100 - LED->LightS) / 100.0f;

	i = LED->LightH / 60;
	int difs = LED->LightH % 60; // factorial part of h

										 // RGB adjustment amount by hue
	float RGB_Adj = (RGB_max - RGB_min)*difs / 60.0f;

	switch (i) {
	case 0:
			LED->LightR = (int)RGB_max;
			LED->LightG = (int)(RGB_min + RGB_Adj);
			LED->LightB = (int)RGB_min;
			break;
	case 1:
			LED->LightR = (int)(RGB_max - RGB_Adj);
			LED->LightG = (int)RGB_max;
			LED->LightB = (int)RGB_min;
			break;
	case 2:
			LED->LightR = (int)RGB_min;
			LED->LightG = (int)RGB_max;
			LED->LightB = (int)(RGB_min + RGB_Adj);
			break;
	case 3:
			LED->LightR = (int)RGB_min;
			LED->LightG = (int)(RGB_max - RGB_Adj);
			LED->LightB = (int)RGB_max;
			break;
	case 4:
			LED->LightR = (int)(RGB_min + RGB_Adj);
			LED->LightG = (int)RGB_min;
			LED->LightB = (int)RGB_max;
			break;
	default:		// case 5:
			LED->LightR = (int)RGB_max;
			LED->LightG = (int)RGB_min;
			LED->LightB = (int)(RGB_max - RGB_Adj);
			break;
	}
	
//	if(LED->LightH == 0)
//	{
////		printf("H:%d R:%d G:%d B:%d \n",LED->LightH%361,LED->LightR,LED->LightG,LED->LightB);
//		printf("%d:RGB_max:%d RGB_min:%d (RGB_max - RGB_Adj):%d\n",i,(int)RGB_max,(int)RGB_min,(int)((RGB_min + RGB_Adj)));
//	}
}

static void LED_Reflash(void)
{
	PHout(10) = LED.LightR  <  TIMER.LEDCLOCK ? OFF : ON ;
	PHout(11) = LED.LightG 	<  TIMER.LEDCLOCK ? OFF : ON ;
	PHout(12) = LED.LightB  <  TIMER.LEDCLOCK ? OFF : ON ;
}

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();


  /*Configure GPIO pins : PHPin PHPin PHPin */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(GPIOH,GPIO_PIN_10 | GPIO_PIN_11 |GPIO_PIN_12,GPIO_PIN_SET);
	
	TIMER.TIM1_FunctionsRegister(LED_Reflash);
}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
