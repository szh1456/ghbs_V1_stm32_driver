#include "ltc6953_master.h"
#include <stdio.h>

uint8_t ltc6953_master_isConsistent(uint8_t* tx_buffer,uint8_t* rx_buffer, uint8_t len)//check consistency by read/write from/to the same register
{
	uint8_t status = 0;
	for (int i = 0; i < len; i++)
		if (tx_buffer[i] != rx_buffer[i])
			status++;
		return (status > 0)?0:1;
}

uint8_t ltc6953_master_detect(void)//detect chip by reading the model version
{
	uint8_t ver;
	ver = uni_ReadStatusRegister(LTC6952_VER, DEVICE_MASTER);
	if (ver & LTC6952_VER_MASK)
		printf("[1.0.0] LTC695x master detected. Version and revision: 0x%02X\r\n",ver);
	else
		printf("[1.0.0] LTC695x master NOT detected. Output: 0x%02X\r\n",ver);
	return ver;
}
uint8_t ltc6953_master_isOkay(void)//check flags
{
	uint8_t stat;
	stat = uni_ReadStatusRegister(LTC6952_STAT,DEVICE_MASTER);
	if (stat & LTC6953_MASTER_STAT_MASK)
		printf("[1.0.0] LTC695x master VCO OK.\r\n");
	else
		printf("[1.0.0] LTC695x master VCO ERROR. Output: 0x%02X\r\n",stat);
	return stat;
}

