/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#include "traffic_light.h"

void clearAllLed(){
	HAL_GPIO_WritePin(LED_R_A_GPIO_Port,   LED_R_A_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_A_GPIO_Port,   LED_Y_A_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_A_GPIO_Port,   LED_G_A_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_B_GPIO_Port,   LED_R_B_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_B_GPIO_Port,   LED_Y_B_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_B_GPIO_Port,   LED_G_B_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_C_GPIO_Port,   LED_R_C_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_C_GPIO_Port,   LED_Y_C_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_C_GPIO_Port,   LED_G_C_Pin,     GPIO_PIN_SET);

	HAL_GPIO_WritePin(LED_R_D_GPIO_Port,   LED_R_D_Pin,     GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_Y_D_GPIO_Port,   LED_Y_D_Pin,  	GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED_G_D_GPIO_Port,   LED_G_D_Pin,     GPIO_PIN_SET);
}

/* Ham chuyen den duong 1*/
void YellowToRed1(){
	HAL_GPIO_WritePin(GPIOA, LED_R_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R_C_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_C_Pin, GPIO_PIN_SET);
}
void RedToGreen1(){
	HAL_GPIO_WritePin(GPIOA, LED_R_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_R_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_C_Pin, GPIO_PIN_RESET);
}
void GreenToYellow1(){
	HAL_GPIO_WritePin(GPIOA, LED_G_A_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_A_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_G_C_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_C_Pin, GPIO_PIN_RESET);
}

/* Ham chuyen den duong 2*/
void YellowToRed2(){
	HAL_GPIO_WritePin(GPIOA, LED_R_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_R_D_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_D_Pin, GPIO_PIN_SET);
}
void RedToGreen2(){
	HAL_GPIO_WritePin(GPIOA, LED_R_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_R_D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_G_D_Pin, GPIO_PIN_RESET);
}
void GreenToYellow2(){
	HAL_GPIO_WritePin(GPIOA, LED_G_B_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_B_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOA, LED_G_D_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOA, LED_Y_D_Pin, GPIO_PIN_RESET);
}

void traffic_light_run(int redtime, int yellowtime, int greentime){
	switch (trafState){
		case START:
			HAL_GPIO_WritePin(GPIOA, LED_Y_A_Pin|LED_Y_B_Pin|LED_Y_C_Pin|LED_Y_D_Pin, GPIO_PIN_SET);
			trafState = RED_GREEN;
			setTimer(1, redtime);
			setTimer(2, greentime);
			setTimer(4, 10);
			setTimer(5, 10);
			break;
		case RED_GREEN:
			YellowToRed1();
			RedToGreen2();
			if (isTimerExpired(5)){
				updateTimerBuffer(getTimerCounter(1), getTimerCounter(2));
				setTimer(5, PREIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(4)){
				display7SegLed();
				setTimer(4, PREIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(2)){
				trafState = RED_YELLOW;
				setTimer(2, yellowtime);
			}
			break;
		case RED_YELLOW:
			GreenToYellow2();
			if (isTimerExpired(5)){
				updateTimerBuffer(getTimerCounter(1), getTimerCounter(2));
				setTimer(5, PREIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(4)){
				display7SegLed();
				setTimer(4, PREIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(1)){
				trafState = GREEN_RED;
				setTimer(1, greentime);
				setTimer(2, redtime);
			}
			break;
		case GREEN_RED:
			RedToGreen1();
			YellowToRed2();
			if (isTimerExpired(5)){
				updateTimerBuffer(getTimerCounter(1), getTimerCounter(2));
				setTimer(5, PREIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(4)){
				display7SegLed();
				setTimer(4, PREIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(1)){
				trafState = YELLOW_RED;
				setTimer(1, yellowtime);
			}
			break;
		case YELLOW_RED:
			GreenToYellow1();
			if (isTimerExpired(5)){
				updateTimerBuffer(getTimerCounter(1), getTimerCounter(2));
				setTimer(5, PREIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(4)){
				display7SegLed();
				setTimer(4, PREIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(1)){
				trafState = RED_GREEN;
				setTimer(1, redtime);
				setTimer(2, greentime);
			}
			break;
		default:
			break;
		}
}
