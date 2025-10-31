inline void serial_send_manual_controls(bool presetLoading) {
  if (faderRow1ControlManual || presetLoading) {
    byte dataArray[9];

    // uint16_t ADSR1_attack_serial = linToExpLookup[ADSR1_attack];
    // uint16_t ADSR1_decay_serial = linToExpLookup[ADSR1_decay];
    // uint16_t ADSR1_release_serial = linToExpLookup[ADSR1_release];

    dataArray[0] = (uint8_t)'a';

    dataArray[1] = highByte(ADSR1_attack);
    dataArray[2] = lowByte(ADSR1_attack);
    dataArray[3] = highByte(ADSR1_decay);
    dataArray[4] = lowByte(ADSR1_decay);
    dataArray[5] = highByte(ADSR1_sustain);
    dataArray[6] = lowByte(ADSR1_sustain);
    dataArray[7] = highByte(ADSR1_release);
    dataArray[8] = lowByte(ADSR1_release);

    Serial2.write(dataArray, 9);
    Serial1.write(dataArray, 9);
  }

  if ((faderRow2ControlManual && !ADSR3Enabled) || presetLoading) {
    byte dataArray[9];

    // uint16_t ADSR2_attack_serial = linToExpLookup[ADSR2_attack];
    // uint16_t ADSR2_decay_serial = linToExpLookup[ADSR2_decay];
    // uint16_t ADSR2_release_serial = linToExpLookup[ADSR2_release];

    dataArray[0] = (uint8_t)'b';

    dataArray[1] = highByte(ADSR2_attack);
    dataArray[2] = lowByte(ADSR2_attack);
    dataArray[3] = highByte(ADSR2_decay);
    dataArray[4] = lowByte(ADSR2_decay);
    dataArray[5] = highByte(ADSR2_sustain);
    dataArray[6] = lowByte(ADSR2_sustain);
    dataArray[7] = highByte(ADSR2_release);
    dataArray[8] = lowByte(ADSR2_release);

    Serial2.write(dataArray, 9);
    Serial1.write(dataArray, 9);

  }

  if ((faderRow2ControlManual && ADSR3Enabled) || presetLoading) {
    byte dataArray[9];

    //  uint16_t ADSR3_attack_serial = linToExpLookup[ADSR3_attack];
    //  uint16_t ADSR3_decay_serial = linToExpLookup[ADSR3_decay];
    //  uint16_t ADSR3_release_serial = linToExpLookup[ADSR3_release];

    dataArray[0] = (uint8_t)'c';

    dataArray[1] = highByte(ADSR3_attack);
    dataArray[2] = lowByte(ADSR3_attack);
    dataArray[3] = highByte(ADSR3_decay);
    dataArray[4] = lowByte(ADSR3_decay);
    dataArray[5] = highByte(ADSR3_sustain);
    dataArray[6] = lowByte(ADSR3_sustain);
    dataArray[7] = highByte(ADSR3_release);
    dataArray[8] = lowByte(ADSR3_release);

    Serial2.write(dataArray, 9);
    
  }

  if (VCFPotsControlManual || presetLoading) {
    byte dataArray[9];

    dataArray[0] = (uint8_t)'d';

    dataArray[1] = highByte(CUTOFF);
    dataArray[2] = lowByte(CUTOFF);
    dataArray[3] = highByte(RESONANCE);
    dataArray[4] = lowByte(RESONANCE);
    dataArray[5] = highByte(ADSR2toVCF);
    dataArray[6] = lowByte(ADSR2toVCF);
    dataArray[7] = highByte(LFO2toVCF);
    dataArray[8] = lowByte(LFO2toVCF);

    Serial2.write(dataArray, 9);
  }

  if (VCAPotsControlManual || presetLoading) {
    byte dataArray[3];

    dataArray[0] = (uint8_t)'e';

    dataArray[1] = highByte(ADSR1toVCA);
    dataArray[2] = lowByte(ADSR1toVCA);

    Serial2.write(dataArray, 3);
  }

  if (PWMPotsControlManual || presetLoading) {
    byte dataArray[3];

    dataArray[0] = (uint8_t)'f';

    dataArray[1] = highByte(PW);
    dataArray[2] = lowByte(PW);

    Serial2.write(dataArray, 3);
  }
}

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
      byte dataArray[9];

      //  uint16_t ADSR3_attack_serial = linToExpLookup[ADSR3_attack];
      //  uint16_t ADSR3_decay_serial = linToExpLookup[ADSR3_decay];
      //  uint16_t ADSR3_release_serial = linToExpLookup[ADSR3_release];

      dataArray[0] = (uint8_t)'c';
      dataArray[1] = highByte(ADSR3_attack);
      dataArray[2] = lowByte(ADSR3_attack);
      dataArray[3] = highByte(ADSR3_decay);
      dataArray[4] = lowByte(ADSR3_decay);
      dataArray[5] = highByte(ADSR3_sustain);
      dataArray[6] = lowByte(ADSR3_sustain);
      dataArray[7] = highByte(ADSR3_release);
      dataArray[8] = lowByte(ADSR3_release);


      Serial2.write(dataArray, 9);
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