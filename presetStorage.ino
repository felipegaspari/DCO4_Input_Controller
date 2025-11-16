void initFS() {
  LittleFS.begin();

  if (!LittleFS.exists("presetBank1")) {
    fileBank1 = LittleFS.open("presetBank1", "w+");
    // Fresh file: initialise RAM bank and on-flash file to zeros.
    memset(presetBank1Buffer, 0, flashBankSize);
    memset(flashData,          0, flashPresetSize);
    // Pre-allocate full bank region on flash so high-index presets
    // can be written safely later.
    for (uint16_t offset = 0; offset < flashBankSize; ) {
      uint8_t zeros[64] = {0};
      uint16_t chunk = (flashBankSize - offset) > sizeof(zeros)
                       ? sizeof(zeros)
                       : (flashBankSize - offset);
      fileBank1.write(zeros, chunk);
      offset += chunk;
    }
    fileBank1.flush();
    fileBank1.seek(0);
  } else {
    fileBank1 = LittleFS.open("presetBank1", "r+");
    // Ensure the underlying file is at least flashBankSize bytes long so
    // we can write any preset index 0..NUM_PRESETS-1 safely.
    uint32_t sz = fileBank1.size();
    if (sz < flashBankSize) {
      fileBank1.seek(sz);
      for (uint32_t offset = sz; offset < flashBankSize; ) {
        uint8_t zeros[64] = {0};
        uint32_t chunk = (flashBankSize - offset) > sizeof(zeros)
                         ? sizeof(zeros)
                         : (flashBankSize - offset);
        fileBank1.write(zeros, chunk);
        offset += chunk;
      }
      fileBank1.flush();
      fileBank1.seek(0);
    } else {
      fileBank1.seek(0);
    }
  }

  // Load full bank into RAM buffer.
  fileBank1.read(presetBank1Buffer, flashBankSize);
  fileBank1.close();

  // Copy first preset slot into flashData for initial load.
  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = presetBank1Buffer[i];
  }

  loadPreset(1);
}

void load_preset_name(byte destinationPreset) {

  if (destinationPreset >= NUM_PRESETS) {
    return;
  }

  uint16_t startByteN = destinationPreset * flashPresetSize;

  loadedName[0] = presetBank1Buffer[119 + startByteN];
  loadedName[1] = presetBank1Buffer[120 + startByteN];
  loadedName[2] = presetBank1Buffer[121 + startByteN];
  loadedName[3] = presetBank1Buffer[122 + startByteN];
  loadedName[4] = presetBank1Buffer[123 + startByteN];
  loadedName[5] = presetBank1Buffer[124 + startByteN];
  loadedName[6] = presetBank1Buffer[125 + startByteN];
  loadedName[7] = presetBank1Buffer[126 + startByteN];
  loadedName[8] = presetBank1Buffer[127 + startByteN];
  loadedName[9] = presetBank1Buffer[128 + startByteN];
  loadedName[10] = presetBank1Buffer[129 + startByteN];
  loadedName[11] = presetBank1Buffer[130 + startByteN];
}

