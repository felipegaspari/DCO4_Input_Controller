void sendParams() {

  // ENABLE IF DETUNE1 is serial
  // DETUNE1 = ((float)LFO1Level * LFO1toDCO_formula) + ((float)ADSR3Level[0] * ADSR3toDETUNE1_formula) + 1 /* + RANDOMNESS1*/;
  // if (DETUNE1 < 0) {
  //   DETUNE1 = 0;
  // }
  DETUNE2 = (uint8_t)((float)(LFO2Level + LFO2_CC_HALF) / 4096 * LFO2toOSC2DETUNE) + OSC2Detune;
  //DETUNE1 = 2.00f;
  //DETUNE2 = 127;

  byte *b = (byte *)&DETUNE1;
  byte dataArray[5];
  byte ndata = 0;

  dataArray[0] = b[0];
  dataArray[1] = b[1];
  dataArray[2] = b[2];
  dataArray[3] = b[3];
  dataArray[4] = (uint8_t)DETUNE2;

  if (Serial2.availableForWrite() > 5) {
    Serial2.write((char *)"p");
    Serial2.write(dataArray, 5);
  }
}

void serial_send_manual_controls(bool presetLoading) {
  if (faderRow1ControlManual || presetLoading) {
    byte dataArray[8];

    dataArray[0] = highByte(ADSR1_attack);
    dataArray[1] = lowByte(ADSR1_attack);
    dataArray[2] = highByte(ADSR1_decay);
    dataArray[3] = lowByte(ADSR1_decay);
    dataArray[4] = highByte(ADSR1_sustain);
    dataArray[5] = lowByte(ADSR1_sustain);
    dataArray[6] = highByte(ADSR1_release);
    dataArray[7] = lowByte(ADSR1_release);

    Serial2.write((char *)"a");
    Serial2.write(dataArray, 8);
  }

  if ((faderRow2ControlManual && !ADSR3Enabled)  || presetLoading) {
    byte dataArray[8];

    dataArray[0] = highByte(ADSR2_attack);
    dataArray[1] = lowByte(ADSR2_attack);
    dataArray[2] = highByte(ADSR2_decay);
    dataArray[3] = lowByte(ADSR2_decay);
    dataArray[4] = highByte(ADSR2_sustain);
    dataArray[5] = lowByte(ADSR2_sustain);
    dataArray[6] = highByte(ADSR2_release);
    dataArray[7] = lowByte(ADSR2_release);

    Serial2.write((char *)"b");
    Serial2.write(dataArray, 8);
  } 
  if ((faderRow2ControlManual && ADSR3Enabled)  || presetLoading) {
    byte dataArray[8];
    dataArray[0] = highByte(ADSR3_attack);
    dataArray[1] = lowByte(ADSR3_attack);
    dataArray[2] = highByte(ADSR3_decay);
    dataArray[3] = lowByte(ADSR3_decay);
    dataArray[4] = highByte(ADSR3_sustain);
    dataArray[5] = lowByte(ADSR3_sustain);
    dataArray[6] = highByte(ADSR3_release);
    dataArray[7] = lowByte(ADSR3_release);

    Serial2.write((char *)"c");
    Serial2.write(dataArray, 8);
  }

  if (VCFPotsControlManual  || presetLoading) {
    byte dataArray[8];
    dataArray[0] = highByte(CUTOFF);
    dataArray[1] = lowByte(CUTOFF);
    dataArray[2] = highByte(RESONANCE);
    dataArray[3] = lowByte(RESONANCE);
    dataArray[4] = highByte(ADSR2toVCF);
    dataArray[5] = lowByte(ADSR2toVCF);
    dataArray[6] = highByte(LFO2toVCF);
    dataArray[7] = lowByte(LFO2toVCF);

    Serial2.write((char *)"d");
    Serial2.write(dataArray, 8);
  }

  if (VCAPotsControlManual  || presetLoading) {
    byte dataArray[2];

    dataArray[0] = highByte(ADSR1toVCA);
    dataArray[1] = lowByte(ADSR1toVCA);

    Serial2.write((char *)"e");
    Serial2.write(dataArray, 2);
  }

  if (PWMPotsControlManual  || presetLoading) {
    byte dataArray[2];

    dataArray[0] = highByte(PW);
    dataArray[1] = lowByte(PW);

    Serial2.write((char *)"f");
    Serial2.write(dataArray, 2);
  }
}

void sendSerial() {  // to DCO

  if (sendDetune2Flag) {
    if (Serial2.availableForWrite() > 1) {
      DETUNE2 = (uint8_t)((float)(LFO2Level + LFO2_CC_HALF) / 4096 * LFO2toOSC2DETUNE) + OSC2Detune;
      byte byteArray[2] = { (uint8_t)'q', (uint8_t)DETUNE2 };
      Serial2.write(byteArray, 2);
      sendDetune2Flag = false;
    }
  }

  if (serial_send_portamentoFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'r', portamentoTime };
      Serial2.write(byteArray, 2);
      serial_send_portamentoFlag = false;
    }
  }

  if (serial_send_oscSyncModeFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'t', oscSyncMode };
      Serial2.write(byteArray, 2);
      serial_send_oscSyncModeFlag = false;
    }
  }

  if (serial_send_OSC1IntervalFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'y', OSC1Interval };
      Serial2.write(byteArray, 2);
      serial_send_OSC1IntervalFlag = false;
    }
  }

  if (serial_send_OSC2IntervalFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'z', OSC2Interval };
      Serial2.write(byteArray, 2);
      serial_send_OSC2IntervalFlag = false;
    }
  }

  if (serial_send_LFO1SpeedFlag) {
    if (Serial2.availableForWrite() > 2) {
      byte *b = (byte *)&LFO1SpeedVal;
      byte byteArray[3] = { (byte)'l', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serial_send_LFO1SpeedFlag = false;
    }
  }

  if (serial_send_LFO1toDCOFlag) {
    if (Serial2.availableForWrite() > 2) {
      byte *b = (byte *)&LFO1toDCOVal;
      byte byteArray[3] = { (byte)'m', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serial_send_LFO1toDCOFlag = false;
    }
  }

  if (serial_send_LFO1toDCOWaveChangeFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'b', LFO1Waveform };
      Serial2.write(byteArray, 2);
      serial_send_LFO1toDCOWaveChangeFlag = false;
    }
  }

  if (serialSendADSR3ControlValuesFlag) {
    if (Serial2.availableForWrite() > 4) {
      byte ADSR3BytesArray[5];
      ADSR3BytesArray[0] = (byte)'s';
      ADSR3BytesArray[1] = (byte)(ADSR3_attack / 16);
      ADSR3BytesArray[2] = (byte)(ADSR3_decay / 16);
      ADSR3BytesArray[3] = (byte)(ADSR3_sustain / 16);
      ADSR3BytesArray[4] = (byte)(ADSR3_release / 16);
      //Serial2.write((char *)"s");
      Serial2.write(ADSR3BytesArray, 5);
      serialSendADSR3ControlValuesFlag = false;
    }
  }

  if (serialSendADSR3toDCOFlag) {
    if (Serial2.availableForWrite() > 2) {
      byte *b = (byte *)&ADSR3toDETUNE1;
      byte byteArray[3] = { (byte)'w', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serialSendADSR3toDCOFlag = false;
    }
  }
  if (serialSendADSR3ToOscSelectFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (byte)'c', (uint8_t)ADSR3ToOscSelect };
      Serial2.write(byteArray, 2);
      serialSendADSR3ToOscSelectFlag = false;
    }
  }
}