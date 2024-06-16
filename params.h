#ifndef __PARAMS_H__
#define __PARAMS_H__

byte noteStart[NUM_VOICES];
byte noteEnd[NUM_VOICES];
byte velocity[NUM_VOICES];
byte note[NUM_VOICES];

byte voiceMode = 0;
byte currentVoice = 0;
int16_t unisonDetune = 0;
byte noiseLevel = 0;

// encoder values
int16_t portamentoTimeVal;

int16_t VCFKeytrackVal;

int16_t SQR1LevelVal;
int16_t SQR2LevelVal;
int16_t SubLevelVal;

int8_t OSC1IntervalVal;
int8_t OSC2IntervalVal;
int16_t OSC2DetuneVal;

int16_t VCALevelVal;

int16_t ADSR3toDETUNE1Val;
int16_t ADSR3toPWMVal;

int8_t velocityToVCFVal = 0;
int8_t velocityToVCAVal = 0;
int8_t velocityToPWMVal = 0;

int16_t LFO2toOSC2DETUNEVal;

int16_t LFO1toDCOVal;
int16_t LFO2toDCOVal;
int16_t LFO3toDCOVal;

int16_t LFO1toVCAVal;

int16_t LFO1toPWMVal;
int16_t LFO2toPWMVal;
int16_t LFO3toPWMVal;

int16_t LFO1SpeedVal;
int16_t LFO2SpeedVal;
int16_t LFO3SpeedVal;

int16_t LFO1toVCFVal;
int16_t LFO2toVCFVal;
int16_t LFO3toVCFVal;


int8_t LFO1WaveformVal;
int8_t LFO2WaveformVal;
int8_t LFO3WaveformVal;

int8_t oscSyncModeVal;

int8_t ADSR3ToOscSelect;

int16_t calibrationVal;
//

float velocityToVCF = 0;
float velocityToVCA = 0;
float velocityToPWM = 0;

int16_t aftertouch = 0;
byte portamentoTime = 0;
byte portamentoMode = 0;

float VCAResonanceCompensation = 0;
bool RESONANCEAmpCompensation = true;

bool VCFADSRRestart = true;
bool VCAADSRRestart = true;
byte VCFKeytrack = 0;
byte oscSyncMode = 0;

byte presetName[17] = {32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32};
String presetNameString;
byte currentPreset;

/// LFO

static const uint16_t LFO1_CC = 4095;
static const uint16_t LFO1_CC_HALF = LFO1_CC / 2;
static const uint16_t LF01_CC_THIRD = LFO1_CC / 3;
static const uint16_t LFO2_CC = 4095;
static const uint16_t LFO2_CC_HALF = LFO2_CC / 2;
static const uint16_t LFO3_CC = 4095;
static const uint16_t LFO3_CC_HALF = LFO2_CC / 2;

int16_t      LFO1Level;
byte     LFO1Waveform;
float    LFO1Speed;
uint16_t LFO1toVCF;
uint16_t LFO1toVCA = 0;
uint16_t LFO1toPWM;
float    LFO1toDCO;
uint16_t LFO1toDETUNE1;
uint16_t LFO1toDETUNE2;

int16_t LFO2Level;
byte     LFO2Waveform;
float    LFO2Speed;
uint16_t LFO2toVCF;
uint16_t LFO2toVCA;
uint16_t LFO2toPWM;
float    LFO2toDCO;
uint16_t LFO2toDETUNE1;
uint16_t LFO2toDETUNE2;
uint8_t LFO2toOSC2DETUNE;

int16_t LFO3Level;
byte     LFO3Waveform;
float    LFO3Speed;
uint16_t LFO3toVCF;
uint16_t LFO3toVCA;
uint16_t LFO3toPWM;
float    LFO3toDCO;
uint16_t LFO3toDETUNE1;
uint16_t LFO3toDETUNE2;

uint16_t LFO3toSQR1;
uint16_t LFO3toSQR2;
uint16_t LFO3toSUB;
///

/// ADSR
uint16_t ADSR1_attack;
uint16_t ADSR1_decay;
uint16_t ADSR1_sustain;
uint16_t ADSR1_release;
uint16_t ADSR2_attack;
uint16_t ADSR2_decay;
uint16_t ADSR2_sustain;
uint16_t ADSR2_release;
uint16_t ADSR3_attack;
uint16_t ADSR3_decay;           
uint16_t ADSR3_sustain;         
uint16_t ADSR3_release;

byte ADSR1_curve2Val = 0;
byte ADSR2_curve2Val = 0;

float ADSR1_curve1 = 0.999;
float ADSR1_curve2 = 0.997;
//float ADSR1_curve2 = 0.995;
float ADSR2_curve1 = 0.999f;
float ADSR2_curve2 = 0.9985f;
float ADSR3_curve1 = 0.997;
float ADSR3_curve2 = 0.997;

unsigned long tADSR;
unsigned long tADSR_params;

uint16_t ADSR1Level[NUM_VOICES];
uint16_t ADSR2Level[NUM_VOICES];
uint16_t ADSR3Level[NUM_VOICES];

int16_t ADSR1toVCA;
int16_t ADSR1toVCF;
int16_t ADSR1toPWM;
int16_t ADSR1toDETUNE1;
int16_t ADSR1toDETUNE2;

int16_t ADSR2toVCA;
int16_t ADSR2toVCF;
int16_t ADSR2toPWM;
int16_t ADSR2toDETUNE1;
int16_t ADSR2toDETUNE2;

int16_t ADSR3toVCA;
int16_t ADSR3toVCF;
int16_t ADSR3toPWM;
int16_t ADSR3toDETUNE1;
int16_t ADSR3toDETUNE2;

int16_t ADSR3toSQR1;
int16_t ADSR3toSQR2;
int16_t ADSR3toSUB;
#endif
