/*
 * button.c
 *
 *  Created on: Oct 15, 2025
 *      Author: ngoqu
 */

#include "button.h"

// =============================
// Cấu trúc lưu trạng thái cho từng nút
// =============================
static GPIO_TypeDef* buttonPorts[MAX_BUTTONS] = {GPIOC, GPIOC, GPIOC};
static uint16_t buttonPins[MAX_BUTTONS]       = {BUTTON1_Pin, BUTTON2_Pin, BUTTON3_Pin};

// Bộ nhớ trạng thái cho debounce
static int KeyReg0[MAX_BUTTONS];
static int KeyReg1[MAX_BUTTONS];
static int KeyReg2[MAX_BUTTONS];
static int KeyReg3[MAX_BUTTONS];
static int TimerForKeyPress[MAX_BUTTONS];
static int button_flag[MAX_BUTTONS];
static int button_longPress_flag[MAX_BUTTONS];
static int button_release_flag[MAX_BUTTONS];

//xu ly double click
static int button_doubleClick_flag[MAX_BUTTONS];
static int button_click_count[MAX_BUTTONS];
static int doubleClickTimer[MAX_BUTTONS];


void button_init(void) {
    for (int i = 0; i < MAX_BUTTONS; i++) {
        KeyReg0[i] = KeyReg1[i] = KeyReg2[i] = NORMAL_STATE;
        KeyReg3[i] = NORMAL_STATE;
        TimerForKeyPress[i] = 0;
        button_flag[i] = 0;
        button_longPress_flag[i] = 0;
        button_release_flag[i] = 0;
        button_doubleClick_flag[i] = 0;
        button_click_count[i] = 0;
        doubleClickTimer[i] = 0;
    }
}

// =============================
// Hàm gọi định kỳ mỗi TIMER_CYCLE (ví dụ 10 ms)
// =============================
void getKeyInput(void) {
    for (int i = 0; i < MAX_BUTTONS; i++) {
        KeyReg0[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg2[i];
        KeyReg2[i] = HAL_GPIO_ReadPin(buttonPorts[i], buttonPins[i]);

        if ((KeyReg0[i] == KeyReg1[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg3[i] != KeyReg2[i]) {
            	//nếu nút mới được thả
            	if (KeyReg3[i] == PRESSED_STATE && KeyReg2[i] == NORMAL_STATE){
            		button_release_flag[i] = 1;


            	//xử lý double click
            		button_click_count[i]++;
            		if (button_click_count[i] == 1) {
            		    doubleClickTimer[i] = DOUBLE_CLICK_INTERVAL;
            		} else if (button_click_count[i] == 2) {
            		    button_doubleClick_flag[i] = 1;
            		    button_click_count[i] = 0;
            	        doubleClickTimer[i] = 0;
            		}
            	}


                //xử lý nhấn đơn nhưng không set flag vì chưa biết có nhấn đúp hay không
                KeyReg3[i] = KeyReg2[i];
                if (KeyReg2[i] == PRESSED_STATE) {
                    TimerForKeyPress[i] = DURATION_FOR_AUTO_INCREASING;
                }
            } else {
                // Nếu nút đang được giữ
                if (KeyReg2[i] == PRESSED_STATE ) {
                    if (TimerForKeyPress[i] > 0) {
                        TimerForKeyPress[i]--;
                        if (TimerForKeyPress[i] <= 0) {
                            button_longPress_flag[i] = 1; // báo nhấn giữ lâu
                            TimerForKeyPress[i] = DURATION_FOR_AUTO_INCREASING / 2;
                        }
                    }
                }
            }

            // Đếm ngược double click timer
            if (doubleClickTimer[i] > 0) {
                doubleClickTimer[i]--;
                if (doubleClickTimer[i] == 0) {
                    // Nếu hết thời gian mà chưa có nhấn thứ 2 -> chỉ là single click
                	if (button_click_count[i] == 1) {
                	    button_flag[i] = 1;
                	}
                    button_click_count[i] = 0;
                }
            }
        }
    }
}

// =============================
// Kiểm tra nút được nhấn 1 lần (rising edge)
// =============================
int isButtonPressed(int index) {
    if (index < 0 || index >= MAX_BUTTONS) return 0;
    if (button_flag[index] == 1) {
        button_flag[index] = 0;
        return 1;
    }
    return 0;
}

// =============================
// Kiểm tra nút được nhấn giữ lâu (1 s)
// =============================
int isButtonLongPressed(int index) {
    if (index < 0 || index >= MAX_BUTTONS) return 0;
    if (button_longPress_flag[index] == 1) {
        button_longPress_flag[index] = 0;
        return 1;
    }
    return 0;
}

// =============================
// Kiểm tra nút được thả
// =============================
int isButtonReleased(int index){
    if (index < 0 || index >= MAX_BUTTONS) return 0;
    if (button_release_flag[index] == 1) {
        button_release_flag[index] = 0;
        return 1;
    }
    return 0;
}


// =============================
// Kiểm tra nhấn đúp (double click)
// =============================
int isButtonDoubleClicked(int index) {
    if (index < 0 || index >= MAX_BUTTONS) return 0;
    if (button_doubleClick_flag[index] == 1) {
        button_doubleClick_flag[index] = 0;
        return 1;
    }
    return 0;
}
