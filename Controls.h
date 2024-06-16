#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include <RoxMux_fela.h>
//#include <light_CD74HC4067.h>
#include <MD_REncoder_fela.h>
#include <CD74HC4067.h>
//#include "analogmuxdemux.h"

// #define PIN_SAW1 42
// #define PIN_SAW2 42
// #define PIN_TRI 42
// #define PIN_SIN 42

#define muxAnalog_PIN_CH0 21
#define muxAnalog_PIN_CH1 20
#define muxAnalog_PIN_CH2 19
#define muxAnalog_PIN_CH3 18

#define digitalMUX1_PIN_S0 21
#define digitalMUX1_PIN_S1 20
#define digitalMUX1_PIN_S2 19
#define digitalMUX1_PIN_S3 18

#define muxAnalog_PIN_SIG 27

#define digitalMUX1_PIN_SIG0 2
#define digitalMUX2_PIN_SIG0 16
#define digitalMUX3_PIN_SIG0 17

// Rox74HC4067 <3> muxDigital;
// Rox74HC4067 <1> muxAnalog;

CD74HC4067 muxDigital(21, 20, 19, 18);
CD74HC4067 muxAnalog(21, 20, 19, 18);

uint8_t activeDigitalMuxChannel = 0;
uint8_t activeAnalogMuxChannel = 0;
uint8_t valorMUX1[48];

MD_REncoder enc1 = MD_REncoder(50, 50);
MD_REncoder enc2 = MD_REncoder(50, 50);
MD_REncoder enc3 = MD_REncoder(50, 50);
MD_REncoder enc4 = MD_REncoder(50, 50);
MD_REncoder enc5 = MD_REncoder(50, 50);

MD_REncoder enc6 = MD_REncoder(50, 50);
MD_REncoder enc7 = MD_REncoder(50, 50);
MD_REncoder enc8 = MD_REncoder(50, 50);
MD_REncoder enc9 = MD_REncoder(50, 50);
MD_REncoder enc10 = MD_REncoder(50, 50);
MD_REncoder enc11 = MD_REncoder(50, 50);

//ezButton sine(PIN_BUTTON_SIN);  // create ezButton object that attach to pin 6;
//ezButton saw_2(PIN_BUTTON_SAW2);  // create ezButton object that attach to pin 7;
//ezButton saw(PIN_BUTTON_SAW1);
//ezButton tri(PIN_BUTTON_TRI);

RoxButton button1;
RoxButton button2;
RoxButton button3;
RoxButton button4;
RoxButton button5;
RoxButton button6;
RoxButton button7;
RoxButton button8;
RoxButton button9;
RoxButton button10;
RoxButton button11;
RoxButton button12;
RoxButton button13;
RoxButton button14;
RoxButton button15;
RoxButton button16;

uint8_t fader1ArrayPos = 0;
uint8_t fader2ArrayPos = 1;
uint8_t fader3ArrayPos = 2;
uint8_t fader4ArrayPos = 3;
uint8_t fader5ArrayPos = 4;
uint8_t fader6ArrayPos = 5;
uint8_t fader7ArrayPos = 6;
uint8_t fader8ArrayPos = 7;

uint8_t pot1ArrayPos = 14;
uint8_t pot2ArrayPos = 13;
uint8_t pot3ArrayPos = 15;
uint8_t pot4ArrayPos = 12;
uint8_t pot5ArrayPos = 11;
uint8_t pot6ArrayPos = 10;
uint8_t pot7ArrayPos;
uint8_t pot8ArrayPos;

bool sineStatus = 0;
bool triStatus = 0;
bool sawStatus = 0;
bool saw2Status = 0;
bool sqr1Status = 0;
bool sqr2Status = 0;
bool SUBStatus = 1;
byte waveStatus;

byte botonEnc1 = 0;
byte botonEnc2 = 0;
byte botonEnc3 = 0;
byte botonEnc4 = 0;
byte botonEnc5 = 0;
byte botonEnc6 = 0;
byte botonEnc7 = 0;
byte botonEnc8 = 0;
byte botonEnc9 = 0;
byte botonEnc10 = 0;
byte botonEnc11 = 0;
byte botonEnc12 = 0;
byte botonEnc13 = 0;
byte botonEnc14 = 0;

uint16_t muxAnalogRaw[16];
uint16_t muxAnalogData[16];
uint16_t muxAnalogDataPrev[16];

unsigned long muxAnalogLastReadTime;
byte muxAnalogReadChannel = 0;

int encVal[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int encValFunc[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int encVal2[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int encVal3[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int encVal4[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int encVal5[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int encVal6[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int buttonVal[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int buttonVal2[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
int buttonVal3[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

byte faderRow1Mode = 0;
bool faderRow1ControlManual = false;

byte faderRow2Mode = 0;
bool faderRow2ControlManual = false;

byte VCFPots = 0;
bool VCFPotsControlManual = false;

byte VCAPots = 0;
bool VCAPotsControlManual = false;

byte PWMPots = 0;
bool PWMPotsControlManual = false;

bool faderControlManual = false;
bool potsControlManual = false;
bool allControlsManual = false;

bool ADSR3Enabled = false;

bool presetSelect = false;
bool presetSaveSelectMode = false;
bool presetSaveMode = false;
bool presetSaved = true;

uint8_t presetSelectVal = 0;
byte presetChar = 0;
byte charSelectVal = 0;

byte presetNameVal[17] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
byte loadedName[17];

bool funcKeyOn = false;

#endif
