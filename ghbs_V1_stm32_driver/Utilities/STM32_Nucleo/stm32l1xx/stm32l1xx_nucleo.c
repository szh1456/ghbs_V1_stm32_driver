/**
  ******************************************************************************
  * @file    stm32l1xx_nucleo.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    11-February-2014
  * @brief   This file provides set of firmware functions to manage Leds and
  *          push-button available on STM32NUCLEO Kit from STMicroelectronics.
  *          It provides also functions to configure and manage the STM32F3xx 
  *          resources (SPI and ADC) used to drive LCD, uSD card and Joystick
  *          available on adafruit 1.8" TFT shield.   
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */  
  
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_nucleo.h"

/** @addtogroup Utilities
  * @{
  */ 

/** @addtogroup STM32L1XX_NUCLEO
  * @{
  */
      
/** @defgroup STM32L1XX_NUCLEO_LOW_LEVEL 
  * @brief This file provides set of firmware functions to manage Leds and push-button
  *        available on STM32NUCLEO Kit from STMicroelectronics.
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
    
/** @defgroup STM32L1XX_NUCLEO_LOW_LEVEL_Private_Variables
  * @{
  */ 
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED2_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED2_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED2_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {USER_BUTTON_GPIO_PORT}; 

const uint16_t BUTTON_PIN[BUTTONn] = {USER_BUTTON_PIN}; 

const uint32_t BUTTON_CLK[BUTTONn] = {USER_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {USER_BUTTON_EXTI_LINE};

const uint8_t BUTTON_PORT_SOURCE[BUTTONn] = {USER_BUTTON_EXTI_PORT_SOURCE};
								 
const uint8_t BUTTON_PIN_SOURCE[BUTTONn] = {USER_BUTTON_EXTI_PIN_SOURCE}; 
const uint8_t BUTTON_IRQn[BUTTONn] = {USER_BUTTON_EXTI_IRQn};


USART_TypeDef* COM_USART[COMn] = {EVAL_COM2}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM2_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM2_RX_GPIO_PORT};

const uint32_t COM_USART_CLK[COMn] = {EVAL_COM2_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM2_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM2_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM2_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM2_RX_PIN};
 
const uint8_t COM_TX_PIN_SOURCE[COMn] = {EVAL_COM2_TX_SOURCE};

const uint8_t COM_RX_PIN_SOURCE[COMn] = {EVAL_COM2_RX_SOURCE};
 
const uint8_t COM_TX_AF[COMn] = {EVAL_COM2_TX_AF};
 
const uint8_t COM_RX_AF[COMn] = {EVAL_COM2_RX_AF};

/**
  * @}
  */ 

/* Private function prototypes -----------------------------------------------*/

/** @defgroup STM32L1XX_NUCLEO_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *         This parameter must be: LED2
  * @retval None
  */
void STM_EVAL_LEDInit(Led_TypeDef Led)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(GPIO_CLK[Led], ENABLE);
  
  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);  
}


void Force_Sync_GPIOInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(FORCE_SYNC_GPIO_CLK, ENABLE);
  
  /* Configure the GPIO pin */
  GPIO_InitStructure.GPIO_Pin = FORCE_SYNC_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_Init(FORCE_SYNC_GPIO_PORT, &GPIO_InitStructure);  
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *         This parameter must be: LED2
  * @retval None
  */
void STM_EVAL_LEDOn(Led_TypeDef Led)
{   
  GPIO_PORT[Led]->BSRRL = GPIO_PIN[Led]; 
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *         This parameter must be: LED2
  * @retval None
  */
void STM_EVAL_LEDOff(Led_TypeDef Led)
{
  GPIO_PORT[Led]->BSRRH = GPIO_PIN[Led]; 
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *         This parameter must be: LED2
  * @retval None
  */
void STM_EVAL_LEDToggle(Led_TypeDef Led)
{
  GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}
/**
  * @brief  Configures Button GPIO and associated EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter must be: BUTTON_USER
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                            generation capability  
  * @retval None
  */
void STM_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Enable the GPIO Clock */
  RCC_AHBPeriphClockCmd(BUTTON_CLK[Button], ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* Configure Button pin as input */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

  if (Button_Mode == BUTTON_MODE_EXTI)
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    SYSCFG_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

    /* Configure Button EXTI line */
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure); 
  }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter must be: BUTTON_USER  
  * @retval The Button GPIO pin value.
  */
uint32_t STM_EVAL_PBGetState(Button_TypeDef Button)
{
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}


void STM_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM], ENABLE);

  /* Enable USART2 clock */
  RCC_APB1PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 

  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(COM_TX_PORT[COM], COM_TX_PIN_SOURCE[COM], COM_TX_AF[COM]);

  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(COM_RX_PORT[COM], COM_RX_PIN_SOURCE[COM], COM_RX_AF[COM]);
  
  /* Configure USART Tx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);
    
  /* Configure USART Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
  GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

  /* USART configuration */
  USART_Init(COM_USART[COM], USART_InitStruct);
    
  /* Enable USART */
  USART_Cmd(COM_USART[COM], ENABLE);
}
void STM_USART_DEBUG_Init(COM_TypeDef COM)
{
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  STM_EVAL_COMInit(COM, &USART_InitStructure);
}

