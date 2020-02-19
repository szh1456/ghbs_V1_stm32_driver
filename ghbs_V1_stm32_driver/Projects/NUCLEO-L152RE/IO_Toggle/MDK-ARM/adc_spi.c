#include "adc_spi.h"

void adc_SPI_DeInit(void)
{
  adc_SPI_LowLevel_DeInit();
}

void adc_SPI_Init(void)
{
  adc_SPI_LowLevel_Init();
    
  /*!< Deselect: Chip Select high */
  for (uint8_t i = 'A';i <= 'H';i++)
	{
		adc_set_cs_high(i);
	}
}

void adc_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite, uint8_t device)
{
	adc_set_cs_low(device);
	uint8_t mask = 0x00;
  
  /*!< Send "Read from Memory" instruction and MSB of WriteAddr  */
  adc_SendByte( AD9250_WRITE | mask, device);
	adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
	switch (NumByteToWrite)
	{
		case 1:
			mask = AD9250_1BYTE;	break;
		case 2:
			mask = AD9250_2BYTE;	break;
		case 3:
			mask = AD9250_3BYTE;	break;
		default:
			mask = AD9250_MBYTE; 	break;
	}
  
	for (int num = 0;  num <  NumByteToWrite; num++)  /*!< while there is data to be read */
  {
   // todo
		adc_SendByte(pBuffer[num],device);
  }
  
  /*!< Deselect the EEPROM: Chip Select high */
	adc_set_cs_high(device);
}


uint32_t adc_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead, uint8_t device)
{
  /*!< Select the EEPROM: Chip Select low */
  adc_set_cs_low(device);
  uint8_t mask = 0x00;
	adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
	switch (NumByteToRead)
	{
		case 1:
			mask = AD9250_1BYTE;	break;
		case 2:
			mask = AD9250_2BYTE;	break;
		case 3:
			mask = AD9250_3BYTE;	break;
		default:
			mask = AD9250_MBYTE; 	break;
	}
	
  /*!< Send "Read from Memory" instruction and MSB of WriteAddr  */
  adc_SendByte(AD9250_READ | mask, device);

  adc_SPI_LowLevel_AlterDirection(SPI_Direction_Rx);
  for (int num = 0;  num <  NumByteToRead; num++)  /*!< while there is data to be read */
  {
   // todo
		pBuffer[num] = adc_SendDummyByte(adc_DUMMY_BYTE,device);
  }
  adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
  /*!< Deselect the EEPROM: Chip Select high */
  adc_set_cs_high(device);
  
  return 0;
}


void adc_SendByte(uint8_t byte, uint8_t device)
{
  /*!< Loop while DR register in not empty */
  while (SPI_I2S_GetFlagStatus(adc_SPI, SPI_I2S_FLAG_TXE) == RESET);
  /*!< Send byte through the SPI peripheral */
  SPI_SendData(adc_SPI, byte);
  /*!< Return the byte read from the SPI bus */
  //SPI_ReceiveData(adc_SPI);
}

uint8_t adc_SendDummyByte(uint8_t byte, uint8_t device)
{
  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(adc_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return (uint8_t)SPI_ReceiveData(adc_SPI);
}

uint8_t adc_ReadStatusRegister(uint8_t* addr, uint8_t device)
{
  uint8_t unistatus = 0xFF;
  /*!< Select the EEPROM: Chip Select low */
  adc_set_cs_low(device);
  //adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
  /*!< Send "Read Status Register" instruction */
	adc_SendByte(addr[0], device);
	adc_SendByte(addr[1] , device);
	//SPI_I2S_ClearFlag(adc_SPI,SPI_I2S_FLAG_RXNE);
	adc_SPI_LowLevel_AlterDirection(SPI_Direction_Rx);
	unistatus = adc_SendDummyByte(adc_DUMMY_BYTE, device);
	adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
	adc_set_cs_high(device); 
  /*!< Deselect the EEPROM: Chip Select high */
	addr[2] = unistatus;
	printf("[*]Read from 0x%02X, Value 0x%02X. \r\n",addr[1], addr[2]);
  return unistatus;
}

void adc_WriteStatusRegister(uint8_t* addr, uint8_t device)
{ 
  /*!< Select the EEPROM: Chip Select low */
  adc_set_cs_low(device);
  //adc_SPI_LowLevel_AlterDirection(SPI_Direction_Tx);
  /*!< Send "Read Status Register" instruction */
  adc_SendByte(addr[0], device);
	adc_SendByte(addr[1] , device);
	adc_SendByte(addr[2] , device);
		Delay(1);//while (SPI_I2S_GetFlagStatus(adc_SPI, SPI_I2S_FLAG_TXE) == RESET)	;
  /*!< Deselect the EEPROM: Chip Select high */
  adc_set_cs_high(device);
	printf("[*]Write to 0x%02X, Value 0x%02X.\r\n",addr[1], addr[2]);
}

void adc_set_cs_low(uint8_t device)
{
	switch (device)
	{
		case 'A':
			adc_CS_LOW_A(); break;
		case 'B':
			adc_CS_LOW_B(); break;
		case 'C':
			adc_CS_LOW_C(); break;
		case 'D':
			adc_CS_LOW_D(); break;
		case 'E':
			adc_CS_LOW_E(); break;
		case 'F':
			adc_CS_LOW_F(); break;
		case 'G':
			adc_CS_LOW_G(); break;
		case 'H':
			adc_CS_LOW_H(); break;
	}
}
void adc_set_cs_high(uint8_t device)
{
	switch (device)
	{
		case 'A':
			adc_CS_HIGH_A(); break;
		case 'B':
			adc_CS_HIGH_B(); break;
		case 'C':
			adc_CS_HIGH_C(); break;
		case 'D':
			adc_CS_HIGH_D(); break;
		case 'E':
			adc_CS_HIGH_E(); break;
		case 'F':
			adc_CS_HIGH_F(); break;
		case 'G':
			adc_CS_HIGH_G(); break;
		case 'H':
			adc_CS_HIGH_H(); break;
	}
}