void ltc6953_master_config_global(void)//set global configs 
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	
	tx_buffer[0] = 0x08;
	tx_buffer[1] = 0x02;
	tx_buffer[2] = 0x00;
	tx_buffer[3] = 0xFF;
	tx_buffer[4] = 0x3F;
	
	printf("[1.0.0] LTC6953 Global Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_GLOBAL_LEN; i++)
		printf("[1.0.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_GLOBAL_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_GLOBAL_ADDR, LTC6953_MASTER_GLOBAL_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_GLOBAL_ADDR, LTC6953_MASTER_GLOBAL_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_GLOBAL_LEN))
		printf("[1.0.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.0.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_GLOBAL_LEN; i++)
			printf("[1.0.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_GLOBAL_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
}

void ltc6953_master_config_srq(void)//set SRQ configs 
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	
	tx_buffer[0] = 0x13;
	tx_buffer[1] = 0x00;
	
	printf("[1.1.0] LTC6953 SRQ Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_SRQ_LEN; i++)
		printf("[1.1.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_SRQ_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_SRQ_ADDR, LTC6953_MASTER_SRQ_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_SRQ_ADDR, LTC6953_MASTER_SRQ_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_SRQ_LEN))
		printf("[1.1.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.1.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_SRQ_LEN; i++)
			printf("[1.1.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_SRQ_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
}

void ltc6953_master_config_outs(void)//set output-specific configs 
{
	uint8_t tx_buffer[BUFFER_SIZE], rx_buffer[BUFFER_SIZE];
	
	tx_buffer[0] = 0x00;
	tx_buffer[1] = 0x80;
	tx_buffer[2] = 0x00;
	tx_buffer[3] = 0x00;
	
	printf("[1.2.0] LTC6953 OUT_0 Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_OUT_0_LEN; i++)
		printf("[1.2.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_OUT_0_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_OUT_0_ADDR, LTC6953_MASTER_OUT_0_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_OUT_0_ADDR, LTC6953_MASTER_OUT_0_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_OUT_0_LEN))
		printf("[1.2.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.2.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_OUT_0_LEN; i++)
			printf("[1.2.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_OUT_0_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
	
	tx_buffer[0] = 0x00;
	tx_buffer[1] = 0xC0;
	tx_buffer[2] = 0x0E;
	tx_buffer[3] = 0x00;
	
	printf("[1.3.0] LTC6953 OUT_1 Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_OUT_1_LEN; i++)
		printf("[1.3.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_OUT_1_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_OUT_1_ADDR, LTC6953_MASTER_OUT_1_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_OUT_1_ADDR, LTC6953_MASTER_OUT_1_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_OUT_1_LEN))
		printf("[1.3.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.3.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_OUT_1_LEN; i++)
			printf("[1.3.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_OUT_1_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
	
	tx_buffer[0] = 0x00;
	tx_buffer[1] = 0x80;
	tx_buffer[2] = 0x00;
	tx_buffer[3] = 0x00;
	
	printf("[1.4.0] LTC6953 OUT_2 Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_OUT_2_LEN; i++)
		printf("[1.4.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_OUT_2_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_OUT_2_ADDR, LTC6953_MASTER_OUT_2_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_OUT_2_ADDR, LTC6953_MASTER_OUT_2_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_OUT_2_LEN))
		printf("[1.4.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.4.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_OUT_2_LEN; i++)
			printf("[1.4.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_OUT_2_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
	
	tx_buffer[0] = 0x00;
	tx_buffer[1] = 0xC0;
	tx_buffer[2] = 0x0E;
	tx_buffer[3] = 0x00;
	
	printf("[1.5.0] LTC6953 OUT_3 Config:\r\n");
	for (int i = 0; i < LTC6953_MASTER_OUT_3_LEN; i++)
		printf("[1.5.0] \tADDR\t0x%02X\tVALUE\t0x%02X\r\n", LTC6953_MASTER_OUT_3_ADDR + i, tx_buffer[i]);
	uni_WriteBuffer(tx_buffer, LTC6953_MASTER_OUT_3_ADDR, LTC6953_MASTER_OUT_3_LEN,DEVICE_MASTER);
	uni_ReadBuffer(rx_buffer, LTC6953_MASTER_OUT_3_ADDR, LTC6953_MASTER_OUT_3_LEN,DEVICE_MASTER);
	if (ltc6953_master_isConsistent(tx_buffer,rx_buffer,LTC6953_MASTER_OUT_3_LEN))
		printf("[1.5.1] Setting successful. Consistency verified.\r\n");
	else
	{
		printf("[1.5.1] Setting error. Consistency not met.\r\n");
		for (int i = 0; i < LTC6953_MASTER_OUT_3_LEN; i++)
			printf("[1.5.1] \tADDR\t0x%02X\tTX\t0x%02X\tRX\t0x%02X\r\n", LTC6953_MASTER_OUT_3_ADDR + i, tx_buffer[i], rx_buffer[i]);
	}
}

void ltc6953_master_aux_sync(void)//perform sync for follower chips
{
	printf("[4.0.0] Starting syncing master and auxillaries...");
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_0_ADDR + 1, 0x80, DEVICE_MASTER);// set SRQMOD to 0 to allow sync mode
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_1_ADDR + 1, 0xC0, DEVICE_MASTER);// maybe not necessary
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_2_ADDR + 1, 0x80, DEVICE_MASTER);
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_3_ADDR + 1, 0xC0, DEVICE_MASTER);
	
	//uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x00, DEVICE_MASTER);
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x01, DEVICE_MASTER);//toggle SSRQ, sync ref master
	Delay(10);
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x00, DEVICE_MASTER);//toggle SSRQ
	
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_0_ADDR + 1, 0x00, DEVICE_MASTER);// ref clocks free run !
	uni_WriteStatusRegister(LTC6953_MASTER_OUT_2_ADDR + 1, 0x00, DEVICE_MASTER);
	
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x0C, DEVICE_MASTER);// set SRQMOD to 1 to allow retiming to REF
	Delay(10);
	
	while(!( ltc6952_aux_isOkay(DEVICE_AUX_A,1) && ltc6952_aux_isOkay(DEVICE_AUX_B,1) ) )
	{
		Delay(1);
	}
	
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x01, DEVICE_MASTER);//toggle SSRQ, sync parallel auxs
	Delay(10);
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x00, DEVICE_MASTER);//toggle SSRQ
	printf("\tFinished.\r\n");
}

void ltc6952_aux_lp_sysref(void) //put followers to low-power mode while waiting for SYSREF request
{
	printf("[-.-.-] Putting auxillaries to low-power mode and in the sync mode...\r\n");
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 2, 0x22, DEVICE_AUX_A);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 2, 0x22, DEVICE_AUX_B);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 3, 0x22, DEVICE_AUX_A);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 3, 0x22, DEVICE_AUX_B);
	
	uni_WriteStatusRegister(0x0B, 0x08, DEVICE_AUX_A);
	uni_WriteStatusRegister(0x0B, 0x08, DEVICE_AUX_B);
}

void ltc6952_aux_fp_sysref(void)//put followers to full-power mode while waiting for SYSREF request
{
	printf("[-.-.-] Putting auxillaries to full-power mode and in the sysref req mode...\r\n");
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 2, 0x00, DEVICE_AUX_A);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 2, 0x00, DEVICE_AUX_B);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 3, 0x00, DEVICE_AUX_A);
	uni_WriteStatusRegister(LTC6952_AUX_GLOBAL_ADDR + 3, 0x00, DEVICE_AUX_B);
	
	uni_WriteStatusRegister(0x0B, 0x08, DEVICE_AUX_A);
	uni_WriteStatusRegister(0x0B, 0x08, DEVICE_AUX_B);
	//Delay(1);
}

void ltc6952_perform_sysref(void)// request SYSREF
{	
	printf("[4.0.0] Starting perform sysref request...");
	ltc6952_aux_fp_sysref();
	
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x01, DEVICE_MASTER);//toggle SSRQ, send sysref request
	Delay(2);
	uni_WriteStatusRegister(LTC6953_MASTER_SRQ_ADDR + 1, 0x00, DEVICE_MASTER);//toggle SSRQ
	uni_WriteStatusRegister(0x0B, 0x00, DEVICE_AUX_A);
	uni_WriteStatusRegister(0x0B, 0x00, DEVICE_AUX_B);
	printf("\tFinished.\r\n");
}

