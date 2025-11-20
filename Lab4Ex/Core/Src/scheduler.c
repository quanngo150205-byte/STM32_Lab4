#include "scheduler.h"

// ===== STRUCT TASK =====
typedef struct {
    void (*pTask)(void);
    uint32_t Delay;
    uint32_t Period;
    uint8_t RunMe;
    uint32_t TaskID;
} sTask;

// ===== GLOBAL =====
static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t newTaskID = 0;

// ===== PRIVATE =====
static uint32_t Get_New_Task_ID(void);

// =======================================================
//                 SCHEDULER INIT
// =======================================================
void SCH_Init(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].Delay = 0;
        SCH_tasks_G[i].Period = 0;
        SCH_tasks_G[i].RunMe = 0;
        SCH_tasks_G[i].TaskID = 0;
    }
}

// =======================================================
//           HÀM NÀY SẼ ĐƯỢC GỌI TRONG TIMER ISR
// =======================================================
void SCH_TimerCallback(void) {
    if (SCH_tasks_G[0].pTask && SCH_tasks_G[0].RunMe == 0) {
        if (SCH_tasks_G[0].Delay > 0) {
            SCH_tasks_G[0].Delay--;
        }
        if (SCH_tasks_G[0].Delay == 0) {
            SCH_tasks_G[0].RunMe = 1;
        }
    }
}

// =======================================================
//                   ADD TASK
// =======================================================
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint8_t index = 0;
    uint32_t sumDelay = 0;

    for (index = 0; index < SCH_MAX_TASKS; index++) {
        sumDelay += SCH_tasks_G[index].Delay;

        if (sumDelay > DELAY) {
            uint32_t newDelay = DELAY - (sumDelay - SCH_tasks_G[index].Delay);
            SCH_tasks_G[index].Delay = sumDelay - DELAY;

            // Shift từ cuối lên
            for (int i = SCH_MAX_TASKS - 1; i > index; i--) {
                SCH_tasks_G[i] = SCH_tasks_G[i - 1];
            }

            SCH_tasks_G[index].pTask = pFunction;
            SCH_tasks_G[index].Delay = newDelay;
            SCH_tasks_G[index].Period = PERIOD;
            SCH_tasks_G[index].RunMe = (newDelay == 0);
            SCH_tasks_G[index].TaskID = Get_New_Task_ID();
            return SCH_tasks_G[index].TaskID;
        }

        // Vị trí trống
        if (SCH_tasks_G[index].pTask == 0) {
            SCH_tasks_G[index].pTask = pFunction;
            SCH_tasks_G[index].Delay = DELAY - sumDelay;
            SCH_tasks_G[index].Period = PERIOD;
            SCH_tasks_G[index].RunMe = (SCH_tasks_G[index].Delay == 0);
            SCH_tasks_G[index].TaskID = Get_New_Task_ID();
            return SCH_tasks_G[index].TaskID;
        }
    }

    return 0; // Không đủ slot
}

// =======================================================
//                  DELETE TASK
// =======================================================
uint8_t SCH_Delete_Task(uint32_t taskID) {
    uint8_t i, j;

    for (i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].TaskID == taskID) {

            if (i < SCH_MAX_TASKS - 1 && SCH_tasks_G[i + 1].pTask != 0) {
                SCH_tasks_G[i + 1].Delay += SCH_tasks_G[i].Delay;
            }

            for (j = i; j < SCH_MAX_TASKS - 1; j++) {
                SCH_tasks_G[j] = SCH_tasks_G[j + 1];
            }

            // Clear cuối
            SCH_tasks_G[j].pTask = 0;
            SCH_tasks_G[j].Delay = 0;
            SCH_tasks_G[j].Period = 0;
            SCH_tasks_G[j].RunMe = 0;
            SCH_tasks_G[j].TaskID = 0;

            return 1;
        }
    }
    return 0; // không thấy
}

// =======================================================
//                 DISPATCH TASK
// =======================================================
void SCH_Dispatch_Tasks(void) {
    if (SCH_tasks_G[0].RunMe > 0) {
        (*SCH_tasks_G[0].pTask)();
        SCH_tasks_G[0].RunMe = 0;

        sTask temp = SCH_tasks_G[0];
        SCH_Delete_Task(temp.TaskID);

        if (temp.Period != 0) {
            SCH_Add_Task(temp.pTask, temp.Period, temp.Period);
        }
    }
}

// =======================================================
static uint32_t Get_New_Task_ID(void) {
    newTaskID++;
    if (newTaskID == 0) newTaskID++;
    return newTaskID;
}
