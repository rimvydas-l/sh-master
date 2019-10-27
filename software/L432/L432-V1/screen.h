#ifndef __SCREEN_H__
#define __SCREEN_H__

#define INPUT_RECTANGLE_WIDTH 7
#define INPUT_RECTANGLE_HEIGHT 5
#define INPUT_RECTANGLE_SPACING 1

#include "ssd1306.h"
#include "data.h"

void screen_init(void);
void screen_draw(CURRENT_DATA_t* currentData, SCOPE_t* scopeData);

#endif //__SCREEN_H__