/**
  * @brief  Initializes the SPI Interface used to drive the LCD and uSD card 
  *         available on adafruit 1.8" TFT shield.
  * @note   This function must by called by the application code before to initialize
  *         the LCD and uSD card.    
  * @param  None
  * @retval None
  */

//void STM_SPI_Init(void)
//{
//  GPIO_InitTypeDef  GPIO_InitStructure;
//  SPI_InitTypeDef   SPI_InitStructure;

//  /* Enable GPIOs clock */
//  RCC_AHBPeriphClockCmd(SPI_MOSI_GPIO_CLK | SPI_MISO_GPIO_CLK | SPI_SCK_GPIO_CLK, ENABLE);

//  /* Enable SPI clock */
//  RCC_APB2PeriphClockCmd(LCD_SD_SPI_CLK, ENABLE); 

//  /* Configure SPI SCK pin */
//  GPIO_InitStructure.GPIO_Pin = SPI_SCK_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
//  GPIO_Init(SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

//  /* Configure SPI MISO pin */
//  GPIO_InitStructure.GPIO_Pin = SPI_MISO_PIN;
//  GPIO_Init(SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

//  /* Configure SPI MOSI pin */
//  GPIO_InitStructure.GPIO_Pin = SPI_MOSI_PIN;
//  GPIO_Init(SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);
//  
//  /* Connect SCK, MISO and MOSI pins to SPI alternate */
//  GPIO_PinAFConfig(SPI_SCK_GPIO_PORT, SPI_SCK_SOURCE, SPI_SCK_AF);
//  GPIO_PinAFConfig(SPI_MISO_GPIO_PORT, SPI_MISO_SOURCE, SPI_MISO_AF);
//  GPIO_PinAFConfig(SPI_MOSI_GPIO_PORT, SPI_MOSI_SOURCE, SPI_MOSI_AF); 
//  
//  /* Configure SPI */
//  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
//  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
//  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
//  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
//  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
//      /* SPI baudrate is set to 8 MHz maximum (PCLK2/SPI_BaudRatePrescaler = 32/4 = 8 MHz) 
//       to verify these constraints:
//          - ST7735R LCD SPI interface max baudrate is 15MHz for write and 6.66MHz for read
//            Since the provided driver doesn't use read capability from LCD, only constraint 
//            on write baudrate is considered.
//          - SD card SPI interface max baudrate is 25MHz for write/read
//          - PCLK2 max frequency is 32 MHz 
//       */
//  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
//  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
//  SPI_InitStructure.SPI_CRCPolynomial = 7;
//  SPI_Init(LCD_SD_SPI, &SPI_InitStructure);
//    
//  /* Enable SPI */
//  SPI_Cmd(LCD_SD_SPI, ENABLE);
//}
/**
  * @brief  Initializes the SPI Interface (universal)
  * @note      
  * @param  None
  * @retval None
  */
