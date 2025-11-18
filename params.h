#ifndef __PARAMS_H__
#define __PARAMS_H__

byte noteStart[NUM_VOICES];
byte noteEnd[NUM_VOICES];
byte velocity[NUM_VOICES];
byte note[NUM_VOICES];

byte voiceMode = 0;
byte syncMode = 0;
byte currentVoice = 0;
int16_t unisonDetune = 0;
int16_t analogDrift = 0;
int16_t analogDriftSpeed = 0;
int16_t analogDriftSpread = 0;

byte noiseLevel = 0;

// encoder values
int16_t calibrationVal;
//
bool manualCalibration = false;
int8_t manualCalibrationStage = 0;
int8_t manualCalibrationInitAmpCompOffset[NUM_OSCILLATORS] = {0,0,0,0,0,0,0,0};  

int8_t velocityToVCF = 0;
int8_t velocityToVCA = 0;
int8_t velocityToPWM = 0;

int16_t aftertouch = 0;
int16_t portamentoTime = 0;
byte portamentoMode = 0;

float VCAResonanceCompensation = 0;
bool RESONANCEAmpCompensation = true;

bool VCFADSRRestart = true;
bool VCAADSRRestart = true;
int16_t VCFKeytrack = 0;
uint16_t oscSyncMode = 0;

int8_t ADSR3ToOscSelect;

byte presetName[17] = { 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32 };
String presetNameString;
byte currentPreset;

/// LFO

static constexpr uint16_t LFO1_CC = 4095;
static constexpr uint16_t LFO1_CC_HALF = LFO1_CC / 2;
static constexpr uint16_t LF01_CC_THIRD = LFO1_CC / 3;
static constexpr uint16_t LFO2_CC = 4095;
static constexpr uint16_t LFO2_CC_HALF = LFO2_CC / 2;
static constexpr uint16_t LFO3_CC = 4095;
static constexpr uint16_t LFO3_CC_HALF = LFO2_CC / 2;

int16_t LFO1Level;
int8_t LFO1Waveform;
int16_t LFO1Speed;
int16_t LFO1toVCF;
int16_t LFO1toVCA = 0;
int16_t LFO1toPWM;
int16_t LFO1toDCO;
int16_t LFO1toDETUNE1;
int16_t LFO1toDETUNE2;

int16_t LFO2Level;
int8_t LFO2Waveform;
int16_t LFO2Speed;
int16_t LFO2toVCF;
int16_t LFO2toVCA;
int16_t LFO2toPWM;
int16_t LFO2toDCO;
int16_t LFO2toDETUNE1;
int16_t LFO2toDETUNE2;
int16_t LFO2toOSC2DETUNE;

int16_t LFO3Level;
int8_t LFO3Waveform;
int16_t LFO3Speed;
int16_t LFO3toVCF;
int16_t LFO3toVCA;
int16_t LFO3toPWM;
int16_t LFO3toDCO;
int16_t LFO3toDETUNE1;
int16_t LFO3toDETUNE2;

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

bool ADSR1CurveSelect = false;
bool ADSR2CurveSelect = false;

int8_t ADSR1AttackCurveVal = 0;
int8_t ADSR1DecayCurveVal = 0;
int8_t ADSR2AttackCurveVal = 0;
int8_t ADSR2DecayCurveVal = 0;
int8_t ADSR2_curve2Val = 0;

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
