#ifndef __SERIAL_H__
#define __SERIAL_H__

// Shared serial/parameter protocol headers.
// These keep the Input Controller speaking the same on-wire language
// as the mainboard and DCO for 'p'/'w' parameter frames and other commands.
#include "serial_param_protocol.h"
#include "serial_protocol.h"
#include "serial_parser.h"
#include "params_def.h"   // ParamId enum for modern param protocol

//#define ENABLE_SERIAL
#define ENABLE_SERIAL1
#define ENABLE_SERIAL2

// Serial2 receive task (from mainboard/DCO).
void serial_read_n();

float freq;

byte finishByte = 1;

// Flags controlling when to send which values via Serial2.
bool sendDetune2Flag = false;
bool serial_send_portamentoFlag = false;
bool serial_send_oscSyncModeFlag = false;
bool serial_send_OSC1IntervalFlag = false;
bool serial_send_OSC2IntervalFlag = false;
bool serial_send_LFO1SpeedFlag = false;
bool serial_send_LFO1toDCOFlag = false;
bool serial_send_LFO1toDCOWaveChangeFlag = false;
bool serialSendADSR3ControlValuesFlag = false;
bool serialSendADSR3toDCOFlag = false;
bool serialSendADSR3ToOscSelectFlag = false;

// Parameter send helpers ('p'/'w' frames, modern ParamId-based protocol).
void serial_send_param_change_byte(ParamId param, int8_t paramValue, bool sendToAll = true); 
void serial_send_param_change(ParamId param, int16_t paramValue, bool sendToAll = true); 

#endif

/*
SIGNAL LIST:

1 LOAD (PRESET SCROLL)
2 LOAD/SAVE EXIT
3 SAVE
4 SAVE - SET NAME
5 SAVE - COMPLETE
6 SAVE - SET NAME - CHAR SELECTION
7
8

*/