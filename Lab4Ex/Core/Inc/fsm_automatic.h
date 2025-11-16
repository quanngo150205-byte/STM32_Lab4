/*
 * fsm_automatic.h
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#ifndef INC_FSM_AUTOMATIC_H_
#define INC_FSM_AUTOMATIC_H_
#define GREEN_TIME     3000
#define YELLOW_TIME    2000


#include "global.h"
#include "traffic_light.h"
#include "7seg.h"

//timer(0) blink led PA5
//timer(1) dem thoi gian countdown duong 1
//timer(2) dem thoi gian countdown duong 2
//timer(4) quet led 7 doan
//timer(5) update time_buffer

void fsm_automatic_run();
#endif /* INC_FSM_AUTOMATIC_H_ */
