/*
 * traffic_light.c
 *
 *  Created on: Oct 28, 2025
 *      Author: ngoqu
 */

#include "traffic_light.h"

traffic_state trafState = START;

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

void traffic_light_autorun(int redtime, int yellowtime, int greentime){
	switch (trafState){
		case START:
			trafState = RED_GREEN;
			setTimer(TIMER_COUNTDOWN_1, redtime);
			setTimer(TIMER_COUNTDOWN_2, greentime);
			setTimer(TIMER_DISPLAY_7SEG, 10);
			setTimer(TIMER_UPDATE_BUFFER, 10);
			break;
		case RED_GREEN:
			YellowToRed1();
			RedToGreen2();
			if (isTimerExpired(TIMER_UPDATE_BUFFER)){
				updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
				setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegLed();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(TIMER_COUNTDOWN_2)){
				trafState = RED_YELLOW;
				setTimer(TIMER_COUNTDOWN_2, yellowtime);
			}
			break;
		case RED_YELLOW:
			GreenToYellow2();
			if (isTimerExpired(TIMER_UPDATE_BUFFER)){
				updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
				setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegLed();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(TIMER_COUNTDOWN_1)){
				trafState = GREEN_RED;
				setTimer(TIMER_COUNTDOWN_1, greentime);
				setTimer(TIMER_COUNTDOWN_2, redtime);
			}
			break;
		case GREEN_RED:
			RedToGreen1();
			YellowToRed2();
			if (isTimerExpired(TIMER_UPDATE_BUFFER)){
				updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
				setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegLed();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(TIMER_COUNTDOWN_1)){
				trafState = YELLOW_RED;
				setTimer(TIMER_COUNTDOWN_1, yellowtime);
			}
			break;
		case YELLOW_RED:
			GreenToYellow1();
			if (isTimerExpired(TIMER_UPDATE_BUFFER)){
				updateTimerBuffer(getTimerCounter(TIMER_COUNTDOWN_1), getTimerCounter(TIMER_COUNTDOWN_2));
				setTimer(TIMER_UPDATE_BUFFER, PERIOD_UPDATE_TIME_BUFFER);
			}
			if (isTimerExpired(TIMER_DISPLAY_7SEG)){
				display7SegLed();
				setTimer(TIMER_DISPLAY_7SEG, PERIOD_SCAN_7SEG_LED);
			}
			if (isTimerExpired(TIMER_COUNTDOWN_1)){
				trafState = RED_GREEN;
				setTimer(TIMER_COUNTDOWN_1, redtime);
				setTimer(TIMER_COUNTDOWN_2, greentime);
			}
			break;
		default:
			break;
		}
}

void traffic_light_hand_control_run(){
	switch (trafState){
		case START:
			if (isTimerExpired(TIMER_BLINK_LED)){
				ALL_RED_toggle();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}
			if (isButtonPressed(1)){
				trafState = RED_GREEN;
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}
			break;
		case RED_GREEN:
			YellowToRed1();
			RedToGreen2();
			if (isButtonPressed(1)){
				trafState = RED_GREENBLINK;
			}
			break;
		case RED_GREENBLINK:
			if (isTimerExpired(TIMER_BLINK_LED)){
				BLINK_GREEN_ROAD2();
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}
			if (isButtonPressed(1)){
				trafState = RED_YELLOW;
			}
			break;
		case RED_YELLOW:
			GreenToYellow2();
			if (isButtonPressed(1)){
				trafState = GREEN_RED;
			}
			break;
		case GREEN_RED:
			YellowToRed2();
			RedToGreen1();
			if (isButtonPressed(1)){
				trafState = GREENBLINK_RED;
			}
			break;
		case GREENBLINK_RED:
			if (isTimerExpired(TIMER_BLINK_LED)){
				HAL_GPIO_TogglePin(GPIOA, LED_G_A_Pin|LED_G_C_Pin);
				setTimer(TIMER_BLINK_LED, COLOR_LED_BLINK_CYCLE);
			}
			if (isButtonPressed(1)){
				trafState = YELLOW_RED;
			}
			break;
		case YELLOW_RED:
			GreenToYellow1();
			if (isButtonPressed(1)){
				trafState = RED_GREEN;
			}
			break;
		default:
			break;
		}
	}
