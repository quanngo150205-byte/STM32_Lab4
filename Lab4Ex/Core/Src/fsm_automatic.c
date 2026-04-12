/*
 * fsm_automatic.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#include "fsm_automatic.h"
#include "display_lcd.h"

int lcd_blink_state_internal = 0;

void fsm_automatic_run(){
	// ================= UI LCD UPDATE ================= //
	if (status >= RED_GREEN && status <= AMBER_RED) {
		if (isTimerExpired(TIMER_LCD_UPDATE)) {
			const char* c1 = ""; 
			const char* c2 = "";
			if (status == RED_GREEN) { c1 = "RED"; c2 = "GREEN"; }
			else if (status == RED_AMBER) { c1 = "RED"; c2 = "AMBER"; }
			else if (status == GREEN_RED) { c1 = "GREEN"; c2 = "RED"; }
			else if (status == AMBER_RED) { c1 = "AMBER"; c2 = "RED"; }

			if (flagPedDisplay) {
				if (isTimerExpired(TIMER_LCD_BLINK)) {
					lcd_blink_state_internal = 1 - lcd_blink_state_internal;
					setTimer(TIMER_LCD_BLINK, PERIOD_LCD_BLINK);
				}
				if (lcd_blink_state_internal) {
					lcd_ui_pedestrian_warning();
				} else {
					lcd_ui_auto(c1, getTimerCounter(TIMER_COUNTDOWN_1) * TICK / 1000, 
								c2, getTimerCounter(TIMER_COUNTDOWN_2) * TICK / 1000);
				}
			} else {
				lcd_ui_auto(c1, getTimerCounter(TIMER_COUNTDOWN_1) * TICK / 1000, 
							c2, getTimerCounter(TIMER_COUNTDOWN_2) * TICK / 1000);
			}
			setTimer(TIMER_LCD_UPDATE, PERIOD_LCD_UPDATE);
		}
	}
	// =================================================== //

	switch (status){
			case INIT:
				if (flagchangeMode){
					status = RED_GREEN;
					setTimer(TIMER_COUNTDOWN_1, RedTime);
					setTimer(TIMER_COUNTDOWN_2, GreenTime);
					setTimer(TIMER_DISPLAY_7SEG, 40);
					setTimer(TIMER_UPDATE_BUFFER, 10);
					flagchangeMode = 0;
					flagPedDisplay = 0;
				}
				break;
			case RED_GREEN:
				YellowToRed1();
				RedToGreen2();
				if (isTimerExpired(TIMER_UPDATE_BUFFER)){
					updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
					setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
				}
				if (isTimerExpired(TIMER_DISPLAY_7SEG)){
					display7SegLed();
					setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
				}
				if (isTimerExpired(TIMER_COUNTDOWN_2)){
					status = RED_AMBER;
					setTimer(TIMER_COUNTDOWN_2, AmberTime);
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
					flagPedDisplay = 0;
				}
				break;
			case RED_AMBER:
				GreenToYellow2();
				if (isTimerExpired(TIMER_UPDATE_BUFFER)){
					updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
					setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
				}
				if (isTimerExpired(TIMER_DISPLAY_7SEG)){
					display7SegLed();
					setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
				}
				if (isTimerExpired(TIMER_COUNTDOWN_1)){
					status = GREEN_RED;
					setTimer(TIMER_COUNTDOWN_1, GreenTime);
					setTimer(TIMER_COUNTDOWN_2, RedTime);
					// Phep mau: Huy co khi tuyen 2 da an toan chuyen qua do
					if (pedDisplayRoad == 2) flagPedDisplay = 0;
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
					flagPedDisplay = 0;
				}
				break;
			case GREEN_RED:
				RedToGreen1();
				YellowToRed2();
				if (isTimerExpired(TIMER_UPDATE_BUFFER)){
					updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
					setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
				}
				if (isTimerExpired(TIMER_DISPLAY_7SEG)){
					display7SegLed();
					setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
				}
				if (isTimerExpired(TIMER_COUNTDOWN_1)){
					status = AMBER_RED;
					setTimer(TIMER_COUNTDOWN_1, AmberTime);
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
					flagPedDisplay = 0;
				}
				break;
			case AMBER_RED:
				GreenToYellow1();
				if (isTimerExpired(TIMER_UPDATE_BUFFER)){
					updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
					setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
				}
				if (isTimerExpired(TIMER_DISPLAY_7SEG)){
					display7SegLed();
					setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
				}
				if (isTimerExpired(TIMER_COUNTDOWN_1)){
					status = RED_GREEN;
					setTimer(TIMER_COUNTDOWN_1, RedTime);
					setTimer(TIMER_COUNTDOWN_2, GreenTime);
					// Huy co xin qua duong khi tuyen 1 da chuyen DO
					if (pedDisplayRoad == 1) flagPedDisplay = 0;
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
					flagPedDisplay = 0;
				}
				break;
			default:
				break;
			}
}
