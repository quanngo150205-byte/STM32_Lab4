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
        	trafState = START;
            break;
        case MANUAL:
        	trafState = START;
            break;
        case CONFIG:
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
            break;
        case CONFIG:
            break;
        default: break;
    }
}

void fsm_menu_run() {
    static int previousState = 0;

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

void buttonScan() {
    if (isButtonPressed(0)) {
        flagMenuChange = 1;
        switch (status) {
            case INIT:
                nextMenuState = AUTO;
                break;
            case AUTO:
                nextMenuState = MANUAL;
                break;
            case MANUAL:
                nextMenuState = CONFIG;
                break;
            case CONFIG:
                nextMenuState = INIT;
                break;
        }
    }
}
