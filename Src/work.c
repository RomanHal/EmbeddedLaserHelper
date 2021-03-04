#include "main.h"
#include "send.h"
#include <stdint.h>
#include "work.h"
#include "stepper.h"
#include "wait.h"
#include "cmsis_os2.h"
#include "status.h"

void move_until_barrier_touched();
void send_shoot();
void receive_shoot_ok_response(uint32_t *amount);
void  wait(uint32_t time_ms);
void barrier_up();
void move_until_path_clear();
void barrier_down();
void move_to_end();

extern volatile uint8_t shootResponseReceived;
extern volatile uint32_t send_flag;
extern volatile DeviceStatus status;

typedef enum work_state
{
    Move,
    Shoot,
    Wait,
    ClearPath
}work_state;



void work(uint32_t *amount,uint32_t time_ms)
{
    static work_state state=Move;

    switch(state)
    {
        case Move:
            move_until_barrier_touched();
            state=Shoot;
            break;
        case Shoot:
            send_shoot();
            receive_shoot_ok_response(amount);
            state=Wait;
            break;
        case Wait:
            wait(time_ms);
            state=ClearPath;
            break;
        case ClearPath:
            barrier_up();
            move_until_path_clear();
            barrier_down();
            state=Move;
            if(*amount<=0)status=StatusIDLE;
            break;
    }
}

void move_until_barrier_touched()
{
    while(HAL_GPIO_ReadPin(BarrierTouch_GPIO_Port,BarrierTouch_Pin)==GPIO_PIN_SET)
    {
        makeStep(StepperPath,0);
    }
}
void send_shoot()
{
    send_flag |=ReShootBit;
}
void receive_shoot_ok_response(uint32_t *amount)
{
    while(!shootResponseReceived) osDelay(50);
    (*amount)--;
    shootResponseReceived=0;
}

void barrier_up()
{
    while(HAL_GPIO_ReadPin(BarrierUp_GPIO_Port,BarrierUp_Pin)==GPIO_PIN_SET)
    {
        makeStep(StepperBarrier,0);
    }
}
void barrier_down()
{
    while(HAL_GPIO_ReadPin(BarrierDown_GPIO_Port,BarrierDown_Pin)==GPIO_PIN_SET)
    {
        makeStep(StepperBarrier,1);
    }
}
void move_until_path_clear()
{
    //TODO change to use Diode Sensor
    for(int i=0;i<50;i++)
    {
        makeStep(StepperPath,0);
    }
}