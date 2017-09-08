#ifndef LCD_H
#define LCD_H
#include "LiquidCrystal_I2C.h"

// Number of characters LCD can handle
const int LCD_X = 16;
const int LCD_Y = 2;
LiquidCrystal_I2C lcd(0x27, LCD_X, LCD_Y);  // set the LCD address to 0x27 for 16 chars and 2 line display
uint8_t EURO_SYMBOL[8] = {0x3,0x4,0x1e,0x8,0x1e,0x8,0x7}; // Euro symbol for lcd

const char INIT_MESSAGE[LCD_X] = "SO HUNGRY.";
const char GENERAL_MESSAGE[LCD_X] = "Coin donations!";
const char TOTAL_MESSAGE[LCD_X] = "Total:";
#endif
