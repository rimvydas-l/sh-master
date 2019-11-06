#include "screen.h"

void draw_Rectangle(uint8_t x, uint8_t y, uint16_t enabled, uint16_t filled);
void draw_Separator();
void draw_Mapping(uint16_t* mapping);
void draw_MappingElement(uint8_t x, uint8_t y, uint16_t filled);


void screen_init(void)
{
	ssd1306_Init();
	ssd1306_Fill(0);
	ssd1306_UpdateScreen();
}

void screen_draw(CURRENT_DATA_t* currentData, SCOPE_t* scopeData)
{
	uint8_t i;
	
	ssd1306_Fill(Black);
	draw_Separator();
	draw_Mapping(scopeData->mapping);
	
	for (i = 0; i < 16; i++)
	{
		draw_Rectangle(i * (INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING), 0, scopeData->enabledInputs & 1 << i, currentData->inputStatus & 1 << i);
	}
	
	for (i = 0; i < 16; i++)
	{
		draw_Rectangle(i * (INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING), INPUT_RECTANGLE_HEIGHT + 5, scopeData->enabledOutputs & 1 << i, currentData->outputStatus & 1 << i);
	}
	
	ssd1306_UpdateScreen();
}

void draw_Rectangle(uint8_t x, uint8_t y, uint16_t enabled, uint16_t filled)
{
	uint8_t i, j;
	SSD1306_COLOR frameColor = (enabled == 0) ? Black : White;
	SSD1306_COLOR color = (filled == 0) ? Black : frameColor;
	for (i = 0; i < INPUT_RECTANGLE_WIDTH; i++) {
		for (j = 0; j < INPUT_RECTANGLE_HEIGHT; j++) {
			if (i == 0 || i == INPUT_RECTANGLE_WIDTH - 1 || j == 0 || j == INPUT_RECTANGLE_HEIGHT - 1) {
				ssd1306_DrawPixel(x + i, y + j, frameColor);
			}
			else {
				ssd1306_DrawPixel(x + i, y + j, color);
			}
		}
	}
}

void draw_Separator()
{
	uint8_t i;

	ssd1306_DrawPixel(0, INPUT_RECTANGLE_HEIGHT + 1, White);
	ssd1306_DrawPixel(0, INPUT_RECTANGLE_HEIGHT + 3, White);
	
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 4 - 1, INPUT_RECTANGLE_HEIGHT + 1, White);
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 4 - 1, INPUT_RECTANGLE_HEIGHT + 3, White);
	
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 8 - 1, INPUT_RECTANGLE_HEIGHT + 1, White);
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 8 - 1, INPUT_RECTANGLE_HEIGHT + 3, White);
	
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 12 - 1, INPUT_RECTANGLE_HEIGHT + 1, White);
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 12 - 1, INPUT_RECTANGLE_HEIGHT + 3, White);
	
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 16 - 2, INPUT_RECTANGLE_HEIGHT + 1, White);
	ssd1306_DrawPixel((INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 16 - 2, INPUT_RECTANGLE_HEIGHT + 3, White);

	for (i = 0; i < (INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING) * 16 - 1; i++)
	{
		ssd1306_DrawPixel(i, INPUT_RECTANGLE_HEIGHT + 2, White);
	}
}

void draw_Mapping(uint16_t* mapping)
{
	uint8_t i, j;

	uint8_t baseHeight = INPUT_RECTANGLE_HEIGHT * 2 + 6;
	
	for (i = 0; i < 16; i++) {
		if ((scopeData.enabledInputs >> i) & 1U) {
			for (j = 0; j < 16; j++) {
				if ((scopeData.enabledOutputs >> (15-j)) & 1U) {
					draw_MappingElement(i * (INPUT_RECTANGLE_WIDTH + INPUT_RECTANGLE_SPACING), j * 3 + baseHeight, mapping[i] & 1 << (15 - j));
				}
			}
		}
	}
}

void draw_MappingElement(uint8_t x, uint8_t y, uint16_t filled)
{
	uint8_t i;
	SSD1306_COLOR color = (filled == 0) ? Black : White;
	
	for (i = 0; i < INPUT_RECTANGLE_WIDTH; i++)
	{
		ssd1306_DrawPixel(x + i, y, White);
		if (i == 0) {
			ssd1306_DrawPixel(x + i, y + 1, White);
		}
		else {
			ssd1306_DrawPixel(x + i, y + 1, color);
		}
	}
}