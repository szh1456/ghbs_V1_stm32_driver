#include "ltc6952_aux.h"
#include <stdio.h>

uint8_t ltc6952_aux_isConsistent(uint8_t* tx_buffer,uint8_t* rx_buffer, uint8_t len, uint8_t device)
{
	uint8_t status = 0;
	for (int i = 0; i < len; i++)
		if (tx_buffer[i] != rx_buffer[i])
			status++;
		return (status > 0)?0:1;
}

uint8_t ltc6952_aux_detect(uint8_t device)
{
	uint8_t ver;
	ver = uni_ReadStatusRegister(LTC6952_VER, device);
	if (ver & LTC6952_VER_MASK)
		printf("[%d.0.0] LTC6952 auxillary %d detected. Version and revision: 0x%02X\r\n", device+1, device, ver);
	else
		printf("[%d.0.0] LTC6952 auxillary %d NOT detected. Output: 0x%02X\r\n", device+1, device, ver);
	return ver;
}
uint8_t ltc6952_aux_isOkay(uint8_t device, uint8_t print)
{
	uint8_t stat;
	stat = uni_ReadStatusRegister(LTC6952_STAT,device);
	if (stat & LTC6952_AUX_STAT_MASK)
	{
		
		if (print)
			printf("[%d.0.0] LTC6952 auxillary %d STAT OK.\r\n", device+1, device);
		stat = 1;
	}
	else
	{
		if (print)
			printf("[%d.0.0] LTC6952 auxillary %d STAT ERROR. Output: 0x%02X\r\n",device+1, device,stat);
		stat = 0;
	}
	return stat;
}

