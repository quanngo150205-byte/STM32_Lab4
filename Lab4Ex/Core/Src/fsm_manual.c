/*
 * fsm_manual.c
 *
 *  Created on: Nov 17, 2025
 *      Author: ngoqu
 */


#include "fsm_manual.h"

int red_time = 0;
int yellow_time = 0;
int green_time = 0;

void fsm_manual_run(){
    switch(man_state){
    case MAN_RED:
        if (isTimerExpired(TIMER_BLINK_LED)){
        	ALL_RED_toggle();
            setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
        }
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(red_time * 100, (MAN_RED - 10) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
        }

        switch(manEvt){
            case EV_INC:
                if (red_time < 99) red_time++;
                break;
            case EV_DEC:
                if (red_time > 1) red_time--;
                break;
            case EV_NEXT_MODE:
                clearAllLed();
                man_state = MAN_YELLOW;
                setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
                break;
            default:
                break;
        }
        manEvt = EV_NONE;
        break;

    case MAN_YELLOW:
        if (isTimerExpired(TIMER_BLINK_LED)){
            ALL_YELLOW_toggle();
            setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
        }
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(yellow_time * 100, (MAN_YELLOW - 10) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
        }

        switch(manEvt){
            case EV_INC:
                if (yellow_time < red_time) yellow_time++;
                break;
            case EV_DEC:
                if (yellow_time > 1) yellow_time--;
                break;
            case EV_NEXT_MODE:
                clearAllLed();
                man_state = MAN_GREEN;
                setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
                break;
            default:
                break;
        }
        manEvt = EV_NONE;
        break;

    case MAN_GREEN:
        if (isTimerExpired(TIMER_BLINK_LED)){
            ALL_GREEN_toggle();
            setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
        }
        if (isTimerExpired(TIMER_UPDATE_BUFFER)){
            updateTimerBuffer(green_time * 100, (MAN_GREEN - 10) * 100);
            setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
        }
        if (isTimerExpired(TIMER_DISPLAY_7SEG)){
            display7SegLed();
            setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
        }

        switch(manEvt){
            case EV_INC:
                if (green_time < red_time - yellow_time) green_time++;
                break;
            case EV_DEC:
                if (green_time > 1) green_time--;
                break;
            case EV_NEXT_MODE:
                clearAllLed();
                trafState = START;
                man_state = MAN_RUN;
                break;
            default:
                break;
        }
        manEvt = EV_NONE;
        break;

    case MAN_RUN:
        traffic_light_autorun(red_time*1000, yellow_time*1000, green_time*1000);
        break;

    default:
        break;
    }
}