void loadPreset(uint16_t presetN) {

  if (presetN >= NUM_PRESETS) {
    return;
  }

  byte unused_data;
  uint16_t unused_data_uint16_t;

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;
  ADSR3Enabled = false;

  float a;
  int b;

  uint16_t startByteN = presetN * flashPresetSize;

  for (int i = 0; i < flashPresetSize; i++) {
    flashData[i] = presetBank1Buffer[i + startByteN];
  }

  // bits
  sawStatus = bitRead(flashData[0], 0);
  saw2Status = bitRead(flashData[0], 1);
  triStatus = bitRead(flashData[0], 2);
  sineStatus = bitRead(flashData[0], 3);
  sqr1Status = bitRead(flashData[0], 4);
  sqr2Status = bitRead(flashData[0], 5);
  RESONANCEAmpCompensation = bitRead(flashData[0], 6);
  VCAADSRRestart = bitRead(flashData[0], 7);

  VCFADSRRestart = bitRead(flashData[1], 0);
  PWMPotsControlManual = bitRead(flashData[1], 1);  // makes no sense, should be off after loading or writing presets
  ADSR3Enabled = bitRead(flashData[1], 2);
  unused_data = bitRead(flashData[1], 3);
  unused_data = bitRead(flashData[1], 4);
  unused_data = bitRead(flashData[1], 5);
  unused_data = bitRead(flashData[1], 6);
  unused_data = bitRead(flashData[1], 7);

  // flashData[2] can carry a tiny per‑preset header / version.
  // For older presets this will be 0.
  uint8_t presetFormatVersion = flashData[2];
  (void)presetFormatVersion;  // reserved for future use
  unused_data = flashData[3];
  unused_data = flashData[4];
  unused_data = flashData[5];

  // int8_t
  LFO1Waveform = (int8_t)flashData[6];
  LFO2Waveform = (int8_t)flashData[7];

  OSC1Interval = (int8_t)flashData[8];

  OSC2Interval = (int8_t)flashData[9];

  oscSyncMode = (int8_t)flashData[10];
  portamentoTime = (int16_t)flashData[11];
  voiceMode = (int8_t)flashData[12];

  ADSR3ToOscSelect = (int8_t)flashData[13];
  velocityToVCF = (int8_t)flashData[14];
  velocityToVCA = (int8_t)flashData[15];

  unisonDetune = (int16_t)flashData[16];
  ADSR1AttackCurveVal = (int8_t)flashData[17];
  ADSR1DecayCurveVal = (int8_t)flashData[18];
  ADSR2AttackCurveVal = (int8_t)flashData[19];
  ADSR2DecayCurveVal = (int8_t)flashData[20];
  analogDrift = (int16_t)flashData[21];
  analogDriftSpeed = (int16_t)flashData[22];
  analogDriftSpread = (int16_t)flashData[23];
  syncMode = flashData[24];
  unused_data = flashData[25];
  unused_data = flashData[26];
  unused_data = flashData[27];
  unused_data = flashData[28];
  unused_data = flashData[29];

  // int16_t
  VCFKeytrack = (int16_t)word(flashData[30], flashData[31]);
  SQR1Level = (int16_t)word(flashData[32], flashData[33]);
  SQR2Level = (int16_t)word(flashData[34], flashData[35]);
  SubLevel = (int16_t)word(flashData[36], flashData[37]);
  unused_data_uint16_t = word(flashData[38], flashData[39]);
  LFO1toDCO = (int16_t)word(flashData[40], flashData[41]);
  LFO1Speed = (int16_t)word(flashData[42], flashData[43]);
  LFO2Speed = (int16_t)word(flashData[44], flashData[45]);
  ADSR3toPWM = (int16_t)word(flashData[46], flashData[47]);
  ADSR3toDETUNE1 = (int16_t)word(flashData[48], flashData[49]);

  unused_data_uint16_t = word(flashData[50], flashData[51]);
  unused_data_uint16_t = word(flashData[52], flashData[53]);
  unused_data_uint16_t = word(flashData[54], flashData[55]);
  unused_data_uint16_t = word(flashData[56], flashData[57]);
  unused_data_uint16_t = word(flashData[58], flashData[59]);
  unused_data_uint16_t = word(flashData[60], flashData[61]);

  // uint16_t
  OSC2Detune = (int16_t)word(flashData[62], flashData[63]);
  LFO2toOSC2DETUNE = (int16_t)word(flashData[64], flashData[65]);
  VCALevel = (int16_t)word(flashData[66], flashData[67]);
  LFO1toVCA = (int16_t)word(flashData[68], flashData[69]);
  LFO2toPWM = (int16_t)word(flashData[70], flashData[71]);

  unused_data_uint16_t = word(flashData[72], flashData[73]);

  CUTOFF = word(flashData[74], flashData[75]);
  RESONANCE = word(flashData[76], flashData[77]);
  ADSR2toVCF = word(flashData[78], flashData[79]);
  LFO2toVCF = word(flashData[80], flashData[81]);
  ADSR1toVCA = word(flashData[82], flashData[83]);
  PW = word(flashData[84], flashData[85]);

  unused_data_uint16_t = word(flashData[86], flashData[87]);

  ADSR1_attack = word(flashData[88], flashData[89]);
  ADSR1_decay = word(flashData[90], flashData[91]);
  ADSR1_sustain = word(flashData[92], flashData[93]);
  ADSR1_release = word(flashData[94], flashData[95]);

  ADSR2_attack = word(flashData[96], flashData[97]);
  ADSR2_decay = word(flashData[98], flashData[99]);
  ADSR2_sustain = word(flashData[100], flashData[101]);
  ADSR2_release = word(flashData[102], flashData[103]);

  ADSR3_attack = word(flashData[104], flashData[105]);
  ADSR3_decay = word(flashData[106], flashData[107]);
  ADSR3_sustain = word(flashData[108], flashData[109]);
  ADSR3_release = word(flashData[110], flashData[111]);

  unused_data_uint16_t = word(flashData[112], flashData[113]);
  unused_data_uint16_t = word(flashData[114], flashData[115]);
  unused_data_uint16_t = word(flashData[116], flashData[117]);

  unused_data = flashData[118];

  presetName[0]  = flashData[119];
  presetName[1]  = flashData[120];
  presetName[2]  = flashData[121];
  presetName[3]  = flashData[122];
  presetName[4]  = flashData[123];
  presetName[5]  = flashData[124];
  presetName[6]  = flashData[125];
  presetName[7]  = flashData[126];
  presetName[8]  = flashData[127];
  presetName[9]  = flashData[128];
  presetName[10] = flashData[129];
  presetName[11] = flashData[130];
  presetName[12] = flashData[131];
  presetName[13] = flashData[132];
  presetName[14] = flashData[133];
  presetName[15] = flashData[134];

  /**********************************************************************************/
  /////////////////// START NEW STUFF //

  serial_send_signal(6);  // Screen silence

  delay(10);

  // PWM control Manual off after loading
  serial_send_param_change_byte(ParamId::PARAM_PWM_POTS_CONTROL_MANUAL, 0, false);
  // ADSR3Enabled OFF
  serial_send_param_change_byte(ParamId::PARAM_ADSR3_ENABLED, 0, false);

  serial_send_param_change_byte(ParamId::PARAM_SAW_STATUS,  (uint8_t)sawStatus,  false);
  serial_send_param_change_byte(ParamId::PARAM_SAW2_STATUS, (uint8_t)saw2Status, false);
  serial_send_param_change_byte(ParamId::PARAM_TRI_STATUS,  (uint8_t)triStatus,  false);
  serial_send_param_change_byte(ParamId::PARAM_SINE_STATUS, (uint8_t)sineStatus, false);
  serial_send_param_change_byte(ParamId::PARAM_SQR1_STATUS, (uint8_t)sqr1Status, false);
  serial_send_param_change_byte(ParamId::PARAM_SQR2_STATUS, (uint8_t)sqr2Status, false);

  set_LED_Status(16, 0);

  delay(2);

  serial_send_param_change_byte(ParamId::PARAM_RESONANCE_COMPENSATION, (uint8_t)RESONANCEAmpCompensation, false);
  serial_send_param_change_byte(ParamId::PARAM_VCA_ADSR_RESTART,        (uint8_t)VCAADSRRestart,          false);
  serial_send_param_change_byte(ParamId::PARAM_VCF_ADSR_RESTART,        (uint8_t)VCFADSRRestart,          false);
  serial_send_param_change_byte(ParamId::PARAM_ADSR3_TO_OSC_SELECT,     (uint8_t)ADSR3ToOscSelect,        false);

  // LFO1Waveform
  serial_send_param_change_byte(ParamId::PARAM_LFO1_WAVEFORM, (uint8_t)LFO1Waveform, false);
  // LFO2Waveform
  serial_send_param_change_byte(ParamId::PARAM_LFO2_WAVEFORM, (uint8_t)LFO2Waveform, false);
  
delay(2);

  serial_send_param_change_byte(ParamId::PARAM_OSC1_INTERVAL,   (uint8_t)OSC1Interval,   false);
  serial_send_param_change_byte(ParamId::PARAM_OSC2_INTERVAL,   (uint8_t)OSC2Interval,   false);

  serial_send_param_change_byte(ParamId::PARAM_OSC_SYNC_MODE,   (uint8_t)oscSyncMode,    false);

  serial_send_param_change_byte(ParamId::PARAM_PORTAMENTO_TIME, (uint8_t)portamentoTime, false);

  serial_send_param_change_byte(ParamId::PARAM_VOICE_MODE,      (uint8_t)voiceMode,      false);

delay(2);

  serial_send_param_change_byte(ParamId::PARAM_ADSR3_TO_OSC_SELECT, (uint8_t)ADSR3ToOscSelect, false);

  serial_send_param_change_byte(ParamId::PARAM_VELOCITY_TO_VCF,     (uint8_t)velocityToVCF,    false);
  serial_send_param_change_byte(ParamId::PARAM_VELOCITY_TO_VCA,     (uint8_t)velocityToVCA,    false);

  serial_send_param_change_byte(ParamId::PARAM_SQR1_LEVEL,          (uint8_t)SQR1Level,        true);
  serial_send_param_change_byte(ParamId::PARAM_SQR2_LEVEL,          (uint8_t)SQR2Level,        true);
  serial_send_param_change_byte(ParamId::PARAM_SUB_LEVEL,           (uint8_t)SubLevel,         true);

  serial_send_param_change_byte(ParamId::PARAM_UNISON_DETUNE,       (uint8_t)unisonDetune,     false);
  serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_AMOUNT, (uint8_t)analogDrift,      false);
  serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_SPEED,  (uint8_t)analogDriftSpeed, false);
  serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_SPREAD, (uint8_t)analogDriftSpread,false);
  
  serial_send_param_change_byte(ParamId::PARAM_SYNC_MODE,           (uint8_t)syncMode,         false);