void ltc6952_aux_config_global(uint8_t device, uint16_t pd)
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	pd = (~pd) & 0x07FF;
	
	tx_buffer[0] = 0x2A;
	tx_buffer[1] = 0x00;
	tx_buffer[2] = ((pd >> 10) & 0x01) * (0x03) + ((pd >> 9) & 0x01) * (0x0C) + ((pd >> 8) & 0x01) * (0x30) + ((pd >> 7) & 0x01) * (0xC0);
	tx_buffer[3] = ((pd >> 6) & 0x01) * (0x03) + ((pd >> 5) & 0x01) * (0x0C) + ((pd >> 4) & 0x01) * (0x30) + ((pd >> 3) & 0x01) * (0xC0);
	tx_buffer[4] = ((pd >> 2) & 0x01) * (0x03) + ((pd >> 1) & 0x01) * (0x0C) + ((pd) & 0x01) * (0x30);
	
	printf("[%d.0.0] LTC6952 auxillary %d Global Config:\r\n",device+1, device);
	for (int i = 0; i < LTC6952_AUX_GLOBAL_LEN; i++)
		printf("[%d.0.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n",device+1, LTC6952_AUX_GLOBAL_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6952_AUX_GLOBAL_ADDR, LTC6952_AUX_GLOBAL_LEN,device);
	uni_ReadBuffer(rx_buffer, LTC6952_AUX_GLOBAL_ADDR, LTC6952_AUX_GLOBAL_LEN,device);
	if (ltc6952_aux_isConsistent(tx_buffer,rx_buffer,LTC6952_AUX_GLOBAL_LEN,device))
		printf("[%d.0.1] Setting successful. Consistency verified.\r\n",device+1);
	else
	{
		printf("[%d.0.1] Setting error. Consistency not met.\r\n", device+1);
		for (int i = 0; i < LTC6952_AUX_GLOBAL_LEN; i++)
			printf("[%d.0.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", device+1, LTC6952_AUX_GLOBAL_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
}

void ltc6952_aux_config_srq(uint8_t device)
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	
	tx_buffer[0] = 0xCC;
	tx_buffer[1] = 0x01;
	tx_buffer[2] = 0x00;
	tx_buffer[3] = 0x14;//h'28=d'40
	tx_buffer[4] = 0x05;
	tx_buffer[5] = 0x00;
	
	printf("[%d.1.0] LTC6952 auxillary %d SRQ Config:\r\n",device+1, device);
	for (int i = 0; i < LTC6952_AUX_SRQ_LEN; i++)
		printf("[%d.1.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n",device+1, LTC6952_AUX_SRQ_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6952_AUX_SRQ_ADDR, LTC6952_AUX_SRQ_LEN,device);
	uni_ReadBuffer(rx_buffer, LTC6952_AUX_SRQ_ADDR, LTC6952_AUX_SRQ_LEN,device);
	if (ltc6952_aux_isConsistent(tx_buffer,rx_buffer,LTC6952_AUX_SRQ_LEN,device))
		printf("[%d.1.1] Setting successful. Consistency verified.\r\n",device+1);
	else
	{
		printf("[%d.1.1] Setting error. Consistency not met.\r\n",device+1);
		for (int i = 0; i < LTC6952_AUX_SRQ_LEN; i++)
			printf("[%d.1.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n",device+1, LTC6952_AUX_SRQ_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
}

void ltc6952_aux_config_out_dclk(uint8_t device, uint16_t ddel, uint8_t out_num, uint8_t analogdelay)
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	uint8_t target_addr;
	target_addr = LTC6952_AUX_OUT_0_ADDR + LTC6952_AUX_OUT_LEN * out_num; 
	
	tx_buffer[0] = 0x99;
	tx_buffer[1] = 0x80 + (uint8_t)(ddel >> 8) ;
	tx_buffer[2] = 0x00 + (uint8_t)(ddel & 0x00FF);
	tx_buffer[3] = 0x00 + (analogdelay & 0x3F);
	
	printf("\r\n[%d.2.0] LTC6952 auxillary %d OUT_%d Config:\r\n", device+1, device, out_num);
	printf("[%d.2.0] This is a DCLOCK with delay of %d VCO half-cycles.\r\n", device+1, ddel);
	for (int i = 0; i < LTC6952_AUX_OUT_LEN; i++)
		printf("[%d.2.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", device+1, target_addr + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, target_addr, LTC6952_AUX_OUT_LEN,device);
	uni_ReadBuffer(rx_buffer, target_addr, LTC6952_AUX_OUT_LEN,device);
	if (ltc6952_aux_isConsistent(tx_buffer,rx_buffer,LTC6952_AUX_OUT_LEN,device))
		printf("[%d.2.1] Setting successful. Consistency verified.\r\n", device+1);
	else
	{
		printf("[%d.2.1] Setting error. Consistency not met.\r\n", device+1);
		for (int i = 0; i < LTC6952_AUX_OUT_LEN; i++)
			printf("[%d.2.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", device+1, target_addr + i, tx_buffer[i], rx_buffer[i]);
	}
}
void ltc6952_aux_config_out_sysref(uint8_t device, uint16_t ddel, uint8_t out_num)
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	uint8_t target_addr;
	target_addr = LTC6952_AUX_OUT_0_ADDR + LTC6952_AUX_OUT_LEN * out_num; 
	
	tx_buffer[0] = 0x9C;
	tx_buffer[1] = 0xE0 + (uint8_t)(ddel >> 8) ;
	tx_buffer[2] = 0x00 + (uint8_t)(ddel & 0x00FF);
	tx_buffer[3] = 0x00;
	
	printf("\r\n[%d.2.0] LTC6952 auxillary %d OUT_%d Config:\r\n", device+1, device, out_num);
	printf("[%d.2.0] This is a SYSREF with delay of %d VCO half-cycles.\r\n", device+1, ddel);
	for (int i = 0; i < LTC6952_AUX_OUT_LEN; i++)
		printf("[%d.2.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", device+1, target_addr + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, target_addr, LTC6952_AUX_OUT_LEN,device);
	uni_ReadBuffer(rx_buffer, target_addr, LTC6952_AUX_OUT_LEN,device);
	if (ltc6952_aux_isConsistent(tx_buffer,rx_buffer,LTC6952_AUX_OUT_LEN,device))
		printf("[%d.2.1] Setting successful. Consistency verified.\r\n", device+1);
	else
	{
		printf("[%d.2.1] Setting error. Consistency not met.\r\n", device+1);
		for (int i = 0; i < LTC6952_AUX_OUT_LEN; i++)
			printf("[%d.2.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", device+1, target_addr + i, tx_buffer[i], rx_buffer[i]);
	}
}
