/*
 * Task.c
 *
 *  Created on: Nov 28, 2025
 *      Author: ngoqu
 */

#include "Task.h"

void BlinkLed(){
	if (isTimerExpired(TIMER_FOR_LED_PA5)){
		HAL_GPIO_TogglePin(GPIOA, LED_BLINK_Pin);
		setTimer(TIMER_FOR_LED_PA5, LED_PA5_CYCLE);
	}
}

void fsm_run_all(){
	fsm_automatic_run();
	fsm_manual_run();
	fsm_config_run();
}

void doInit(){
	status = INIT;
	setTimers(100);
	clear7Seg();
	clearAllLed();
}
