/*
 * fsm_menu.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */

#include "fsm_menu.h"


static void doEntry(int state) {
    switch(state) {
        case INIT:
            clearAllLed();
            clear7Seg();
            break;
        case AUTO:
        	clear7Seg();
        	clearAllLed();
        	trafState = START;
            break;
        case MANUAL:
        	clear7Seg();
        	clearAllLed();
        	man_state = MAN_RED;
        	trafState = START;
            break;
        case CONFIG:
        	clear7Seg();
        	clearAllLed();
        	trafState = START;
            break;
        default: break;
    }
}

static void doAction(int state) {
    switch (state) {
        case INIT:
            break;
        case AUTO:
        	fsm_automatic_run();
            break;
        case MANUAL:
        	fsm_manual_run();
            break;
        case CONFIG:
            break;
        default: break;
    }
}

void fsm_menu_run() {
    static int previousState = 0;

    if (isTimerExpired(TIMER_FOR_LED_PA5)){
    	LED_PA5_toggle();
    	setTimer(TIMER_FOR_LED_PA5, LED_PA5_CYCLE);
    }

    // Entry logic
    if (previousState != status) {
        doEntry(status);
        previousState = status;
    }

    // Action logic
    doAction(status);

    // Transition logic
    if (flagMenuChange) {
        status = nextMenuState;
        flagMenuChange = 0;
    }
}

