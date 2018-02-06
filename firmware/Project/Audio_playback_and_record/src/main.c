/**
  ******************************************************************************
  * @file    Audio_playback_and_record/src/main.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    28-October-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include <stdio.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
/** @addtogroup STM32F4-Discovery_Audio_Player_Recorder
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if defined MEDIA_USB_KEY
 USB_OTG_CORE_HANDLE          USB_OTG_Core;
 USBH_HOST                    USB_Host;
#endif

RCC_ClocksTypeDef RCC_Clocks;
__IO uint8_t RepeatState = 0;
__IO uint16_t CCR_Val = 16826;
extern __IO uint8_t LED_Toggle;

/* Private function prototypes -----------------------------------------------*/
static void TIM_LED_Config(void);
static void vMainTask( void *pvParameters );
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
*/
int main(void)
{
	USART_Config();
	printf("SStarted Music Player\n");


	/* Start the check task - which is defined in this file. */
	xTaskCreate( vMainTask, "Check", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );

	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here! */
  return 0;  
}

static void vMainTask( void *pvParameters ) {
	( void ) pvParameters;
	for( ;; )
	{
		printf("hello\r\n");
		vTaskDelay( 1000 );
	}
}
/**
  * @brief  Configures the TIM Peripheral for Led toggling.
  * @param  None
  * @retval None
  */
static void TIM_LED_Config(void)
{
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  uint16_t prescalervalue = 0;
  
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* Enable the TIM3 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Initialize Leds mounted on STM324F4-EVAL board */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED6);
  
  /* Compute the prescaler value */
  prescalervalue = (uint16_t) ((SystemCoreClock ) / 550000) - 1;
  
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 65535;
  TIM_TimeBaseStructure.TIM_Prescaler = prescalervalue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  
  /* Enable TIM4 Preload register on ARR */
  TIM_ARRPreloadConfig(TIM4, ENABLE);
  
  /* TIM PWM1 Mode configuration: Channel */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR_Val;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  
  /* Output Compare PWM1 Mode configuration: Channel2 */
  TIM_OC1Init(TIM4, &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Disable);
	
  /* TIM Interrupts enable */
  TIM_ITConfig(TIM4, TIM_IT_CC1 , ENABLE);
  
  /* TIM4 enable counter */
  TIM_Cmd(TIM4, ENABLE);
}


void vApplicationTickHook( void )
{
}

void vApplicationStackOverflowHook ( void)
{

}

void vApplicationIdleHook (void)
{

}

void vApplicationMallocFailedHook (void)
{

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

  
/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
