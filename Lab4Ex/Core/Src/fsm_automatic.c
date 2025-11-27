/*
 * fsm_automatic.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	switch (status){
			case INIT:
				if (flagchangeMode){
					status = RED_GREEN;
					setTimer(TIMER_COUNTDOWN_1, RedTime);
					setTimer(TIMER_COUNTDOWN_2, GreenTime);
					setTimer(TIMER_DISPLAY_7SEG, 40);
					setTimer(TIMER_UPDATE_BUFFER, 10);
					flagchangeMode = 0;
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
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
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
				}
				if (flagchangeMode){
					status = MANUAL;
					setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
					clear7Seg();
					clearAllLed();
					flagchangeMode = 0;
				}
				break;
			default:
				break;
			}
}
