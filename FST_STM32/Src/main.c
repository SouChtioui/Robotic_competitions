/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;
TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM5_Init(void);
static void MX_TIM1_Init(void);
static void MX_TIM4_Init(void);

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void motorR_forward(uint32_t motor_speed);
void motorR_backward(uint32_t motor_speed);
void motorR_stop(void);
void motorL_forward(uint32_t motor_speed);
void motorL_backward(uint32_t motor_speed);
void motorL_stop(void);
void FWD(uint32_t motorR_speed,uint32_t motorL_speed);
void BWD(uint32_t motorR_speed,uint32_t motorL_speed);
void TurnL(int32_t motorR_speed,int32_t motorL_speed);
void TurnR(int32_t motorR_speed,int32_t motorL_speed);
void TurnLPro(int32_t motorR_speed,int32_t motorL_speed);
void TurnRPro(int32_t motorR_speed,int32_t motorL_speed);
void stop(void);
void readSensors(void);
void suiveur(void);
//************************************************************ MY Variables ****************************************************** 
//************************************************************ MY Variables ****************************************************** 
//************************************************************ MY Variables ****************************************************** 

bool L,CL,CR,R,C,XL,XR; // my sensors
bool reverse_line_color=false;
bool enable_TurnLPro=true;
bool enable_TurnRPro=false;
bool interrupted_line=false;
bool interrupted_line_done=false;
bool first_turn_after_9alba=true;
int32_t right_ticks=0;
int32_t left_ticks=0;
int32_t previous_right_ticks=0;
int32_t previous_left_ticks=0;
int32_t Rticks_diff=0;
int32_t Lticks_diff=0;
uint16_t right_speed=290;
uint16_t left_speed=330;
int16_t right_error=0;
int16_t left_error=0;
uint16_t desired_speed=55;
uint8_t kp=5;
uint16_t previous_time=0;
uint16_t change_line_time_mark=0;

//************************************************************ END OF MY VARIABLES ****************************************************** 
//************************************************************ END OF MY VARIABLES ****************************************************** 
//************************************************************ END OF MY VARIABLES ****************************************************** 

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();


  /* Configure the system clock */
  SystemClock_Config();


  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM5_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim5,TIM_CHANNEL_ALL);
  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	/*************************************************************my loop**********************************************************************/
	/*************************************************************my loop**********************************************************************/
	/*************************************************************my loop**********************************************************************/

