/*
 * display_lcd.h
 *
 *  Created on: Apr 13, 2026
 *      Author: ngoqu
 */

#ifndef INC_DISPLAY_LCD_H_
#define INC_DISPLAY_LCD_H_

#include "i2c_lcd.h"

void display_lcd_init(void);

// Auto Mode APIs
void lcd_ui_auto(const char* color1, int val1, const char* color2, int val2);
void lcd_ui_pedestrian_warning(void);

// Manual Mode API
void lcd_ui_manual(const char* color1, const char* color2);

// Config Mode API
void lcd_ui_config(const char* mode_str, int time_val);

#endif /* INC_DISPLAY_LCD_H_ */
