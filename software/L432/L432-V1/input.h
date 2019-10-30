#ifndef __INPUT_H__
#define __INPUT_H__

#include "stm32l4xx_hal.h"
#include "mcp23017.h"
#include "data.h"

extern MCP23017_HandleTypeDef hmcp_input;

void input_init(void);
void input_read(void);

#endif //__INPUT_H__