delay(2);

  serial_send_param_change(ParamId::PARAM_LFO1_TO_DCO, (uint16_t)LFO1toDCO,  false);

  serial_send_param_change(ParamId::PARAM_LFO1_SPEED,  (uint16_t)LFO1Speed,  false);

  serial_send_param_change(ParamId::PARAM_LFO2_SPEED,  (uint16_t)LFO2Speed,  false);

  serial_send_param_change(ParamId::PARAM_VCA_LEVEL,   (uint16_t)VCALevel,   false);

  serial_send_param_change(ParamId::PARAM_LFO1_TO_VCA, (uint16_t)LFO1toVCA,  false);

  serial_send_param_change(ParamId::PARAM_LFO2_TO_PW,  (uint16_t)LFO2toPWM,  false);
delay(2);
  serial_send_param_change(ParamId::PARAM_ADSR3_TO_PWM,     (uint16_t)ADSR3toPWM + 512, false);

  serial_send_param_change(ParamId::PARAM_ADSR3_TO_DETUNE1, (uint16_t)ADSR3toDETUNE1,   false);

  serial_send_param_change(ParamId::PARAM_OSC2_DETUNE_VAL,  (uint16_t)OSC2Detune,       false);

  serial_send_param_change(ParamId::PARAM_LFO2_TO_DETUNE2,  (uint16_t)LFO2toOSC2DETUNE, false);

  serial_send_manual_controls(true);  
  
  delay(2);

  serial_send_param_change_byte(ParamId::PARAM_ADSR1_ATTACK_CURVE, (uint8_t)ADSR1AttackCurveVal, false);
  serial_send_param_change_byte(ParamId::PARAM_ADSR1_DECAY_CURVE,  (uint8_t)ADSR1DecayCurveVal,  false);
  serial_send_param_change_byte(ParamId::PARAM_ADSR2_ATTACK_CURVE, (uint8_t)ADSR2AttackCurveVal, false);
  serial_send_param_change_byte(ParamId::PARAM_ADSR2_DECAY_CURVE,  (uint8_t)ADSR2DecayCurveVal,  false);

  delay(100);
  // includes:
  // CUTOFF                   ------  PARAM GROUP VCF
  // RESONANCE                ------  PARAM GROUP VCF
  // ADSR2toVCF               ------  PARAM GROUP VCF
  // LFO2toVCF                ------  PARAM GROUP VCF
  // formula_update(4);       ------  PARAM GROUP VCF
  // formula_update(2);       ------  PARAM GROUP VCF
  //
  // ADSR1toVCA
  // PW
  //
  //  ADSR1_attack
  //  ADSR1_decay
  //  ADSR1_sustain
  //  ADSR1_release
  //
  //  ADSR2_attack
  //  ADSR2_decay
  //  ADSR2_sustain
  //  ADSR2_release
  //
  //  ADSR3_attack
  //  ADSR3_decay
  //  ADSR3_sustain
  //  ADSR3_release

  //////////////// END NEW STUFF

  presetNameString = String((char *)presetName);

  currentPreset = presetN;
  presetSelectVal = currentPreset;



  delay(1);

  serial_send_preset_scroll(currentPreset, presetName);
  serial_send_signal(1);  // Screen silence ENDs
}

