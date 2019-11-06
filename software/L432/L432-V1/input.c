#include "input.h"

extern I2C_HandleTypeDef hi2c1;

void input_init(void)
{
	mcp23017_init(&hmcp_input, &hi2c1, MCP23017_ADDRESS_20);
	
	mcp23017_mirror_int(&hmcp_input);
	
	mcp23017_iodir(&hmcp_input, MCP23017_PORTA, MCP23017_IODIR_ALL_INPUT);
	mcp23017_iodir(&hmcp_input, MCP23017_PORTB, MCP23017_IODIR_ALL_INPUT);
	
	mcp23017_int_en(&hmcp_input, MCP23017_PORTA, 0xFF);
	mcp23017_int_en(&hmcp_input, MCP23017_PORTB, 0xFF);

	input_read();
	currentData.inputStatus = setData.inputStatus;
}

void input_read(void)
{
	mcp23017_read_gpio(&hmcp_input, MCP23017_PORTA);
	mcp23017_read_gpio(&hmcp_input, MCP23017_PORTB);

	setData.inputStatus = hmcp_input.gpio[0] << 8 | hmcp_input.gpio[1];

}