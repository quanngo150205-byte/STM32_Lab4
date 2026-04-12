/*
 * display_lcd.c
 *
 *  Created on: Apr 13, 2026
 *      Author: ngoqu
 */

#include "display_lcd.h"
#include <stdio.h>
#include <string.h>

char lcd_buf_1[32];
char lcd_buf_2[32];

void display_lcd_init(void) {
	lcd_init();
}

void lcd_ui_auto(const char* color1, int val1, const char* color2, int val2) {
	sprintf(lcd_buf_1, "R1_%-5s: %02d   ", color1, val1);
	sprintf(lcd_buf_2, "R2_%-5s: %02d   ", color2, val2);
	lcd_goto_XY(1, 0); 
	lcd_send_string(lcd_buf_1);
	lcd_goto_XY(2, 0); 
	lcd_send_string(lcd_buf_2);
}

void lcd_ui_pedestrian_warning(void) {
	lcd_goto_XY(1, 0); 
	lcd_send_string("  XIN QUA DUONG ");
	lcd_goto_XY(2, 0); 
	lcd_send_string("                ");
}

void lcd_ui_manual(const char* color1, const char* color2) {
	lcd_goto_XY(1, 0); 
	lcd_send_string("  MANUAL MODE   ");
	sprintf(lcd_buf_2, "R1:%-3s    R2:%-3s", color1, color2);
	lcd_goto_XY(2, 0); 
	lcd_send_string(lcd_buf_2);
}

void lcd_ui_config(const char* mode_str, int time_val) {
	lcd_goto_XY(1, 0); 
	lcd_send_string("  CONFIG MODE   ");
	sprintf(lcd_buf_2, "SET %s TIME: %02d ", mode_str, time_val);
	lcd_goto_XY(2, 0); 
	lcd_send_string(lcd_buf_2);
}
