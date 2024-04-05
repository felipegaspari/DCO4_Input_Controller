void writePreset(uint16_t presetN) {

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  PWMPotsControlManual = false;
  VCAPotsControlManual = false;

  presetSave = false;
  presetSaved = true;

  faderRow2ControlManual = false;
  faderRow1ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}

void loadPreset(uint16_t presetN) {
  //eeprom_buffer_fill();

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;

 
/*   Move parameters to encoder variables */
portamentoTimeVal = portamentoTime;

VCFKeytrackVal = (int16_t)VCFKeytrack;

SQR1LevelVal = (int16_t)(4096 - SQR1Level) / 32;
SQR2LevelVal = (int16_t)(4096 - SQR2Level) / 32;
SubLevelVal = (int16_t)(4096 - SubLevel) / 32;

OSC1IntervalVal = OSC1Interval;
OSC2IntervalVal = OSC2Interval;
OSC2DetuneVal = OSC2Detune;

VCALevelVal = VCALevel;

ADSR3toDETUNE1Val = ADSR3toDETUNE1;
ADSR3toPWMVal = ADSR3toPWM;

LFO1toVCAVal = LFO1toVCA;

LFO2toOSC2DETUNEVal = LFO2toOSC2DETUNE;

LFO1toPWMVal = LFO1toPWM;
LFO2toPWMVal = LFO2toPWM;
LFO3toPWMVal = LFO3toPWM;

LFO1WaveformVal = LFO1Waveform;
LFO2WaveformVal = LFO2Waveform;
LFO3WaveformVal = LFO3Waveform;

oscSyncModeVal = oscSyncMode;

/* NOT IMPLEMENTED
  ADSR1toVCA =
  ADSR1toVCF = 
  //ADSR2
  ADSR2toVCA = word(flashData[27], flashData[28]);
  ADSR2toVCF = word(flashData[29], flashData[30]);
  ADSR2toPWM = word(flashData[31], flashData[32]);
  ADSR2toDETUNE1 = word(flashData[33], flashData[34]);
  ADSR2toDETUNE2 = word(flashData[35], flashData[36]);
  //ADSR3
  ADSR3toVCA = word(flashData[37], flashData[38]);
  ADSR3toVCF = word(flashData[39], flashData[40]);
  ADSR3toDETUNE2 = word(flashData[45], flashData[46]);

  LFO1toVCFVal = expConverterReverse(LFO1toVCF, 500);
  // REVISAR !! LFO2toVCFVal = expConverterReverse(LFO2toVCF, 500);

*/
/* --------------------------------- */


  //digitalWrite(PIN_TRI, triStatus);
  //digitalWrite(PIN_SIN, sineStatus);
  //digitalWrite(PIN_SAW1, sawStatus);
  //digitalWrite(PIN_SAW2, saw2Status);

  for (int i = 0; i < 20; i++) {
    formula_update(i);
    controls_formula_update(i);
  }


sendDetune2Flag = true;
serial_send_portamentoFlag = true;
serial_send_oscSyncModeFlag = true;
serial_send_OSC1IntervalFlag = true;
serial_send_OSC2IntervalFlag = true;
serial_send_LFO1SpeedFlag = true;
serial_send_LFO1toDCOFlag = true;
serial_send_LFO1toDCOWaveChangeFlag = true;
serialSendADSR3ControlValuesFlag = true;
serialSendADSR3toDCOFlag = true;
serialSendADSR3ToOscSelectFlag = true;

  sendSerial();
  delayMicroseconds(100);
  sendSerial();

  presetNameString = String((char *)presetName);

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}
