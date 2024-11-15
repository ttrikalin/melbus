#ifndef DEVICES_H
#define DEVICES_H

// The MELBUS peripheral devices can be in 2 modes:
// 1. Slave mode: The device is a slave and can only receive messages from the HU.
//    When it receives a message, it will respond with its slave_response ID to register its presence.
//  The default mode is slave mode.
// 2. Master mode: The device is the master and can send messages to the HU.
//    It will use its master_name ID when addressing the HU.

/*  Known Melbus IDs
Unit		        slave_name	  slave_resp	master_name	    ID When addressed by HU
Unit		        ID Main Init	ID Response	ID Master Mode	ID When addressed by HU
MD (Internal)		  70			      76			      77			      70 or 71
CD (Internal)		  80			      86			      87			      80 or 71
TV (External)		  A9			      AE			      AF			      A8 or A9
DAB (External)		B8			      BE			      BF			      B8 or B9
SAT (External)		C0			      C6			      C7			      C0 or C1
MD-C (External)		D8			      DE			      DF			      D8 or D9
CD-C (External)		E8			      EE			      EF			      E8 or E9
*/ 



//{TRACK + CART}      0     1     2     3     4     5     6     7     8 ||| 9     10    11    12    13    14
#define DEV_DEFAULT {0x00, 0x02, 0x00, 0x01, 0x80, 0x01, 0xff, 0x60, 0x60, 0x00, 0x0f, 0xff, 0x4a, 0xfc, 0xff }
/*
0 ?
1 02 stop, 08 play
2 08 ? 0f rand
3 [01..0a] CDx
4 track related?
5 track related?
6 ?
7 time min
8 time sec
*/

struct device_t {
    const unsigned char name[4];
    const unsigned char slave_name;
    const unsigned char slave_response;
    const unsigned char master_name;
    bool enabled;
    bool initialized;
    unsigned char info[15];
};



#ifdef MDC
#define ENABLE_MDC true
#else
#define ENABLE_MDC false
#endif

#ifdef CDC
#define ENABLE_CDC true
#else
#define ENABLE_CDC false
#endif

#define g_devicesSize 2
volatile struct device_t g_devices[g_devicesSize] = {
      {"MDC", 0xd8, 0xde, 0xdf, ENABLE_MDC, false, DEV_DEFAULT} 
    , {"CDC", 0xe8, 0xee, 0xef, ENABLE_CDC, false, DEV_DEFAULT} 
};

#endif
