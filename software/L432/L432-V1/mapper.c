#include "mapper.h"

void map_input(void)
{
	uint8_t i;
	uint16_t change;
	change = setData.inputStatus ^ currentData.inputStatus;
	if (change) {
		for (i = 0; i < 16; i++) 
		{
			if ((change >> i) & 1U) {
				setData.outputStatus ^= scopeData.mapping[i];
			}
		}
		currentData.inputStatus = setData.inputStatus;
		map_output();
	}
}

void map_output(void) 
{
	currentData.outputStatus = setData.outputStatus & scopeData.enabledOutputs;
}
