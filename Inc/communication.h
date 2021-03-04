// 0x0f Hello (Start from PC)
// 0xf0 Re:hello
#define CodeHello 0x0f
#define CodeReHello 0xf0
// 0x01 getStatus (IDLE/READY/WORKING/PAUSE)
// 0x11 (1B)Status 
#define CodeGetStatus 0x01
#define CodeReGetStatus 011
// 0x02 getSettings
// 0x12 (2B amount)(2B wait dseconds) Settings
// 0x22 (2B amount)(2B wait dseconds) SetSettings
// 0x32 settingsSetted
#define CodeGetSettings 0x02
#define CodeReGetSettings 0x12
#define CodeSetSettings 0x22
#define CodeReSetSettings 0x32
// 0x03 start
// 0x13 started
#define CodeStart 0x03
#define CodeReStart 0x13
// 0x04 stop
// 0x14 stopped
#define CodeStop 0x04
#define CodeReStop 0x14
// 0x07 shoot
// 0x17 shootOkResponse
#define CodeShoot 0x07
#define CodeReShoot 0x17

// 0x40-0x4f ERRORs 

void decode(int amount);