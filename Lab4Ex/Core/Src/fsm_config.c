/*
 * fsm_config.c
 *
 *  Created on: Oct 29, 2025
 *      Author: ngoqu
 */

#include "fsm_config.h"

int red_temp 	= 0;
int amber_temp 	= 0;
int green_temp 	= 0;

void DoAction();

void fsm_config_run(){
	switch (status){
	case CONFIG_RED:
		if (isTimerExpired(TIMER_BLINK_LED)){
			ALL_RED_toggle();
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
		}
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(red_temp * 100, (CONFIG_RED - 20) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
        }
        if (isButtonLongPressed(1) || isButtonPressed(1)){
            if (red_temp < 100){
                red_temp++;
            }
        }
        if (isButtonLongPressed(2) || isButtonPressed(2)){
            if (red_temp > 2){
                red_temp--;
            }
        }
        if (flagcontrolConfig){
        	status = CONFIG_AMBER;
        	clearAllLed();
        	flagcontrolConfig = 0;
        }
		if (flagchangeMode){
			status = RED_GREEN;
		    setTimer(TIMER_COUNTDOWN_1, RedTime);
		    setTimer(TIMER_COUNTDOWN_2, GreenTime);
		    setTimer(TIMER_DISPLAY_7SEG, 40);
		    setTimer(TIMER_UPDATE_BUFFER, 10);
			flagchangeMode = 0;
		}
		break;
	case CONFIG_AMBER:
		if (isTimerExpired(TIMER_BLINK_LED)){
			ALL_YELLOW_toggle();
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
		}
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(amber_temp * 100, (CONFIG_AMBER - 20) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
        }
        if (isButtonLongPressed(1) || isButtonPressed(1)){
            if (amber_temp < red_temp){
                amber_temp++;
            }
        }
        if (isButtonLongPressed(2) || isButtonPressed(2)){
            if (amber_temp > 1){
                amber_temp--;
            }
        }
        if (flagcontrolConfig){
        	status = CONFIG_GREEN;
        	clearAllLed();
        	flagcontrolConfig = 0;
        }
		if (flagchangeMode){
			status = RED_GREEN;
		    setTimer(TIMER_COUNTDOWN_1, RedTime);
		    setTimer(TIMER_COUNTDOWN_2, GreenTime);
		    setTimer(TIMER_DISPLAY_7SEG, 40);
		    setTimer(TIMER_UPDATE_BUFFER, 10);
			flagchangeMode = 0;
		}
		break;
	case CONFIG_GREEN:
		if (isTimerExpired(TIMER_BLINK_LED)){
			ALL_GREEN_toggle();
			setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
		}
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(green_temp * 100, (CONFIG_GREEN - 20) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG);
        }
        if (isButtonLongPressed(1) || isButtonPressed(1)){
            if (green_temp < red_temp - amber_temp){
                green_temp++;
            }
        }
		if (flagcontrolConfig){
		    status 		= RED_GREEN;
		    RedTime 	= red_temp * 1000;
		    AmberTime 	= amber_temp * 1000;
		    GreenTime	= green_temp * 1000;
		    setTimer(TIMER_COUNTDOWN_1, RedTime);
		    setTimer(TIMER_COUNTDOWN_2, GreenTime);
		    setTimer(TIMER_DISPLAY_7SEG, 40);
		    setTimer(TIMER_UPDATE_BUFFER, 10);
		    clearAllLed();
		    flagcontrolConfig = 0;
		}
		if (flagchangeMode){
			status = RED_GREEN;
		    setTimer(TIMER_COUNTDOWN_1, RedTime);
		    setTimer(TIMER_COUNTDOWN_2, GreenTime);
		    setTimer(TIMER_DISPLAY_7SEG, 40);
		    setTimer(TIMER_UPDATE_BUFFER, 10);
			flagchangeMode = 0;
		}
		break;
	default:
		break;
	}
}
