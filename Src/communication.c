#include <stdint.h>
#include "communication.h"
#include "communicationCallBacks.h"
#include "usbd_cdc_if.h"
#include "status.h"
#include "send.h"
#include "cmsis_os2.h"


extern uint8_t UserRxBufferFS[];
extern volatile DeviceStatus status;
extern volatile uint32_t amount;
extern volatile uint32_t time_to_wait;
extern volatile uint32_t send_flag;
extern volatile uint8_t shootResponseReceived;


void hello_handler();
void start_handler();
void stop_handler();
void get_status_handler();
void get_settings_handler();
void set_settings_handler(int *i);
void re_shoot_handler();


void dataGetted(uint32_t amount)
{
    decode(amount);
}
void decode(int amount)
{
    
    for(int i=0;i<amount;i++)
    {
        uint8_t something=UserRxBufferFS[i];
        switch (something)
        {
        case CodeHello:
            hello_handler();
            break;
        case CodeReShoot:
            re_shoot_handler();
            break;
        case CodeStop:
            stop_handler();
            break;
        case CodeStart:
            start_handler();
            break;
        case CodeGetStatus:
            get_status_handler();
            break;
        case CodeGetSettings:
            get_settings_handler();
            break;
        case CodeSetSettings:
            set_settings_handler(&i);
            break;
        // case CodeReHello:
        //     //
        //     break;
        // case CodeReGetSettings:
            
        //     break;
        // case CodeReSetSettings:

        //     break;
        // case CodeReStart:

        //     break;
        // case CodeReStop:
        //     /* code */
        //     break;
        // case CodeReGetStatus:

        //     break;
        // case CodeShoot:
        //     /* code */
        //     break;
        default:
            break;
        }
    }
}
void hello_handler()
{
    send_flag|=ReHelloBit;
}
void start_handler()
{
 status=StatusWORKING;
    send_flag|=ReStartBit;
}
void stop_handler()
{
 status=StatusPAUSE;
 send_flag|=ReStopBit;
//  FlagSetToReStarted

}
void get_status_handler()
{
    send_flag|=ReGetStatusBit;
}
void get_settings_handler()
{

    send_flag|=ReGetSettingsBit;
    // send settings
}
void set_settings_handler(int *i)
{
    amount=UserRxBufferFS[(*i)+1]+(UserRxBufferFS[(*i)+2]<<8);
    time_to_wait=UserRxBufferFS[(*i)+3]+(UserRxBufferFS[(*i)+4]<<8);
    time_to_wait*=100;
    send_flag|=ReSetSettingsBit;
    *i+=4;
//send setted
}
void re_shoot_handler()
{
    shootResponseReceived=1;
}