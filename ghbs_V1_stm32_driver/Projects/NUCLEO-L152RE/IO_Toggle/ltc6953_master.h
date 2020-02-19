#include "uni_spi.h"
#include "ltc6952_aux.h"
#include "main.h"

#define LTC6953_MASTER_GLOBAL_ADDR 0x01
#define LTC6953_MASTER_GLOBAL_LEN 5

#define LTC6953_MASTER_SRQ_ADDR 0x0A
#define LTC6953_MASTER_SRQ_LEN 2

#define LTC6953_MASTER_OUT_0_ADDR 0x0C
#define LTC6953_MASTER_OUT_0_LEN 4

#define LTC6953_MASTER_OUT_1_ADDR 0x10
#define LTC6953_MASTER_OUT_1_LEN 4

#define LTC6953_MASTER_OUT_2_ADDR 0x14
#define LTC6953_MASTER_OUT_2_LEN 4

#define LTC6953_MASTER_OUT_3_ADDR 0x18
#define LTC6953_MASTER_OUT_3_LEN 4

#define BUFFER_SIZE 16

#define LTC6953_MASTER_STAT_MASK 0x04


void ltc6953_master_config_global(void);
uint8_t ltc6953_master_detect(void);
void ltc6953_master_config_outs(void);
void ltc6953_master_config_srq(void);
uint8_t ltc6953_master_isOkay(void);
void ltc6953_master_aux_sync(void);
void ltc6952_aux_lp_sysref(void);
void ltc6952_aux_fp_sysref(void);
void ltc6952_perform_sysref(void);
