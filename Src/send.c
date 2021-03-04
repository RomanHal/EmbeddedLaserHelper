#include "communication.h"
#include "usbd_cdc_if.h"
#include <stdint.h>
#include "status.h"
#include "wait.h"
#include "send.h"

extern volatile uint32_t send_flag;

void send(uint32_t amount,uint32_t time,DeviceStatus status)
{
    uint8_t ToSend[5];
 if(send_flag==0)
 {
     wait(100);
 }
 else if ((send_flag&1U) > 0)
 {
    //  HelloTODO

    send_flag &= ~(1U);
    ToSend[0]=CodeReHello;
    CDC_Transmit_FS(ToSend,1);

 }
  else if ((send_flag&1U<<1) > 0)
 {
    //  sendStatus
     send_flag &= ~(1U<<1);
     ToSend[0]=CodeReGetStatus;
     ToSend[1]=status;
    CDC_Transmit_FS(ToSend,2);

     /* code */
 }
  else if ((send_flag&1U<<2) > 0)
 { 
    //  sendSettings
      send_flag &= ~(1U<<2);
      ToSend[0]=CodeReGetSettings;
      ToSend[1]=amount;
      ToSend[2]=amount>>8;
      time/=100;
      ToSend[3]=time;
      ToSend[4]=time>>8;
    CDC_Transmit_FS(ToSend,5);
     /* code */
 }
  else if ((send_flag&1U<<3) > 0)
 {
     send_flag &= ~(1U<<3);
     ToSend[0]=CodeReSetSettings;
     CDC_Transmit_FS(ToSend,1);
 }
      else if ((send_flag&1U<<4) > 0)
 {
     send_flag &= ~(1U<<4);
     ToSend[0]=CodeReStart;
     CDC_Transmit_FS(ToSend,1);
 }  
 else if ((send_flag&1U<<5) > 0)
 {
     send_flag &= ~(1U<<5);
     ToSend[0]=CodeReStop;
     CDC_Transmit_FS(ToSend,1);
 }
   else if ((send_flag&1U<<6) > 0)
 {
     send_flag &= ~(1U<<6);
     ToSend[0]=CodeShoot;
     CDC_Transmit_FS(ToSend,1);
 }
   else if ((send_flag&1U<<7) > 0)
 {
    //  TODO :ERRORS
     send_flag &= ~(1U<<7);
 }
}