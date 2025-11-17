/*
 * software_timer.c
 *
 *  Created on: Sep 28, 2025
 *      Author: ngoqu
 */

#include "software_timer.h"


int timer_counter[TIMER_SIZE] = {0};
int timer_flag[TIMER_SIZE] = {0};


void setTimers(int duration) {
    int ticks = duration / TICK;
    for (int i = 0; i < TIMER_SIZE; ++i) {
        timer_counter[i] = ticks;
        timer_flag[i] = 0;
    }
}



void setTimer(int index, int duration) {
    if (index < 0 || index >= TIMER_SIZE) return;
    timer_counter[index] = duration / TICK;
    timer_flag[index] = 0;
}


void timer_run(void) {
    for (int i = 0; i < TIMER_SIZE; ++i) {
        if (timer_counter[i] > 0) {
            timer_counter[i]--;
            if (timer_counter[i] <= 0) {
                timer_flag[i] = 1;
            }
        }
    }
}



int isTimerExpired(int index) {
    if (index < 0 || index >= TIMER_SIZE) return 0;
    return timer_flag[index];
}


int getTimerCounter(int index){
    if (index < 0 || index >= TIMER_SIZE) return 0;
    return timer_counter[index];
}
