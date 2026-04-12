/*
 * fsm_manual.c
 *
 *  Created on: Oct 29, 2025
 *      Author: ngoqu
 */

#include "fsm_manual.h"
#include "display_lcd.h"

void fsm_manual_run(){
	// ================= UI LCD UPDATE ================= //
	if (status >= MANUAL && status <= MAN_AMBER_RED) {
		if (isTimerExpired(TIMER_LCD_UPDATE)) {
			const char* c1 = ""; const char* c2 = "";
			if (status == MANUAL || status == MAN_RED_GREEN) { c1 = "RED"; c2 = "GRE"; }
			else if (status == MAN_RED_AMBER) { c1 = "RED"; c2 = "AMB"; }
			else if (status == MAN_GREEN_RED) { c1 = "GRE"; c2 = "RED"; }
			else if (status == MAN_AMBER_RED) { c1 = "AMB"; c2 = "RED"; }
			
			lcd_ui_manual(c1, c2);
			setTimer(TIMER_LCD_UPDATE, PERIOD_LCD_UPDATE);
		}
	}
	// =================================================== //

	switch (status){
	case MANUAL:
		if (isTimerExpired(TIMER_BLINK_LED)){
			ALL_YELLOW_toggle();
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
		}
		if (flagcontrolManual){
			status = MAN_RED_GREEN;
			clearAllLed();
			flagcontrolManual = 0;
		}
		if (flagchangeMode){
			status = CONFIG_RED;
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
			clearAllLed();
			flagchangeMode = 0;
			flagPedDisplay = 0;
		}
		break;
	case MAN_RED_GREEN:
		YellowToRed1();
		RedToGreen2();
		if (flagcontrolManual){
			status = MAN_RED_AMBER;
			flagcontrolManual = 0;
		}
		if (flagchangeMode){
			status = CONFIG_RED;
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
			clearAllLed();
			flagchangeMode = 0;
			flagPedDisplay = 0;
		}
		break;
	case MAN_RED_AMBER:
		GreenToYellow2();
		if (flagcontrolManual){
			status = MAN_GREEN_RED;
			flagcontrolManual = 0;
		}
		if (flagchangeMode){
			status = CONFIG_RED;
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
			clearAllLed();
			flagchangeMode = 0;
			flagPedDisplay = 0;
		}
		break;
	case MAN_GREEN_RED:
		YellowToRed2();
		RedToGreen1();
		if (flagcontrolManual){
			status = MAN_AMBER_RED;
			flagcontrolManual = 0;
		}
		if (flagchangeMode){
			status = CONFIG_RED;
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
			clearAllLed();
			flagchangeMode = 0;
			flagPedDisplay = 0;
		}
		break;
	case MAN_AMBER_RED:
		GreenToYellow1();
		if (flagcontrolManual){
			status = MAN_RED_GREEN;
			flagcontrolManual = 0;
		}
		if (flagchangeMode){
			status = CONFIG_RED;
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
			clearAllLed();
			flagchangeMode = 0;
			flagPedDisplay = 0;
		}
		break;
	default:
		break;
	}
}
