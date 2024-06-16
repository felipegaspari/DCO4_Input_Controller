
#include "Arduino.h"
//#include <Adafruit_TinyUSB.h>

#define NUM_VOICES 2

byte OSC1Interval = 24;
byte OSC2Interval = 24;
uint16_t OSC2Detune = 255;
float DETUNE1;
float DETUNE2;
uint16_t PW;

uint16_t SubLevel;
uint16_t SQR1Level;
uint16_t SQR2Level;

uint16_t RESONANCE;
uint16_t CUTOFF = 1024;
uint16_t VCALevel = 0;

#define ENABLE_SD

#include "params.h"
#include "auxiliary.h"

#include "Timers_millis.h"
#include "Serial.h"

#include "Controls.h"
#include "buttons.h"
#include "encoders.h"

#include "formulas.h"


//static const float clockFreq = 168000000;

uint32_t i;
byte h;
int val2;
uint32_t contadorLatencia = 0;

uint32_t tiempodeejecucion;

byte SPIvalOut = 32;



void setup() {
#ifdef ENABLE_SERIAL
  Serial.begin(2000000);
#endif

  init_controls();

  init_aux();


#ifdef ENABLE_SERIAL1
  Serial1.setRX(1);
  Serial1.setTX(0);
  Serial1.setPollingMode(true);
  Serial1.setFIFOSize(256);
  Serial1.begin(2500000);
#endif

#ifdef ENABLE_SERIAL2
  Serial2.setRX(5);
  Serial2.setTX(4);
  Serial2.setPollingMode(true);
  Serial2.setFIFOSize(256);
  Serial2.begin(2500000);
#endif
}

void loop1() {

  unsigned long loopStartMicros = micros();

  millisTimer2();

  if (timer1msFlag2) {
    setControlValues();  //LO HACE EL INPUT BOARD
    serial_send_manual_controls();
  }


  if (timer99microsFlag) {
    // sendSerial();
  }

  //serial_read_n();

  unsigned long tiempodeejecuciontotal = micros() - loopStartMicros;

  if (timer200msFlag) {
    //serial_send_param_change(22, ADSR1Level[0]);
    //drawTM(RESONANCE);
    //drawTM(CUTOFF);
    //serial_send_param_change(15, ADSR3toDETUNE1_formula * 100000);
    //Serial.println(tiempodeejecuciontotal);
  }
}

void loop() {

  i = micros();

  //RANDOMNESS1 = (float)random1 / 1440000 * randomnessIntensity1;
  //RANDOMNESS2 = random2 * randomnessIntensity2;

  millisTimer();



  readControls();

  medianFilter();

  if (timer5msFlag) {
    if (ADSR3Enabled && ADSR3toDETUNE1 != 0) {
      serialSendADSR3ControlValuesFlag = true;
    }
  }

  // if (timer223microsFlag == 1) {
  //   for (int i = 2; i < 20; i++) {
  //     formula_update(i);
  //   }
  // }

  uint32_t j = micros();

  tiempodeejecucion = (micros() - j);

  unsigned long tiempodeejecuciontotal = micros() - i;
  //Serial.println(tiempodeejecuciontotal);
  if (timer200msFlag) {
    //serial_send_param_change(22, ADSR1Level[0]);
    //drawTM(RESONANCE);
    //drawTM(CUTOFF);
    //serial_send_param_change(15, ADSR3toDETUNE1_formula * 100000);
    //Serial.println(tiempodeejecuciontotal);
  }

  // if (tiempodeejecuciontotal > 600) {
  //     drawTM(tiempodeejecuciontotal);
  //     drawTMScreen(true);
  //   }

  // if (tiempodeejecucion > 2) {
  // drawTMScreen(true);
  // }

#ifdef ENABLE_SERIAL
  //drawTM(tiempodeejecucion);
  if (1 == 1) {
    //if (timer99microsFlag) {58
    //if (timer31msFlag) {
    // if (tiempodeejecuciontotal > 100 ) {
    //    contadorLatencia++;
    //    float tiemposobrelatencia = (float) micros() / contadorLatencia; // baseline = 5000
    //if (noteEnd[0] == 1) {
    //    Serial.print(tiempodeejecuciontotal);
    //    tiempodeejecucionMedian.add(tiempodeejecuciontotal);
    //    tiempodeejecucionMedian2.add(tiempodeejecucionMedian.getMedian());
    //    Serial.print(tiempodeejecucionMedian.getMedian());
    //    Serial.print((String)" - t_j : " + tiempodeejecuciontotal + (String)" | ");
    //    //    Serial.print((String)" - t / l : " + tiemposobrelatencia);
    //    //    Serial.print((String)" - noteStart" + noteStart[0]);
    //    //    Serial.print((String)" - noteEnd" + noteEnd[0]);
    //    //  //Serial.print((String) " - LFO1Level" + LFO1Level);
    //    ////  Serial.print((String)"- VCF_LFO_INT: " + VCFLFOIntensityLog);
    //    Serial.print((String)"- Fader raw : " + muxFadersRaw[4]);
    //    Serial.print((String)"- Fader median : " + faderMedian[4]);
    //   Serial.print((String)"- Attack2: " + ADSR2_attack);
    //   Serial.print((String)"- Decay2: " + ADSR2_decay);
    //   Serial.print((String)"- Sustain2: " + ADSR2_sustain);
    //    //  Serial.print((String)"- enc1: " + encVal[0]);
    //    //Serial.print((String)" - enc2: " + encVal[1]);
    //    Serial.print((String)" - enc3: " + encVal[2]);
    //    Serial.print((String)" - enc4: " + encVal[3]);
    //    Serial.print((String)" - enc5: " + encVal[4]);
    // Serial.print((String)" - CUTOFF: " + CUTOFF);
    // Serial.print((String)" - RESONANCE: " + RESONANCE);
    // Serial.print((String)" - ADSR2 TO VCF: " + ADSR2toVCF);
    // Serial.print((String)" - LFO TO VCF: " + LFO1toVCF);
    //    Serial.print((String)" - LFO1 TO DCO: " + LFO1toDCO);
    //    Serial.print((String)" - LFO1 SPEED: " + LFO1Speed);
    //    Serial.print((String)" - LFO1 LEVEL: " + LFO1Level);
    //    Serial.print((String)"- DETUNE1 : ");
    //    Serial.print(DETUNE1, 4);
    //Serial.print((String)"- OSC2 DETUNE : " + OSC2Detune);
    //Serial.print((String)" - PW : " + PW);
    //Serial.print((String)" - LFO1toPWM : " + LFO1toPWM);
    //Serial.print((String)" - ADSR1toPWM : " + ADSR1toPWM);
    //Serial.print((String)"- velocity : " + velocity[0]);
    //Serial.print((String)"- freq : " + freq);
    //    Serial.print("HOLA");
    //Serial.print((String)" -enc6" + encVal[5]);

    for (int i = 0; i < 16; i++) {
      if (i != 9 && i != 8) {
        //Serial.print((String) "MuxAnalog" + (int)i + (String) " " + (uint16_t)muxAnalogData[i] + (String) "; ");
        Serial.print((String) " Raw" + (int)i + (String) ": " + (uint16_t)muxAnalogRaw[i] + (String) " ---  ");
      }
    }
    //  for (int i = 0; i < 8; i++) {
    //    Serial.print((String)" -MuxFader" + (int)i + (String)": " + (uint16_t)faderMedian[i]);
    //  }
    // Serial.print(note[0]);
    //Serial.print(analogRead(PC0));
    Serial.println();
  }
#endif
}