// Debug helper: dump full preset bank to USB Serial (if enabled).
// Prints, for each preset index:
//   - preset number
//   - 12-char name (offset 119..130)
//   - first 16 data bytes in hex
void dumpPresetBankToSerial() {
#ifdef ENABLE_SERIAL
  Serial.println(F("=== Preset bank dump ==="));
  for (uint16_t p = 0; p < NUM_PRESETS; ++p) {
    uint32_t startByteN = (uint32_t)p * flashPresetSize;
    if (startByteN + flashPresetSize > flashBankSize) {
      break;
    }

    Serial.print(F("Preset "));
    Serial.print(p);
    Serial.print(F("  name=\""));

    uint32_t nameOffset = startByteN + 119;
  for (uint8_t i = 0; i < 16; ++i) {
      char c = (char)presetBank1Buffer[nameOffset + i];
      if (c < 32) c = ' ';
      Serial.print(c);
    }
    Serial.print(F("\"  data[0..15]="));

    for (uint8_t i = 0; i < 16; ++i) {
      uint8_t b = presetBank1Buffer[startByteN + i];
      if (b < 16) Serial.print('0');
      Serial.print(b, HEX);
      Serial.print(' ');
    }
    Serial.println();
  }
  Serial.println(F("=== End of preset bank dump ==="));
#endif
}

