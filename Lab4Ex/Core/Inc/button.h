/*
 * button.h
 *
 *  Created on: Oct 15, 2025
 *      Author: ngoqu
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include "main.h"

#define MAX_BUTTONS     				3      // Số lượng nút tối đa
#define NORMAL_STATE    				GPIO_PIN_SET
#define PRESSED_STATE   				GPIO_PIN_RESET
#define DURATION_FOR_AUTO_INCREASING    100	   // tuong duong 1s
#define DOUBLE_CLICK_INTERVAL 			40	   // tuong duong 400ms


void button_init(void);
void getKeyInput(void);             // Gọi định kỳ trong ngắt timer (mỗi 10 ms)
int  isButtonPressed(int);      	// Phát hiện nhấn 1 lần
int  isButtonLongPressed(int);    	// Phát hiện nhấn giữ 1s
int  isButtonReleased(int);      	// Phát hiện nhấn thả (nhận tín hiệu khi thả nút)
int  isButtonDoubleClicked(int);  	// Phát hiện nhấn đúp


#endif /* INC_BUTTON_H_ */
