/*
 * button_event.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */

#include "button_event.h"

void getNextMenuStatus() {
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
            default:
            	break;
        }
    }
}


void getManualEvent(){
	if (status == MANUAL){
		if (isButtonPressed(1) || isButtonLongPressed(1)){
			manEvt = EV_INC;
		}
		else if (isButtonPressed(2) || isButtonLongPressed(2)){
			manEvt = EV_DEC;
		}
		else if (isButtonDoubleClicked(2)){
			manEvt = EV_NEXT_MODE;
		}
	}
}


void getNextConfigState(){
	if (status == CONFIG){
		if (isButtonDoubleClicked(1)){
			flagConfigStateChange = 1;
		}
	}
}

