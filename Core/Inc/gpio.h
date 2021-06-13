/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/


/* USER CODE BEGIN Includes */

#include "sys.h"
#include "tim.h"



/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */
#define ON 0
#define OFF 1

/* USER CODE END Private defines */



/* USER CODE BEGIN Prototypes */

typedef struct 
{
	u8 LightR;
	u8 LightG;
	u8 LightB;
	
	u16 LightH;
	u16 LightS;
	u16 LightV;
	
}LED_t;

extern LED_t LED;
void MX_GPIO_Init(void);
void HSVtoRGB(LED_t * LED);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
