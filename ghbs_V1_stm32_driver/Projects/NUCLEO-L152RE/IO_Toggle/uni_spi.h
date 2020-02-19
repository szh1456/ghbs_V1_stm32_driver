#ifndef __STM32L152D_EVAL_SPI_EE_H
#define __STM32L152D_EVAL_SPI_EE_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_nucleo.h"

#define uni_DUMMY_BYTE         0xFF

#define uni_PAGESIZE           16


#define LTC6952_VER           0x38
#define LTC6952_STAT					0x00
#define LTC6952_VER_MASK			0x02

#define DEVICE_MASTER		0
#define DEVICE_AUX_A		1
#define DEVICE_AUX_B		2

 


#define uni_CS_LOW()						 GPIO_ResetBits(uni_SPI_CS_GPIO_PORT, uni_SPI_CS_PIN)
#define uni_CS_LOW_AUX_A()       GPIO_ResetBits(uni_SPI_CS_GPIO_PORT_AUX_A, uni_SPI_CS_PIN_AUX_A)
#define uni_CS_LOW_AUX_B()       GPIO_ResetBits(uni_SPI_CS_GPIO_PORT_AUX_B, uni_SPI_CS_PIN_AUX_B)


#define uni_CS_HIGH()      			 GPIO_SetBits(uni_SPI_CS_GPIO_PORT, uni_SPI_CS_PIN)
#define uni_CS_HIGH_AUX_A()      GPIO_SetBits(uni_SPI_CS_GPIO_PORT_AUX_A, uni_SPI_CS_PIN_AUX_A)
#define uni_CS_HIGH_AUX_B()      GPIO_SetBits(uni_SPI_CS_GPIO_PORT_AUX_B, uni_SPI_CS_PIN_AUX_B)





void     uni_DeInit(void);
void     uni_Init(void);
uint32_t uni_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead, uint8_t device);
void     uni_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite, uint8_t device);

uint8_t uni_ReadByte(uint8_t device);
uint8_t uni_SendByte(uint8_t byte, uint8_t device);
void uni_WriteStatusRegister(uint8_t addr, uint8_t byte, uint8_t device);
uint8_t uni_ReadStatusRegister(uint8_t addr, uint8_t device);

void uni_set_cs_low(uint8_t device);
void uni_set_cs_high(uint8_t device);


#ifdef __cplusplus
}
#endif

#endif /* __STM32L152D_EVAL_SPI_EE_H */