while (1)
  {
		suiveur();
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
	
	/*******************************************************end of my loop**********************************************************************/
	/*******************************************************end of my loop**********************************************************************/
	/*******************************************************end of my loop**********************************************************************/
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 16000;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{


  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 0xFFFFFFFF;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim2, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{


  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 16;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 16;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1000;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim4);

}

/**
  * @brief TIM5 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM5_Init(void)
{

  TIM_Encoder_InitTypeDef sConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 0;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 0xFFFFFFFF;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sConfig.EncoderMode = TIM_ENCODERMODE_TI1;
  sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC1Filter = 0;
  sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
  sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
  sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
  sConfig.IC2Filter = 0;
  if (HAL_TIM_Encoder_Init(&htim5, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MR_FWD_Pin|ML_FWD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, MR_BWD_Pin|ML_BWD_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : MR_FWD_Pin ML_FWD_Pin */
  GPIO_InitStruct.Pin = MR_FWD_Pin|ML_FWD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MR_BWD_Pin ML_BWD_Pin */
  GPIO_InitStruct.Pin = MR_BWD_Pin|ML_BWD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Left_Pin */
  GPIO_InitStruct.Pin = Left_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(Left_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : CLeft_Pin CRight_Pin Right_Pin Centre_Pin 
                           XLeft_Pin XRight_Pin */
  GPIO_InitStruct.Pin = CLeft_Pin|CRight_Pin|Right_Pin|Centre_Pin 
                          |XLeft_Pin|XRight_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
//************************************************************ MY Functions ****************************************************** 
//************************************************************ MY Functions ****************************************************** 
//************************************************************ MY Functions ****************************************************** 

void readSensors(void) //************************************************************************** readSensors 
{
	L=HAL_GPIO_ReadPin(Left_GPIO_Port,Left_Pin);
	CL=HAL_GPIO_ReadPin(CLeft_GPIO_Port,CLeft_Pin);
	CR=HAL_GPIO_ReadPin(CRight_GPIO_Port,CRight_Pin);
	R=HAL_GPIO_ReadPin(Right_GPIO_Port,Right_Pin);
	C=!HAL_GPIO_ReadPin(Centre_GPIO_Port,Centre_Pin);
	XL=!HAL_GPIO_ReadPin(XLeft_GPIO_Port,XLeft_Pin);
	XR=!HAL_GPIO_ReadPin(XRight_GPIO_Port,XRight_Pin);
	if (!reverse_line_color)
	{
		L=!L;
		CL=!CL;
		CR=!CR;
		R=!R;
		C=!C;
		XL=!XL;
		XR=!XR;
	}
}

void motorR_forward(uint32_t motor_speed)
{
	HAL_GPIO_WritePin(MR_FWD_GPIO_Port,MR_FWD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MR_BWD_GPIO_Port,MR_BWD_Pin,GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	TIM4->CCR2=motor_speed;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}
void motorR_backward(uint32_t motor_speed)
{
	HAL_GPIO_WritePin(MR_FWD_GPIO_Port,MR_FWD_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MR_BWD_GPIO_Port,MR_BWD_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	TIM4->CCR2=motor_speed;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}
void motorR_stop(void)
{
	HAL_GPIO_WritePin(MR_FWD_GPIO_Port,MR_FWD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(MR_BWD_GPIO_Port,MR_BWD_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_2);
	TIM4->CCR2=0;
	HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
}

void motorL_forward(uint32_t motor_speed)
{
	HAL_GPIO_WritePin(ML_FWD_GPIO_Port,ML_FWD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(ML_BWD_GPIO_Port,ML_BWD_Pin,GPIO_PIN_RESET);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	TIM3->CCR2=motor_speed;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
}
void motorL_backward(uint32_t motor_speed)
{
	HAL_GPIO_WritePin(ML_FWD_GPIO_Port,ML_FWD_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(ML_BWD_GPIO_Port,ML_BWD_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	TIM3->CCR2=motor_speed;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
}
void motorL_stop(void)
{
	HAL_GPIO_WritePin(ML_FWD_GPIO_Port,ML_FWD_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(ML_BWD_GPIO_Port,ML_BWD_Pin,GPIO_PIN_SET);
	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
	TIM3->CCR2=0;
	HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
}

void FWD(uint32_t motorR_speed,uint32_t motorL_speed)
{
	motorR_forward(motorR_speed);
	motorL_forward(motorL_speed);
}
void BWD(uint32_t motorR_speed,uint32_t motorL_speed)
{
	motorR_backward(motorR_speed);
	motorL_backward(motorL_speed);
}

void TurnL(int32_t motorR_speed,int32_t motorL_speed)
{
	if(motorL_speed>0)
	{
		motorL_forward(motorL_speed);
	}
	else
	{
		motorL_backward(-motorL_speed);
	}
	motorR_forward(motorR_speed);
}
void TurnR(int32_t motorR_speed,int32_t motorL_speed)
{
	if(motorR_speed>0)
	{
		motorR_forward(motorR_speed);
	}
	else
	{
		motorR_backward(-motorR_speed);
	}
	motorL_forward(motorL_speed);
}

void TurnLPro(int32_t motorR_speed,int32_t motorL_speed) //****************************************** TurnLPro
{
	TIM2->CNT=0;
	TIM5->CNT=0;	
	while(TIM5->CNT<150) /*********************** imin *************************/
	{
		TurnR(0,300);
	}
	readSensors(); 
	if(XL && XR) /**************************************************** 9alba ****************************/
	{
		if(reverse_line_color)
		{
			stop();
			while(1)
			{
				
			}
		}
		else
		{
		reverse_line_color=true;
		change_line_time_mark=TIM1->CNT;
		}
	}
	else
	{
		if(first_turn_after_9alba && reverse_line_color)
		{
			interrupted_line_done=false;
			first_turn_after_9alba=false;
		}
		if(motorL_speed>0)
		{
			motorL_forward(motorL_speed);
		}
		else
		{
			motorL_backward(-motorL_speed);
		}
		motorR_forward(motorR_speed);
		while(!C)/****************************************************************** dour issar ********/
		{
			readSensors();
		}
		TurnR(-250,250);/******************************************************************** dour imin ********/
		HAL_Delay(50);	
	}
}
void TurnRPro(int32_t motorR_speed,int32_t motorL_speed) //****************************************** TurnRPro
{
	TIM2->CNT=0;
	TIM5->CNT=0;	
	
	while(TIM2->CNT<150)/*********************** issar ************************/
	{
		TurnL(300,0);
	}
	readSensors(); 
	if(XL && XR) /**************************************************** 9alba ****************************/
	{
		if(reverse_line_color)
		{
			stop();
			while(1)
			{
				
			}
		}
		else
		{
		reverse_line_color=true;
		change_line_time_mark=TIM1->CNT;
		}
	}
	else
	{
		if(first_turn_after_9alba && reverse_line_color)
		{
			interrupted_line_done=false;
			first_turn_after_9alba=false;
		}
		if(motorR_speed>0)
		{
			motorR_forward(motorR_speed);
		}
		else
		{
			motorR_backward(-motorR_speed);
		}
		motorL_forward(motorL_speed);
			while(!C) /******************************************************************** dour imin ********/
		{
			readSensors();
		}
		TurnL(250,-250); /************************************************************* dour issar **********/
		HAL_Delay(50);		
	}
}
void stop(void)
{
	motorR_stop();
	motorL_stop();
}

/******************************************************* Suiveur **********************************************************************/
/******************************************************* Suiveur **********************************************************************/
/******************************************************* Suiveur **********************************************************************/
/******************************************************* Suiveur **********************************************************************/
/******************************************************* Suiveur **********************************************************************/

void suiveur(void)
{
	readSensors(); 
	if(XL && XR) /**************************************************** 9alba ****************************/
	{
		if(reverse_line_color)
		{
			stop();
			while(1)
			{
				
			}
		}
		else
		{
		interrupted_line_done=false;
		reverse_line_color=true;
		change_line_time_mark=TIM1->CNT;
		}
	}
	else if(!L && !CL && !CR && !R && C && !interrupted_line_done) /**************************************************** interrompu ****************************/
	{
		interrupted_line=true;
	}
	//else if(XL && enable_TurnLPro)
	else if(XL) /**************************************************** doura isssar pro ****************************/
	{
		if(interrupted_line)
		{
			interrupted_line=false;
		}
			enable_TurnLPro=false;
			TurnLPro(250,-250);
	}
	//else if(XR && enable_TurnRPro)
	else if(XR) /**************************************************** doura imin pro ****************************/
	{
		if(interrupted_line)
		{
			interrupted_line=false;
			interrupted_line_done=true;
		}		
			enable_TurnRPro=false;
			TurnRPro(-250,250);
	}
	else if(L && !R) /**************************************************** doura issar ****************************/
	{		
			TurnL(350,0);
	}	
	else if(!L && R) /**************************************************** doura imin ****************************/
	{
			TurnR(0,350);
	}
	else if(!XL && !L && !CL && !CR && !R && !XR && !C && !interrupted_line) /******** arb3a byodh *******/
	{
		while(!XL && !L && !CL && !CR && !R && !XR && !C)
		{
			readSensors();
			BWD(300,300);
		}
		HAL_Delay(200);
	}
	else if(!L && CL && !CR && !R) /************************************************ tasli7 issar ***************************/
	{
		int i=0;
		while(!L && CL && !CR && !R)
		{
			if(right_speed+i<330)
			{
				i++;
			}
			FWD(right_speed+i,left_speed);
			readSensors();
		}
	}
	else if(!L && !CL && CR && !R) /************************************************ tasli7 imin ***************************/
	{
		int i=0;
		while(!L && !CL && CR && !R)
		{
			if(left_speed+i<370)
			{
				i++;
			}
			FWD(right_speed,left_speed+i);
			readSensors();
		}
	}
	else
		{
			FWD(right_speed,left_speed);
		}
}

/*********************************************************** Fin Suiveur **********************************************************************/
/*********************************************************** Fin Suiveur **********************************************************************/
/*********************************************************** Fin Suiveur **********************************************************************/
/*********************************************************** Fin Suiveur **********************************************************************/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
/* asservissement
			Rticks_diff=TIM2->CNT-right_ticks;
			Lticks_diff=TIM5->CNT-left_ticks;
			right_ticks=TIM2->CNT;
			left_ticks=TIM5->CNT;
			right_error=Rticks_diff-desired_speed;
			left_error=Lticks_diff-desired_speed;
			right_speed=right_speed-kp*right_error;
			left_speed=left_speed-kp*left_error;
			
			if(right_speed>400)
			{
				right_speed=400;
			}
			else if(right_speed<200)
			{
				right_speed=200;
			}
			if(left_speed>400)
			{
				left_speed=400;
			}
			else if(left_speed<200)
			{
				left_speed=200;
			}
			fin asservissement */
}

//****************************************************** END OF MY Functions ****************************************************** 
//****************************************************** END OF MY Functions ****************************************************** 
//****************************************************** END OF MY Functions ****************************************************** 

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
