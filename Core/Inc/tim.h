/**
  ******************************************************************************
  * @file    tim.h
  * @brief   This file contains all the function prototypes for
  *          the tim.c file
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/



/* USER CODE BEGIN Includes */
#include "sys.h"

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define MAXCALLBACKNUM  10

/* USER CODE END Private defines */

void MX_TIM1_Init(void);

/* USER CODE BEGIN Prototypes */
typedef struct
{
	/**********CountClockDefine***************/
	volatile u32 CLOCK10NS;
	volatile u16 LEDCLOCK;
	
	/*************END*******************************/
	TIM_HandleTypeDef HAL_TIM1;
	
/******************ifuse uncomment*******************/
//	TIM_HandleTypeDef HAL_TIM2;
//	TIM_HandleTypeDef HAL_TIM3;
//	TIM_HandleTypeDef HAL_TIM4;
//	TIM_HandleTypeDef HAL_TIM5;
//	TIM_HandleTypeDef HAL_TIM6;
//	TIM_HandleTypeDef HAL_TIM7;
	
/***********Register funcitons and using it when TIM1 has updateflag**************/
	void (* TIM1_FunctionsRegister)(void(*Functions)(void));
	
	int TIM_FunctionsCNT;
	
	
	
}TIMER_t;

extern TIMER_t TIMER;

void TIMER_FunctionsRegister(void(*Functions)(void));
void TIM1_FunctionsAllCallBack(void);
void TIME_TEST(void);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
