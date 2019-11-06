#include "data.h"

//static SCOPE_t scopeData;
//static CURRENT_DATA_t currentData;

void data_Init(void)
{
	//find scope
	scopeData.inputAddress = 0x20 | 0 << 2 | 0 << 1 | 0; //0x40
	
	//null current data
	currentData.inputStatus = 0;
	currentData.outputStatus = 0x2;
	setData.outputStatus = 0x2;
	
	
	scopeData.enabledInputs = 0xFF00;
	scopeData.enabledOutputs = 0x00FF;

	//	scopeData.mapping[0] = 0x1;
//	scopeData.mapping[1] = 0x2;
//	scopeData.mapping[2] = 0x4;
//	scopeData.mapping[3] = 0x8;
//	scopeData.mapping[4] = 0x10;
//	scopeData.mapping[5] = 0x20;
//	scopeData.mapping[6] = 0x40;
//	scopeData.mapping[7] = 0x80;
//	scopeData.mapping[8] = 0x100;
//	scopeData.mapping[9] = 0x200;
//	scopeData.mapping[10] = 0x400;
//	scopeData.mapping[11] = 0x800;
//	scopeData.mapping[12] = 0x1000;
//	scopeData.mapping[13] = 0x2000;
//	scopeData.mapping[14] = 0x4000;
	scopeData.mapping[15] = 0x7;

}