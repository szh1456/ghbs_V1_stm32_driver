/**
  ******************************************************************************
  * @file    main.c 
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    11-April-2014
  * @brief   Main program body
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
#include "main.h"
#include "stm32l1xx_ip_dbg.h"


/** @addtogroup IO_Toggle
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t __IO BlinkSpeed = 0;
extern uint8_t force_sync_flag;

/* Private function prototypes -----------------------------------------------*/
RCC_ClocksTypeDef RCC_Clocks;
/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32l1xx_xl.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32l1xx.c file
     */ 
  /* Initialize all peripherals pointers */
	STM_USART_DEBUG_Init(COM2);
  IP_Debug();
  /* SysTick end of count event each 1ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 1000);
  
  /* Initialize LED2 */
  //STM_EVAL_LEDInit(LED2);
  
	Force_Sync_GPIOInit();
		FORCE_SYNC_HIGH();
	FORCE_RESET_HIGH();
	force_sync_flag = 0;
	
	
  /* Initialize User_Button on STM32NUCLEO */
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);   
  
  /* Initiate Blink Speed variable */ 
  BlinkSpeed = 0;
	printf("\r\n[0] STM32l1xx Firmware Library compiled with FULL ASSERT function... \n\r");
  printf("[0] Run-time checking enabled  \n\r");
	printf("[0] Program Started ...  \n\r");
  
	uni_Init();
	adc_SPI_Init();
	/*
	while(1){
	adc_CS_LOW_A();
	adc_CS_LOW_G();
	adc_CS_LOW_H();
	Delay(1000);
	adc_CS_HIGH_A();
	adc_CS_HIGH_G();
	adc_CS_HIGH_H();
	Delay(1000);
	}
	*/
	
ltc6953_master_isOkay();
 ltc6953_master_detect();
 ltc6953_master_config_global();
 ltc6953_master_config_srq();
 ltc6953_master_config_outs();
 
 ltc6952_aux_detect(DEVICE_AUX_A);
 ltc6952_aux_isOkay(DEVICE_AUX_A, 1);
 ltc6952_aux_config_global(DEVICE_AUX_A, 0x07FF);
 ltc6952_aux_config_srq(DEVICE_AUX_A);

 ltc6952_aux_config_out_dclk(DEVICE_AUX_A, 0, 0,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_A, 0, 2,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_A, 0, 4,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_A, 0, 5,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_A, 0, 8,0);
 
 
 
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 1);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 3);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 6);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 7);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 9);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_A, 20, 10);
 
 ltc6952_aux_detect(DEVICE_AUX_B);
 ltc6952_aux_isOkay(DEVICE_AUX_B, 1);
 ltc6952_aux_config_global(DEVICE_AUX_B,  0x07FE );
 ltc6952_aux_config_srq(DEVICE_AUX_B);
 
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 0,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 2,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 4,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 5,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 8,0);
 ltc6952_aux_config_out_dclk(DEVICE_AUX_B, 0, 9,0);

 
 ltc6952_aux_config_out_sysref(DEVICE_AUX_B, 20, 1);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_B, 20, 3);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_B, 20, 6);
 ltc6952_aux_config_out_sysref(DEVICE_AUX_B, 20, 7);
 Delay(2000);
 ltc6953_master_aux_sync();
 Delay(1);
 ltc6952_aux_fp_sysref();
 
	
	struct ad9250_dev  ad9250_deviceA ;
	struct ad9250_dev  ad9250_deviceB ;
	struct ad9250_dev  ad9250_deviceC ;
	struct ad9250_dev  ad9250_deviceD ;
	struct ad9250_dev  ad9250_deviceE ;
	struct ad9250_dev  ad9250_deviceF ;
	struct ad9250_dev  ad9250_deviceG ;
	struct ad9250_dev  ad9250_deviceH ;
