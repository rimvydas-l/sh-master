#include "data.h"

//static SCOPE_t scopeData;
//static CURRENT_DATA_t currentData;

void data_Init(void)
{
	//find scope
	scopeData.inputAddress = 0x20 | 0 << 2 | 0 << 1 | 0; //0x40
	
	//null current data
	currentData.inputStatus = 0;
	currentData.outputStatus = 0;
}