void get_preset_name(byte presetN, byte (&myarray)[16]) {
  if (presetN >= NUM_PRESETS) {
    return;
  }
  uint16_t startByteN = presetN * flashPresetSize;
  for (int i = 0; i < 16; i++) {
    myarray[i] = presetBank1Buffer[startByteN + 119 + i];
  }
}

void writePreset(uint16_t presetN) {

  if (presetN >= NUM_PRESETS) {
    return;
  }

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;
  ADSR3Enabled = false;

  uint16_t startByteN = presetN * flashPresetSize;

  // bits
  bitWrite(flashData[0], 0, sawStatus);
  bitWrite(flashData[0], 1, saw2Status);
  bitWrite(flashData[0], 2, triStatus);
  bitWrite(flashData[0], 3, sineStatus);
  bitWrite(flashData[0], 4, sqr1Status);
  bitWrite(flashData[0], 5, sqr2Status);
  bitWrite(flashData[0], 6, RESONANCEAmpCompensation);
  bitWrite(flashData[0], 7, VCAADSRRestart);

  bitWrite(flashData[1], 0, VCFADSRRestart);
  bitWrite(flashData[1], 1, PWMPotsControlManual);
  bitWrite(flashData[1], 2, ADSR3Enabled);
  bitWrite(flashData[1], 3, 0);
  bitWrite(flashData[1], 4, 0);
  bitWrite(flashData[1], 5, 0);
  bitWrite(flashData[1], 6, 0);
  bitWrite(flashData[1], 7, 0);
  flashData[2] = 0;
  flashData[3] = 0;
  flashData[4] = 0;
  flashData[5] = 0;

  // int8_t
  flashData[6] = (byte)LFO1Waveform;
  flashData[7] = (byte)LFO2Waveform;
  flashData[8] = (byte)OSC1Interval;
  flashData[9] = (byte)OSC2Interval;
  flashData[10] = (byte)oscSyncMode;
  flashData[11] = (byte)portamentoTime;
  flashData[12] = (byte)voiceMode;
  flashData[13] = (byte)ADSR3ToOscSelect;
  flashData[14] = (byte)velocityToVCF;
  flashData[15] = (byte)velocityToVCA;
  flashData[16] = (byte)unisonDetune;
  flashData[17] = (byte)ADSR1AttackCurveVal;
  flashData[18] = (byte)ADSR1DecayCurveVal;
  flashData[19] = (byte)ADSR2AttackCurveVal;
  flashData[20] = (byte)ADSR2DecayCurveVal;
  flashData[21] = (byte)analogDrift;
  flashData[22] = (byte)analogDriftSpeed;
  flashData[23] = (byte)analogDriftSpread;
  flashData[24] = (byte)syncMode;
  flashData[25] = 0;
  flashData[26] = 0;
  flashData[27] = 0;
  flashData[28] = 0;
  flashData[29] = 0;
  // int16_t
  flashData[30] = highByte(VCFKeytrack);
  flashData[31] = lowByte(VCFKeytrack);
  flashData[32] = highByte(SQR1Level);
  flashData[33] = lowByte(SQR1Level);
  flashData[34] = highByte(SQR2Level);
  flashData[35] = lowByte(SQR2Level);
  flashData[36] = highByte(SubLevel);
  flashData[37] = lowByte(SubLevel);
  flashData[38] = highByte(0);
  flashData[39] = lowByte(0);
  flashData[40] = highByte(LFO1toDCO);
  flashData[41] = lowByte(LFO1toDCO);
  flashData[42] = highByte(LFO1Speed);
  flashData[43] = lowByte(LFO1Speed);
  flashData[44] = highByte(LFO2Speed);
  flashData[45] = lowByte(LFO2Speed);
  flashData[46] = highByte(ADSR3toPWM);
  flashData[47] = lowByte(ADSR3toPWM);
  flashData[48] = highByte(ADSR3toDETUNE1);
  flashData[49] = lowByte(ADSR3toDETUNE1);
  flashData[50] = 0;
  flashData[51] = 0;
  flashData[52] = 0;
  flashData[53] = 0;
  flashData[54] = 0;
  flashData[55] = 0;
  flashData[56] = 0;
  flashData[57] = 0;
  flashData[58] = 0;
  flashData[59] = 0;
  flashData[60] = 0;
  flashData[61] = 0;

  // uint16_t
  flashData[62] = highByte(OSC2Detune);
  flashData[63] = lowByte(OSC2Detune);
  flashData[64] = highByte(LFO2toOSC2DETUNE);
  flashData[65] = lowByte(LFO2toOSC2DETUNE);
  flashData[66] = highByte(VCALevel);
  flashData[67] = lowByte(VCALevel);
  flashData[68] = highByte(LFO1toVCA);
  flashData[69] = lowByte(LFO1toVCA);
  flashData[70] = highByte(LFO2toPWM);
  flashData[71] = lowByte(LFO2toPWM);

  flashData[72] = highByte(0);
  flashData[73] = lowByte(0);

  flashData[74] = highByte(CUTOFF);
  flashData[75] = lowByte(CUTOFF);
  flashData[76] = highByte(RESONANCE);
  flashData[77] = lowByte(RESONANCE);
  flashData[78] = highByte(ADSR2toVCF);
  flashData[79] = lowByte(ADSR2toVCF);
  flashData[80] = highByte(LFO2toVCF);
  flashData[81] = lowByte(LFO2toVCF);
  flashData[82] = highByte(ADSR1toVCA);
  flashData[83] = lowByte(ADSR1toVCA);
  flashData[84] = highByte(PW);
  flashData[85] = lowByte(PW);
  flashData[86] = highByte(0);
  flashData[87] = lowByte(0);
  flashData[88] = highByte(ADSR1_attack);
  flashData[89] = lowByte(ADSR1_attack);
  flashData[90] = highByte(ADSR1_decay);
  flashData[91] = lowByte(ADSR1_decay);
  flashData[92] = highByte(ADSR1_sustain);
  flashData[93] = lowByte(ADSR1_sustain);
  flashData[94] = highByte(ADSR1_release);
  flashData[95] = lowByte(ADSR1_release);
  flashData[96] = highByte(ADSR2_attack);
  flashData[97] = lowByte(ADSR2_attack);
  flashData[98] = highByte(ADSR2_decay);
  flashData[99] = lowByte(ADSR2_decay);
  flashData[100] = highByte(ADSR2_sustain);
  flashData[101] = lowByte(ADSR2_sustain);
  flashData[102] = highByte(ADSR2_release);
  flashData[103] = lowByte(ADSR2_release);
  flashData[104] = highByte(ADSR3_attack);
  flashData[105] = lowByte(ADSR3_attack);
  flashData[106] = highByte(ADSR3_decay);
  flashData[107] = lowByte(ADSR3_decay);
  flashData[108] = highByte(ADSR3_sustain);
  flashData[109] = lowByte(ADSR3_sustain);
  flashData[110] = highByte(ADSR3_release);
  flashData[111] = lowByte(ADSR3_release);
  flashData[112] = highByte(0);
  flashData[113] = lowByte(0);
  flashData[114] = highByte(0);
  flashData[115] = lowByte(0);
  flashData[116] = highByte(0);
  flashData[117] = lowByte(0);

  flashData[118] = 0;

  ///
  flashData[119] = presetNameVal[0];
  flashData[120] = presetNameVal[1];
  flashData[121] = presetNameVal[2];
  flashData[122] = presetNameVal[3];
  flashData[123] = presetNameVal[4];
  flashData[124] = presetNameVal[5];
  flashData[125] = presetNameVal[6];
  flashData[126] = presetNameVal[7];
  flashData[127] = presetNameVal[8];
  flashData[128] = presetNameVal[9];
  flashData[129] = presetNameVal[10];
  flashData[130] = presetNameVal[11];
  flashData[131] = presetNameVal[12];
  flashData[132] = presetNameVal[13];
  flashData[133] = presetNameVal[14];
  flashData[134] = presetNameVal[15];

  // byte noiseLevel;
  // uint16_t aftertouch;

  for (int i = 0; i < flashPresetSize; i++) {
    presetBank1Buffer[i + startByteN] = flashData[i];
  }

  fileBank1 = LittleFS.open("presetBank1", "r+");
  fileBank1.seek(startByteN);
  fileBank1.write(flashData, flashPresetSize);
  fileBank1.close();

  presetSaveSelectMode = false;
  presetSaveMode = false;

  currentPreset = presetN;
  presetSelectVal = currentPreset;

  for (int i = 0; i < 12; i++) {
    presetName[i] = presetNameVal[i];
  }
  set_LED_Status(16, 0);

}

void writePresetActions(uint16_t presetN) {

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  PWMPotsControlManual = false;
  VCAPotsControlManual = false;
  ADSR3Enabled = false;

  presetSaveSelectMode = false;
  presetSaveMode = false;

  currentPreset = presetN;
  presetSelectVal = currentPreset;

  set_LED_Status(16, 0);
}

void loadPresetActions(uint16_t presetN) {

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;
  ADSR3Enabled = false;

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}