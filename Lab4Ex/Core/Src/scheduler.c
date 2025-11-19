/*
 * app_scheduler.c
 */

#include "scheduler.h"
#include "stm32f1xx_hal.h"   // hoặc dòng chip phù hợp

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

// Task array
static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t newTaskID = 0;

// =================== Forward declarations ===================
static uint32_t Get_New_Task_ID(void);
static void Scheduler_TimerInit(void);

// =================== PUBLIC FUNCTIONS ===================
void SCH_Init(void) {
    Scheduler_TimerInit();
}

void SCH_Update(void){
    if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
        if (SCH_tasks_G[0].Delay > 0) {
            SCH_tasks_G[0].Delay--;
        }
        if (SCH_tasks_G[0].Delay == 0) {
            SCH_tasks_G[0].RunMe = 1;
        }
    }
}

uint32_t SCH_Add_Task(void (* pFunction)(), uint32_t DELAY, uint32_t PERIOD){
    uint8_t newTaskIndex = 0;
    uint32_t sumDelay = 0;
    uint32_t newDelay = 0;

    for(newTaskIndex = 0; newTaskIndex < SCH_MAX_TASKS; newTaskIndex++){
        sumDelay += SCH_tasks_G[newTaskIndex].Delay;

        if(sumDelay > DELAY){
            newDelay = DELAY - (sumDelay - SCH_tasks_G[newTaskIndex].Delay);
            SCH_tasks_G[newTaskIndex].Delay = sumDelay - DELAY;

            for(int i = SCH_MAX_TASKS - 1; i > newTaskIndex; i--){
                SCH_tasks_G[i] = SCH_tasks_G[i - 1];
            }

            SCH_tasks_G[newTaskIndex].pTask = pFunction;
            SCH_tasks_G[newTaskIndex].Delay = newDelay;
            SCH_tasks_G[newTaskIndex].Period = PERIOD;
            SCH_tasks_G[newTaskIndex].RunMe = (newDelay == 0) ? 1 : 0;
            SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();

            return SCH_tasks_G[newTaskIndex].TaskID;
        }
        else {
            if(SCH_tasks_G[newTaskIndex].pTask == 0x0000){
                SCH_tasks_G[newTaskIndex].pTask = pFunction;
                SCH_tasks_G[newTaskIndex].Delay = DELAY - sumDelay;
                SCH_tasks_G[newTaskIndex].Period = PERIOD;
                SCH_tasks_G[newTaskIndex].RunMe = (SCH_tasks_G[newTaskIndex].Delay == 0);
                SCH_tasks_G[newTaskIndex].TaskID = Get_New_Task_ID();
                return SCH_tasks_G[newTaskIndex].TaskID;
            }
        }
    }

    return 0;
}

uint8_t SCH_Delete_Task(uint32_t taskID){
    uint8_t taskIndex, j;
    if(taskID != NO_TASK_ID){
        for(taskIndex = 0; taskIndex < SCH_MAX_TASKS; taskIndex++){
            if(SCH_tasks_G[taskIndex].TaskID == taskID){

                if(taskIndex < SCH_MAX_TASKS - 1 && SCH_tasks_G[taskIndex+1].pTask != 0){
                    SCH_tasks_G[taskIndex+1].Delay += SCH_tasks_G[taskIndex].Delay;
                }

                for(j = taskIndex; j < SCH_MAX_TASKS - 1; j++){
                    SCH_tasks_G[j] = SCH_tasks_G[j+1];
                }

                SCH_tasks_G[j].pTask = 0;
                SCH_tasks_G[j].Delay = 0;
                SCH_tasks_G[j].Period = 0;
                SCH_tasks_G[j].RunMe = 0;
                SCH_tasks_G[j].TaskID = 0;

                return 1;
            }
        }
    }
    return 0;
}

void SCH_Dispatch_Tasks(void){
    if(SCH_tasks_G[0].RunMe > 0){
        (*SCH_tasks_G[0].pTask)();
        SCH_tasks_G[0].RunMe = 0;

        sTask temp = SCH_tasks_G[0];
        SCH_Delete_Task(temp.TaskID);

        if(temp.Period != 0){
            SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
        }
    }
}

// =================== TIMER INIT FOR STM32 ===================
static void Scheduler_TimerInit(void){
    // Bạn phải cấu hình TIM2 trong CubeMX thành 10ms interrupt

    // Không tự cấu hình TIM ở đây để tránh lệch HAL.
    // Chỉ reset counter:
    // __HAL_TIM_SET_COUNTER(&htim2, 0);
}

// =================== CALLBACK FOR TIMER INTERRUPT ===================
void SCH_TimerCallback(void){
    SCH_Update();
}

// =================== TASK ID ===================
static uint32_t Get_New_Task_ID(void){
    newTaskID++;
    if(newTaskID == NO_TASK_ID){
        newTaskID++;
    }
    return newTaskID;
}

#ifdef __cplusplus
}
#endif
