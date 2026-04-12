/*
 * crossroad.c
 *
 *  Created on: Apr 12, 2026
 *      Author: ngoqu
 */

#include "crossroad.h"

#define PED_GREEN_MIN_TICKS		500		// 5 giay = 500 ticks (1 tick = 10ms)

void fsm_pedestrian_run(void){
	// Neu khong co yeu cau tu nguoi di bo, thoat ngay
	if (flagPedestrian == 0){
		return;
	}

	// Xoa co de chi xu ly 1 lan
	flagPedestrian = 0;

	int greenCounter = 0;
	int redCounter = 0;
	int diff = 0;

	if (status == RED_GREEN){
		// Duong 1 = Do (TIMER_COUNTDOWN_1), Duong 2 = Xanh (TIMER_COUNTDOWN_2)
		greenCounter = getTimerCounter(TIMER_COUNTDOWN_2);

		if (greenCounter > PED_GREEN_MIN_TICKS){
			diff = greenCounter - PED_GREEN_MIN_TICKS;

			// Ep thoi gian xanh cua Duong 2 xuong con 5 giay
			setTimer(TIMER_COUNTDOWN_2, PED_GREEN_MIN_TICKS * TICK);

			// Dong bo: giam thoi gian do cua Duong 1 di dung bang phan xanh bi cat
			redCounter = getTimerCounter(TIMER_COUNTDOWN_1);
			if (redCounter > diff){
				setTimer(TIMER_COUNTDOWN_1, (redCounter - diff) * TICK);
			} else {
				setTimer(TIMER_COUNTDOWN_1, TICK);  // dam bao timer khong bi am
			}

			// Bat hien thi LCD xin qua duong - tuyen 2 dang xanh
			flagPedDisplay = 1;
			pedDisplayRoad = 2;
			setTimer(TIMER_LCD_BLINK, PERIOD_LCD_BLINK);
		}
		// Neu greenCounter <= 500 (duoi 5 giay) -> khong lam gi ca

	} else if (status == GREEN_RED){
		// Duong 1 = Xanh (TIMER_COUNTDOWN_1), Duong 2 = Do (TIMER_COUNTDOWN_2)
		greenCounter = getTimerCounter(TIMER_COUNTDOWN_1);

		if (greenCounter > PED_GREEN_MIN_TICKS){
			diff = greenCounter - PED_GREEN_MIN_TICKS;

			// Ep thoi gian xanh cua Duong 1 xuong con 5 giay
			setTimer(TIMER_COUNTDOWN_1, PED_GREEN_MIN_TICKS * TICK);

			// Dong bo: giam thoi gian do cua Duong 2 di dung bang phan xanh bi cat
			redCounter = getTimerCounter(TIMER_COUNTDOWN_2);
			if (redCounter > diff){
				setTimer(TIMER_COUNTDOWN_2, (redCounter - diff) * TICK);
			} else {
				setTimer(TIMER_COUNTDOWN_2, TICK);  // dam bao timer khong bi am
			}

			// Bat hien thi LCD xin qua duong - tuyen 1 dang xanh
			flagPedDisplay = 1;
			pedDisplayRoad = 1;
			setTimer(TIMER_LCD_BLINK, PERIOD_LCD_BLINK);
		}
		// Neu greenCounter <= 500 (duoi 5 giay) -> khong lam gi ca
	}
}
