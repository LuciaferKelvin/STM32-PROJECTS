/**
  ******************************************************************************
  * @file    tim.c
  * @brief   This file provides code for the configuration
  *          of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */

void ( * FuncitonRegister[MAXCALLBACKNUM])(void) = {NULL};


TIMER_t TIMER = {
									.CLOCK10NS = 0,
									.TIM_FunctionsCNT = 0,
									.TIM1_FunctionsRegister = TIMER_FunctionsRegister,
	
								};

static void TIMER_FunctionsCallBack(void(* funcions)(void))
{
	funcions();
}
void TIM1_FunctionsAllCallBack(void)
{
	for(int i = 0 ; i < TIMER.TIM_FunctionsCNT; i ++)
	{
		TIMER_FunctionsCallBack(FuncitonRegister[i]);
	}
}

void TIMER_FunctionsRegister(void(*Functions)(void))
{
	if(TIMER.TIM_FunctionsCNT > MAXCALLBACKNUM)
	{
		printf("ERROR REGISTER ----------------  FULL\n");
		return;
	}
	FuncitonRegister[TIMER.TIM_FunctionsCNT] = Functions;
	printf("PASS REGISTER ----------------  PASS\n");
	TIMER.TIM_FunctionsCNT++;
}



/* USER CODE END 0 */



/* TIM1 init function */
void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_SlaveConfigTypeDef sSlaveConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  TIMER.HAL_TIM1.Instance = TIM1;
  TIMER.HAL_TIM1.Init.Prescaler = 179;
  TIMER.HAL_TIM1.Init.CounterMode = TIM_COUNTERMODE_UP;
  TIMER.HAL_TIM1.Init.Period = 10;
  TIMER.HAL_TIM1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  TIMER.HAL_TIM1.Init.RepetitionCounter = 0;
  TIMER.HAL_TIM1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&TIMER.HAL_TIM1) != HAL_OK)
  {
//    Error_Handler();
  }
  sSlaveConfig.SlaveMode = TIM_SLAVEMODE_DISABLE;
  sSlaveConfig.InputTrigger = TIM_TS_ITR0;
  if (HAL_TIM_SlaveConfigSynchro(&TIMER.HAL_TIM1, &sSlaveConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&TIMER.HAL_TIM1, &sMasterConfig) != HAL_OK)
  {
//    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspInit 0 */

  /* USER CODE END TIM1_MspInit 0 */
    /* TIM1 clock enable */
    __HAL_RCC_TIM1_CLK_ENABLE();

    /* TIM1 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 2, 1);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM1_MspInit 1 */

  /* USER CODE END TIM1_MspInit 1 */
  }
}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM1)
  {
  /* USER CODE BEGIN TIM1_MspDeInit 0 */

  /* USER CODE END TIM1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM1_CLK_DISABLE();

    /* TIM1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM1_MspDeInit 1 */

  /* USER CODE END TIM1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  if(htim->Instance == TIM1)
	{
		TIMER.CLOCK10NS++;
		TIMER.CLOCK10NS %= 100000;
		
		TIMER.LEDCLOCK++;
		TIMER.LEDCLOCK %= 256;
		
		TIM1_FunctionsAllCallBack( );
		
	}
}

/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
