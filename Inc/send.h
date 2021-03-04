#include "status.h"
#define ReHelloBit 1U
#define ReGetStatusBit 1U<<1
#define ReGetSettingsBit 1U<<2
#define ReSetSettingsBit 1U<<3
#define ReStartBit 1U<<4
#define ReStopBit 1U<<5
#define ReShootBit 1U<<6
#define ErrorComBit 1U<<7

void send(uint32_t amount,uint32_t time,DeviceStatus status);
