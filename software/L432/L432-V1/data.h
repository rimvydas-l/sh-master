#ifndef __DATA_H__
#define __DATA_H__

#include "stm32l4xx_hal.h"

typedef struct {
	uint8_t inputAddress;
	uint8_t outputAddress;
	uint16_t enabledInputs;
	uint16_t enabledOutputs;
	uint16_t mapping[16];
} SCOPE_t;

typedef struct {
	uint16_t inputStatus;
	uint16_t outputStatus;
} CURRENT_DATA_t;

extern SCOPE_t scopeData;
extern CURRENT_DATA_t currentData;
extern CURRENT_DATA_t setData;

void data_Init(void);


#endif //__DATA_H__
