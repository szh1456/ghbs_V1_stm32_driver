#include "uni_spi.h"

void uni_DeInit(void)
{
  uni_SPI_LowLevel_DeInit();
}

void uni_Init(void)
{
  uni_SPI_LowLevel_Init();
    
  /*!< Deselect the EEPROM: Chip Select high */
  uni_CS_HIGH();
	uni_CS_HIGH_AUX_A();
	uni_CS_HIGH_AUX_B();
}

void uni_WriteBuffer(uint8_t* pBuffer, uint16_t WriteAddr, uint16_t NumByteToWrite, uint8_t device)
{
	uni_set_cs_low(device);
  
  /*!< Send "Read from Memory" instruction and MSB of WriteAddr  */
  uni_SendByte( (WriteAddr << 1)| 0x00 ,device);

  
	for (int num = 0;  num <  NumByteToWrite; num++)  /*!< while there is data to be read */
  {
   // todo
		uni_SendByte(pBuffer[num],device);
  }
  
  /*!< Deselect the EEPROM: Chip Select high */
	uni_set_cs_high(device);
}


uint32_t uni_ReadBuffer(uint8_t* pBuffer, uint16_t ReadAddr, uint16_t NumByteToRead, uint8_t device)
{
  /*!< Select the EEPROM: Chip Select low */
  uni_set_cs_low(device);
  
  /*!< Send "Read from Memory" instruction and MSB of WriteAddr  */
  uni_SendByte((ReadAddr << 1)| 0x01,device);

  
  for (int num = 0;  num <  NumByteToRead; num++)  /*!< while there is data to be read */
  {
   // todo
		pBuffer[num] = uni_SendByte(uni_DUMMY_BYTE,device);
  }
  
  /*!< Deselect the EEPROM: Chip Select high */
  uni_set_cs_high(device);
  
  return 0;
}

uint8_t uni_ReadByte(uint8_t device)
{
  return (uni_SendByte(uni_DUMMY_BYTE, device));
}


uint8_t uni_SendByte(uint8_t byte, uint8_t device)
{
  /*!< Loop while DR register in not empty */
  while (SPI_I2S_GetFlagStatus(uni_SPI, SPI_I2S_FLAG_TXE) == RESET);

  /*!< Send byte through the SPI peripheral */
  SPI_SendData(uni_SPI, byte);

  /*!< Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(uni_SPI, SPI_I2S_FLAG_RXNE) == RESET);

  /*!< Return the byte read from the SPI bus */
  return (uint8_t)SPI_ReceiveData(uni_SPI);
}

uint8_t uni_ReadStatusRegister(uint8_t addr, uint8_t device)
{
  uint8_t unistatus = 0;
  
  /*!< Select the EEPROM: Chip Select low */
  uni_set_cs_low(device);
  
  /*!< Send "Read Status Register" instruction */
  unistatus = uni_SendByte((addr << 1) | 0x01,device);
	unistatus = uni_SendByte(uni_DUMMY_BYTE,device);
    
  /*!< Deselect the EEPROM: Chip Select high */
  uni_set_cs_high(device);  
  
  return unistatus;
}

void uni_WriteStatusRegister(uint8_t addr, uint8_t byte, uint8_t device)
{ 
  /*!< Select the EEPROM: Chip Select low */
  uni_set_cs_low(device);
  
  /*!< Send "Read Status Register" instruction */
  uni_SendByte((addr << 1) | 0x00,device);
	uni_SendByte(byte,device);
    
  /*!< Deselect the EEPROM: Chip Select high */
  uni_set_cs_high(device);
}

void uni_set_cs_low(uint8_t device)
{
	switch (device)
	{
		case DEVICE_MASTER:
			uni_CS_LOW(); break;
		case DEVICE_AUX_A:
			uni_CS_LOW_AUX_A(); break;
		case DEVICE_AUX_B:
			uni_CS_LOW_AUX_B(); break;
	}
}
void uni_set_cs_high(uint8_t device)
{
	switch (device)
	{
		case DEVICE_MASTER:
			uni_CS_HIGH(); break;
		case DEVICE_AUX_A:
			uni_CS_HIGH_AUX_A(); break;
		case DEVICE_AUX_B:
			uni_CS_HIGH_AUX_B(); break;
	}
}
