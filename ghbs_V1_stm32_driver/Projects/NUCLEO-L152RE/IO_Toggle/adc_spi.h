/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_nucleo.h"
#include "main.h"

#define adc_DUMMY_BYTE         0xFF

#define adc_CS_LOW_A()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_A, adc_SPI_CS_PIN_A)
#define adc_CS_LOW_B()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_B, adc_SPI_CS_PIN_B)
#define adc_CS_LOW_C()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_C, adc_SPI_CS_PIN_C)
#define adc_CS_LOW_D()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_D, adc_SPI_CS_PIN_D)
#define adc_CS_LOW_E()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_E, adc_SPI_CS_PIN_E)
#define adc_CS_LOW_F()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_F, adc_SPI_CS_PIN_F)
#define adc_CS_LOW_G()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_G, adc_SPI_CS_PIN_G)
#define adc_CS_LOW_H()						 GPIO_ResetBits(adc_SPI_CS_GPIO_PORT_H, adc_SPI_CS_PIN_H)

#define adc_CS_HIGH_A()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_A, adc_SPI_CS_PIN_A)
#define adc_CS_HIGH_B()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_B, adc_SPI_CS_PIN_B)
#define adc_CS_HIGH_C()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_C, adc_SPI_CS_PIN_C)
#define adc_CS_HIGH_D()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_D, adc_SPI_CS_PIN_D)
#define adc_CS_HIGH_E()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_E, adc_SPI_CS_PIN_E)
#define adc_CS_HIGH_F()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_F, adc_SPI_CS_PIN_F)
#define adc_CS_HIGH_G()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_G, adc_SPI_CS_PIN_G)
#define adc_CS_HIGH_H()						 GPIO_SetBits(adc_SPI_CS_GPIO_PORT_H, adc_SPI_CS_PIN_H)

//#define AD9250_WRITE	0x00
//#define AD9250_READ	0x80

#define AD9250_1BYTE	0x00
#define AD9250_2BYTE	0x20
#define AD9250_3BYTE	0x40
#define AD9250_MBYTE	0x60


void     adc_SPI_DeInit(void);
void     adc_SPI_Init(void);
uint32_t adc_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead, uint8_t device);
void     adc_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite, uint8_t device);

void adc_SendByte(uint8_t byte, uint8_t device);
uint8_t adc_SendDummyByte(uint8_t byte, uint8_t device);
void adc_WriteStatusRegister(uint8_t * addr, uint8_t device);
uint8_t adc_ReadStatusRegister(uint8_t * addr, uint8_t device);

void adc_set_cs_low(uint8_t device);
void adc_set_cs_high(uint8_t device);

