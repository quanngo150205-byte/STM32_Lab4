/*
 * fsm_config.c
 *
 *  Created on: Nov 18, 2025
 *      Author: ngoqu
 */

#include "fsm_config.h"

void fsm_config_run(){
	switch (conf_state){
		case CONF_INIT:
			if (isTimerExpired(TIMER_BLINK_LED)){
				ALL_RED_toggle();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}

			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegConfigMode();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}

			if (flagConfigStateChange){
				conf_state = HAND_CONTROL;
				trafState = START;
				clear7Seg();
				clearAllLed();
				flagConfigStateChange = 0;
			}
			break;
		case HAND_CONTROL:
			traffic_light_hand_control_run();

			if (flagConfigStateChange){
				conf_state = NIGHT_MODE;
				clear7Seg();
				clearAllLed();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
				flagConfigStateChange = 0;
			}
			break;
		case NIGHT_MODE:
			if (isTimerExpired(TIMER_BLINK_LED)){
				ALL_YELLOW_toggle();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}

			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegConfigMode();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}

			if (flagConfigStateChange){
				conf_state = CONF_INIT;
				clear7Seg();
				clearAllLed();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
				flagConfigStateChange = 0;
			}
			break;
		default:
			break;
	}
}