void uni_SPI_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /*!< uni_CS_GPIO, uni_MOSI_GPIO, uni_MISO_GPIO and uni_SCK_GPIO 
       Periph clock enable */
  RCC_AHBPeriphClockCmd(uni_SPI_CS_GPIO_CLK | uni_SPI_CS_GPIO_CLK_AUX_A | uni_SPI_CS_GPIO_CLK_AUX_B | uni_SPI_MOSI_GPIO_CLK | uni_SPI_MISO_GPIO_CLK |
                        uni_SPI_SCK_GPIO_CLK , ENABLE);

  /*!< uni Periph clock enable */
  RCC_APB2PeriphClockCmd(uni_SPI_CLK, ENABLE); 

  /*!< Configure uni pins: SCK */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(uni_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_MISO_PIN;
  GPIO_Init(uni_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_MOSI_PIN;
  GPIO_Init(uni_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni_SPI_CS_PIN pin: uni_SPI Card CS pin */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(uni_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN_AUX_A;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(uni_SPI_CS_GPIO_PORT_AUX_A, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN_AUX_B;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(uni_SPI_CS_GPIO_PORT_AUX_B, &GPIO_InitStructure);

  /* Connect PXx to uni_SPI_SCK */
  GPIO_PinAFConfig(uni_SPI_SCK_GPIO_PORT, uni_SPI_SCK_SOURCE, uni_SPI_SCK_AF);

  /* Connect PXx to uni_SPI_MISO */
  GPIO_PinAFConfig(uni_SPI_MISO_GPIO_PORT, uni_SPI_MISO_SOURCE, uni_SPI_MISO_AF); 

  /* Connect PXx to uni_SPI_MOSI */
  GPIO_PinAFConfig(uni_SPI_MOSI_GPIO_PORT, uni_SPI_MOSI_SOURCE, uni_SPI_MOSI_AF);  
  
  /*!< uni SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;//set SPI baudrate to 1MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(uni_SPI, &SPI_InitStructure);

  SPI_Cmd(uni_SPI, ENABLE); /*!< uni_SPI enable */
}

void uni_SPI_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  SPI_Cmd(uni_SPI, DISABLE); /*!< uni_SPI disable */
  SPI_I2S_DeInit(uni_SPI);   /*!< DeInitializes the uni_SPI */
  
  /*!< uni_SPI Periph clock disable */
  RCC_APB2PeriphClockCmd(uni_SPI_CLK, DISABLE); 

  /*!< Configure uni_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(uni_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni pins: MISO */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_MISO_PIN;
  GPIO_Init(uni_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_MOSI_PIN;
  GPIO_Init(uni_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni_CS_PIN pin: uni Card CS pin */
  GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN;
  GPIO_Init(uni_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN_AUX_A;
  GPIO_Init(uni_SPI_CS_GPIO_PORT_AUX_A, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = uni_SPI_CS_PIN_AUX_B;
  GPIO_Init(uni_SPI_CS_GPIO_PORT_AUX_B, &GPIO_InitStructure);
}

void adc_SPI_LowLevel_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  SPI_InitTypeDef   SPI_InitStructure;

  /*!< uni_CS_GPIO, uni_MOSI_GPIO, uni_MISO_GPIO and uni_SCK_GPIO 
       Periph clock enable */
  RCC_AHBPeriphClockCmd(adc_SPI_CS_GPIO_CLK_A |
//	adc_SPI_CS_GPIO_CLK_B | adc_SPI_CS_GPIO_CLK_C| adc_SPI_CS_GPIO_CLK_D |
													//adc_SPI_CS_GPIO_CLK_E | adc_SPI_CS_GPIO_CLK_F | adc_SPI_CS_GPIO_CLK_G| adc_SPI_CS_GPIO_CLK_H |
	adc_SPI_MOSI_GPIO_CLK | adc_SPI_MISO_GPIO_CLK |
                        adc_SPI_SCK_GPIO_CLK , ENABLE);

  /*!< uni Periph clock enable */
  RCC_APB1PeriphClockCmd(adc_SPI_CLK, ENABLE); 

  /*!< Configure uni pins: SCK */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(adc_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure adc_SPI pins: MISO */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_MISO_PIN;
  GPIO_Init(adc_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure adc_SPI pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_MOSI_PIN;
  GPIO_Init(adc_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure adc_SPI_CS_PIN pin: adc_SPI Card CS pin */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_A;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_A, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_B;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_B, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_C;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_C, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_D;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_D, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_E;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_E, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_F;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_F, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_G;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_G, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_H;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_H, &GPIO_InitStructure);

  /* Connect PXx to adc_SPI_SCK */
  GPIO_PinAFConfig(adc_SPI_SCK_GPIO_PORT, adc_SPI_SCK_SOURCE, adc_SPI_SCK_AF);

  /* Connect PXx to adc_SPI_MISO */
  GPIO_PinAFConfig(adc_SPI_MISO_GPIO_PORT, adc_SPI_MISO_SOURCE, adc_SPI_MISO_AF); 

  /* Connect PXx to adc_SPI_MOSI */
  GPIO_PinAFConfig(adc_SPI_MOSI_GPIO_PORT, adc_SPI_MOSI_SOURCE, adc_SPI_MOSI_AF);  
  
  /*!< uni SPI Config */
  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;//set SPI baudrate to 1MHz
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(adc_SPI, &SPI_InitStructure);

  SPI_Cmd(adc_SPI, ENABLE); /*!< adc_SPI enable */
}
void adc_SPI_LowLevel_AlterDirection(uint16_t SPI_Direction)
{
	if (SPI_Direction == SPI_Direction_Rx)	while(adc_SPI->SR != 0x0002) ;
	
	SPI_BiDirectionalLineConfig(adc_SPI, SPI_Direction);
}

void adc_SPI_LowLevel_DeInit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  SPI_Cmd(adc_SPI, DISABLE); /*!< adc_SPI disable */
  SPI_I2S_DeInit(adc_SPI);   /*!< DeInitializes the adc_SPI */
  
  /*!< adc_SPI Periph clock disable */
  RCC_APB1PeriphClockCmd(adc_SPI_CLK, DISABLE); 

  /*!< Configure adc_SPI pins: SCK */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_SCK_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(adc_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni pins: MISO */
  //GPIO_InitStructure.GPIO_Pin = adc_SPI_MISO_PIN;
  //GPIO_Init(adc_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure uni pins: MOSI */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_MOSI_PIN;
  GPIO_Init(adc_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure adc_CS_PIN pin: uni Card CS pin */
  GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_A;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_A, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_B;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_B, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_C;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_C, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_D;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_D, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_E;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_E, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_F;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_F, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_G;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_G, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = adc_SPI_CS_PIN_H;
  GPIO_Init(adc_SPI_CS_GPIO_PORT_H, &GPIO_InitStructure);
}


/**
  * @brief  Configures LCD control lines (CS and DC) in Output Push-Pull mode.
  * @param  None
  * @retval None
  */
//void LCD_CtrlLines_Config(void)
//{
//  GPIO_InitTypeDef GPIO_InitStructure;

//  /* Enable GPIOs clock */
//  RCC_AHBPeriphClockCmd(LCD_CS_GPIO_CLK | LCD_DC_GPIO_CLK, ENABLE);

//  /* Configure CS in Output Push-Pull mode */
//  GPIO_InitStructure.GPIO_Pin = LCD_CS_PIN;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
//  GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);
//  
//  /* Configure DC in Output Push-Pull mode */
//  GPIO_InitStructure.GPIO_Pin = LCD_DC_PIN;
//  GPIO_Init(LCD_DC_GPIO_PORT, &GPIO_InitStructure);

//  /* Set chip select pin high */
//  LCD_CS_HIGH();
//}

/**
  * @brief  Configures uSD control line (CS) in Output Push-Pull mode.
  * @param  None
  * @retval None
  */


/**
  * @brief  Sends a byte through the SPI interface and return the byte received 
  *         from the SPI bus.
  * @param  Data: byte send.
  * @retval The received byte value
  * @retval None
  */
//uint8_t STM_SPI_WriteRead(uint8_t Data)
//{
//  uint8_t tmp = 0x00;
// 
//  /* Wait until the transmit buffer is empty */ 
//  while(SPI_I2S_GetFlagStatus(LCD_SD_SPI, SPI_I2S_FLAG_TXE) != SET)
//  {
//  }  
//  /* Send the byte */
//  SPI_I2S_SendData(LCD_SD_SPI, Data);
//  
//  /* Wait to receive a byte */ 
//  while(SPI_I2S_GetFlagStatus(LCD_SD_SPI, SPI_I2S_FLAG_RXNE) != SET)
//  {
//  }
//  /* Return the byte read from the SPI bus */    
//  tmp = SPI_I2S_ReceiveData(LCD_SD_SPI); 

//  /* Wait until the TXE and BSY flags are set */ 
//  while(SPI_I2S_GetFlagStatus(LCD_SD_SPI, SPI_I2S_FLAG_TXE) != SET)
//  {
//  }   
//  while(SPI_I2S_GetFlagStatus(LCD_SD_SPI, SPI_I2S_FLAG_BSY) != RESET)
//  {
//  }  
// 
//  /* Return read Data */
//  return tmp;
//}

/**
  * @brief  Initializes ADC, used to detect motion of Joystick available on 
  *         adafruit 1.8" TFT shield.
  * @param  None
  * @retval None
  */
//void STM_ADC_Config(void)
//{
//  GPIO_InitTypeDef      GPIO_InitStructure;
//  ADC_InitTypeDef       ADC_InitStructure;

//  /* Enable the HSI oscillator */
//  RCC_HSICmd(ENABLE);
//  
//  /* Enable GPIO clock */
//  RCC_AHBPeriphClockCmd(ADC_GPIO_CLK, ENABLE);
//      
//  /* Configure ADCx Channel 8 as analog input */
//  GPIO_InitStructure.GPIO_Pin = ADC_GPIO_PIN ;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
//  GPIO_Init(ADC_GPIO_PORT, &GPIO_InitStructure);  

//  /* Check that HSI oscillator is ready */
//  while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET);
//  
//  /* Enable ADC clock */
//  RCC_APB2PeriphClockCmd(ADC_CLK, ENABLE);  
//   
//  /* Initialize ADC structure */
//  ADC_StructInit(&ADC_InitStructure);
//  
//  /* ADC1 configuration */
//  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;  
//  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
//  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
//  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
//  ADC_InitStructure.ADC_NbrOfConversion = 1;
//  ADC_Init(ADCx, &ADC_InitStructure);
//  
//  /* ADCx regular channel8 configuration */ 
//  ADC_RegularChannelConfig(ADCx, ADC_Channel_8, 1, ADC_SampleTime_16Cycles);
//   
//  /* Enable the ADC */
//  ADC_Cmd(ADCx, ENABLE);
//  
//  /* Wait until the ADC1 is ready */
//  while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
//  {
//  }  
//  /* Start ADC Software Conversion */ 
//  ADC_SoftwareStartConv(ADCx); 
//}

/**
  * @brief  Returns the Joystick key pressed.
  * @note   To know which Joystick key is pressed we need to detect the voltage
  *         level on each key output
  *           - SEL   : 1.055 V / 1308
  *           - RIGHT : 0.595 V / 737
  *           - LEFT  : 3.0 V / 3720 
  *           - UP    : 1.65 V / 2046
  *           - DOWN  : 0.71 V / 88
  *           - None  : 3.3 V / 4095
  * @retval Code of the Joystick key pressed.
  *          This code can be one of the following values:
  *            @arg  JOY_NONE
  *            @arg  JOY_SEL
  *            @arg  JOY_DOWN
  *            @arg  JOY_LEFT
  *            @arg  JOY_RIGHT
  *            @arg  JOY_UP  
  */
//JOYState_TypeDef STM_Get_JOYState(void)
//{
//  JOYState_TypeDef state = JOY_NONE;
//  uint16_t  KeyConvertedValue = 0; 

//  KeyConvertedValue = ADC_GetConversionValue(ADCx);
//  
//  if((KeyConvertedValue > 2010) && (KeyConvertedValue < 2090))
//  {
//    state = JOY_UP;
//  }
//  else if((KeyConvertedValue > 680) && (KeyConvertedValue < 780))
//  {
//    state = JOY_RIGHT;
//  }
//  else if((KeyConvertedValue > 1270) && (KeyConvertedValue < 1350))
//  {
//    state = JOY_SEL;
//  }
//  else if((KeyConvertedValue > 50) && (KeyConvertedValue < 130))
//  {
//    state = JOY_DOWN;
//  }
//  else if((KeyConvertedValue > 3680) && (KeyConvertedValue < 3760))
//  {
//    state = JOY_LEFT;
//  }
//  else
//  {
//    state = JOY_NONE;
//  }
//  /* Loop while a key is pressed */
//  if(state != JOY_NONE)
//  { 
//    while(KeyConvertedValue < 4000)
//    {
//      KeyConvertedValue = ADC_GetConversionValue(ADCx);
//    }      
//  }
//  /* Return the code of the Joystick key pressed*/
//  return state;
//}

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */   

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
