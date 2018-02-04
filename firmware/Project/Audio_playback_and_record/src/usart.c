/*
 * usart.c
 *
 *  Created on: Apr 15, 2015
 *      Author: toandang
 */
#include "usart.h"


void USART_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;


  // sort out clocks
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  /* Configure USART2 Tx (PA.02) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  // Map USART2 to A.02
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
  // Initialize USART
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Tx;
  /* Configure USART */
  USART_Init(USART2, &USART_InitStructure);
  /* Enable the USART */
  USART_Cmd(USART2, ENABLE);
  USART_SendData(USART2,0xFF);
}

void USART_write_byte(char ch){
  USART_SendData(USART2, ch);
  while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET){

  }
}


int _write(int fd, char * str, int len)
{
    for (int i = 0; i < len; ++i)
    {
      USART_write_byte(*(str++));
    }
    return len;
}
