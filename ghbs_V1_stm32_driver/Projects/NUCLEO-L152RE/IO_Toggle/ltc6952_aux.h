#include "uni_spi.h"

#define LTC6952_AUX_GLOBAL_ADDR 0x01
#define LTC6952_AUX_GLOBAL_LEN 5

#define LTC6952_AUX_SRQ_ADDR 0x06
#define LTC6952_AUX_SRQ_LEN 6

#define LTC6952_AUX_OUT_0_ADDR 0x0C
#define LTC6952_AUX_OUT_LEN 4


#define BUFFER_SIZE 16

#define LTC6952_AUX_STAT_MASK 0x15

uint8_t ltc6952_aux_detect(uint8_t device);
uint8_t ltc6952_aux_isOkay(uint8_t device, uint8_t print);
void ltc6952_aux_config_global(uint8_t device, uint16_t pd);
void ltc6952_aux_config_srq(uint8_t device);
void ltc6952_aux_config_out_dclk(uint8_t device, uint16_t ddel, uint8_t out_num, uint8_t analogdelay);
void ltc6952_aux_config_out_sysref(uint8_t device, uint16_t ddel, uint8_t out_num);
