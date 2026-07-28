// @1 ms / preset load: TX manual control blocks 'a'..'f' to Mainboard (Serial2) and Screen (Serial1).
void serial_send_manual_controls(bool presetLoading) {
  if (faderRow1ControlManual || presetLoading) {
    // Exponential-mapped values for DCO
    byte dataArrayDCO[8];
    uint16_t ADSR1_attack_serial  = linToExpLookup[ADSR1_attack];
    uint16_t ADSR1_decay_serial   = linToExpLookup[ADSR1_decay];
    uint16_t ADSR1_release_serial = linToExpLookup[ADSR1_release];

    dataArrayDCO[0] = highByte(ADSR1_attack_serial);
    dataArrayDCO[1] = lowByte(ADSR1_attack_serial);
    dataArrayDCO[2] = highByte(ADSR1_decay_serial);
    dataArrayDCO[3] = lowByte(ADSR1_decay_serial);
    dataArrayDCO[4] = highByte(ADSR1_sustain);
    dataArrayDCO[5] = lowByte(ADSR1_sustain);
    dataArrayDCO[6] = highByte(ADSR1_release_serial);
    dataArrayDCO[7] = lowByte(ADSR1_release_serial);

    // Raw fader values for Screen (so UI bars reflect linear position)
    byte dataArrayScreen[8];
    dataArrayScreen[0] = highByte(ADSR1_attack);
    dataArrayScreen[1] = lowByte(ADSR1_attack);
    dataArrayScreen[2] = highByte(ADSR1_decay);
    dataArrayScreen[3] = lowByte(ADSR1_decay);
    dataArrayScreen[4] = highByte(ADSR1_sustain);
    dataArrayScreen[5] = lowByte(ADSR1_sustain);
    dataArrayScreen[6] = highByte(ADSR1_release);
    dataArrayScreen[7] = lowByte(ADSR1_release);

    // Send ADSR1 values to DCO and Screen
    Serial2.write((char *)"a");
    Serial2.write(dataArrayDCO, 8);
    Serial1.write((char *)"a");
    Serial1.write(dataArrayScreen, 8);
  }

  if ((faderRow2ControlManual && !ADSR3Enabled)  || presetLoading) {
    // Exponential-mapped values for DCO
    byte dataArrayDCO[8];
    uint16_t ADSR2_attack_serial  = linToExpLookup[ADSR2_attack];
    uint16_t ADSR2_decay_serial   = linToExpLookup[ADSR2_decay];
    uint16_t ADSR2_release_serial = linToExpLookup[ADSR2_release];

    dataArrayDCO[0] = highByte(ADSR2_attack_serial);
    dataArrayDCO[1] = lowByte(ADSR2_attack_serial);
    dataArrayDCO[2] = highByte(ADSR2_decay_serial);
    dataArrayDCO[3] = lowByte(ADSR2_decay_serial);
    dataArrayDCO[4] = highByte(ADSR2_sustain);
    dataArrayDCO[5] = lowByte(ADSR2_sustain);
    dataArrayDCO[6] = highByte(ADSR2_release_serial);
    dataArrayDCO[7] = lowByte(ADSR2_release_serial);

    // Raw fader values for Screen
    byte dataArrayScreen[8];
    dataArrayScreen[0] = highByte(ADSR2_attack);
    dataArrayScreen[1] = lowByte(ADSR2_attack);
    dataArrayScreen[2] = highByte(ADSR2_decay);
    dataArrayScreen[3] = lowByte(ADSR2_decay);
    dataArrayScreen[4] = highByte(ADSR2_sustain);
    dataArrayScreen[5] = lowByte(ADSR2_sustain);
    dataArrayScreen[6] = highByte(ADSR2_release);
    dataArrayScreen[7] = lowByte(ADSR2_release);

    // Send ADSR2 values to DCO and Screen
    Serial2.write((char *)"b");
    Serial2.write(dataArrayDCO, 8);
    Serial1.write((char *)"b");
    Serial1.write(dataArrayScreen, 8);
  } 
  if ((faderRow2ControlManual && ADSR3Enabled)  || presetLoading) {
    byte dataArray[8];

    uint16_t ADSR3_attack_serial  = linToExpLookup[ADSR3_attack];
    uint16_t ADSR3_decay_serial   = linToExpLookup[ADSR3_decay];
    uint16_t ADSR3_release_serial = linToExpLookup[ADSR3_release];

    dataArray[0] = highByte(ADSR3_attack_serial);
    dataArray[1] = lowByte(ADSR3_attack_serial);
    dataArray[2] = highByte(ADSR3_decay_serial);
    dataArray[3] = lowByte(ADSR3_decay_serial);
    dataArray[4] = highByte(ADSR3_sustain);
    dataArray[5] = lowByte(ADSR3_sustain);
    dataArray[6] = highByte(ADSR3_release_serial);
    dataArray[7] = lowByte(ADSR3_release_serial);

    // Send ADSR3 manual values to DCO (Serial2) only.
    // (Screen does not currently display ADSR3 via 'c' frames.)
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

// Legacy flag-driven Serial2 TX (portamento/sync/etc). Not scheduled in loop1 today.
void sendSerial() {  // to DCO


  if (serial_send_portamentoFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'r', (uint8_t)portamentoTime };
      Serial2.write(byteArray, 2);
      serial_send_portamentoFlag = false;
    }
  }

  if (serial_send_oscSyncModeFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'t', (uint8_t)oscSyncMode };
      Serial2.write(byteArray, 2);
      serial_send_oscSyncModeFlag = false;
    }
  }

  if (serial_send_OSC1IntervalFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'y', (uint8_t)OSC1Interval };
      Serial2.write(byteArray, 2);
      serial_send_OSC1IntervalFlag = false;
    }
  }

  if (serial_send_OSC2IntervalFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'z', (uint8_t)OSC2Interval };
      Serial2.write(byteArray, 2);
      serial_send_OSC2IntervalFlag = false;
    }
  }

  if (serial_send_LFO1SpeedFlag) {
    if (Serial2.availableForWrite() > 2) {
      byte *b = (byte *)&LFO1Speed;
      byte byteArray[3] = { (byte)'l', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serial_send_LFO1SpeedFlag = false;
    }
  }

  if (serial_send_LFO1toDCOFlag) {
    if (Serial2.availableForWrite() > 2) {
      byte *b = (byte *)&LFO1toDCO;
      byte byteArray[3] = { (byte)'m', b[0], b[1] };
      Serial2.write(byteArray, 3);
      serial_send_LFO1toDCOFlag = false;
    }
  }

  if (serial_send_LFO1toDCOWaveChangeFlag) {
    if (Serial2.availableForWrite() > 1) {
      byte byteArray[2] = { (uint8_t)'b', (uint8_t)LFO1Waveform };
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