//	struct ad9250_dev * ad9250_deviceB;
//	
	ad9250_create(&ad9250_deviceA, 'A');
	ad9250_create(&ad9250_deviceB, 'B');
	ad9250_create(&ad9250_deviceC, 'C');
	ad9250_create(&ad9250_deviceD, 'D');
	ad9250_create(&ad9250_deviceE, 'E');
	ad9250_create(&ad9250_deviceF, 'F');
	ad9250_create(&ad9250_deviceG, 'G');
	ad9250_create(&ad9250_deviceH, 'H');
	
//	ad9250_create(&ad9250_deviceB, 'B');

  printf("[*] ADC A output:  \n\r");
	ad9250_setup(&ad9250_deviceA, -1, 0);
	printf("***************************  \n\r");
  
	printf("[*] ADC B output:  \n\r");
	ad9250_setup(&ad9250_deviceB, -1, 0);
	printf("***************************  \n\r");
	
	printf("[*] ADC C output:  \n\r");
	ad9250_setup(&ad9250_deviceC, -1, 0);
	printf("***************************  \n\r");
	
	printf("[*] ADC D path A output:  \n\r");
	ad9250_setup(&ad9250_deviceD, -1, 0);
	//printf("[*] ADC D path B output:  \n\r");
	//ad9250_setup(&ad9250_deviceD, 1, 1);
	printf("***************************  \n\r");
	
	printf("[*] ADC E output:  \n\r");
	ad9250_setup(&ad9250_deviceE, -1, 0);
	printf("***************************  \n\r");
	
	printf("[*] ADC F output:  \n\r");
	ad9250_setup(&ad9250_deviceF, -1, 0);
	printf("***************************  \n\r");
	
	printf("[*] ADC G output:  \n\r");
	ad9250_setup(&ad9250_deviceG, -1, 0);
	printf("***************************  \n\r");
	
	printf("[*] ADC H output:  \n\r");
	ad9250_setup(&ad9250_deviceH, -1, 0);
	printf("***************************  \n\r");
	
	//ad9250_write(ad9250_deviceA, AD9250_REG_SPI_CFG,0x3C);
	//ad9250_write(ad9250_deviceA, AD9250_REG_DEVICE_UPDATE,0x01);
	//Delay(1);
	//ad9250_read(ad9250_deviceA, AD9250_REG_SPI_CFG);
	ad9250_config_print(&ad9250_deviceD);
	
	FORCE_RESET_LOW();
	Delay(50);
	FORCE_RESET_HIGH();

	Delay(50);

	//ltc6952_perform_sysref();
	

 while(1)
 {
//	 ad9250_read(&ad9250_deviceA,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceB,(AD9250_R1B | 0x0A));	 
//	 ad9250_read(&ad9250_deviceC,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceD,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceE,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceF,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceG,(AD9250_R1B | 0x0A));
//	 ad9250_read(&ad9250_deviceH,(AD9250_R1B | 0x0A));
//	 printf("\n");
	 Delay(50);
	if (force_sync_flag)//(force_sync_flag)
	{
		  
		
			printf("force sync flag recorded!\r\n");
		
			FORCE_SYNC_LOW();
			
			//ltc6952_aux_fp_sysref();
		  ltc6952_perform_sysref();
		  
		
			Delay(50);
			FORCE_SYNC_HIGH();
			force_sync_flag = 0;
	}
 };

 
	adc_SPI_DeInit();
	uni_DeInit();
}

/**
* @brief  Inserts a delay time.
* @param  nTime: specifies the delay time length, in 1 ms.
* @retval None
*/
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;
  
  while(TimingDelay != 0);
}

/**
* @brief  Decrements the TimingDelay variable.
* @param  None
* @retval None
*/
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
printf("\n\r Wrong parameter value detected on\r\n");
  printf("       file  %s\r\n", file);
  printf("       line  %d\r\n", line);
  while (1)
  {
  }
}
#endif

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(EVAL_COM2, (uint8_t) ch);
	ITM_SendChar(ch);
  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(EVAL_COM2, USART_FLAG_TC) == RESET)
  {
  }

  return ch;
}

/**
* @}
*/


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
