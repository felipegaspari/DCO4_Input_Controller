void initFS()
{
  LittleFS.begin();

  if (!LittleFS.exists("presetBank1"))
  {
    fileBank1 = LittleFS.open("presetBank1", "w+");
  }
  else
  {
    fileBank1 = LittleFS.open("presetBank1", "r");
  }

  fileBank1.read(presetBank1Buffer, flashBankSize);
  fileBank1.close();

  for (int i = 0; i < flashPresetSize; i++)
  {
    flashData[i] = presetBank1Buffer[i];
  }

  loadPreset(1);
}

void load_preset_name(byte destinationPreset)
{

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

void loadPreset(uint16_t presetN)
{

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

  for (int i = 0; i < flashPresetSize; i++)
  {
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
  PWMPotsControlManual = bitRead(flashData[1], 1); // makes no sense, should be off after loading or writing presets
  ADSR3Enabled = bitRead(flashData[1], 2);
  unused_data = bitRead(flashData[1], 3);
  unused_data = bitRead(flashData[1], 4);
  unused_data = bitRead(flashData[1], 5);
  unused_data = bitRead(flashData[1], 6);
  unused_data = bitRead(flashData[1], 7);

  unused_data = flashData[2];
  unused_data = flashData[3];
  unused_data = flashData[4];
  unused_data = flashData[5];

  // bytes
  LFO1Waveform = flashData[6];
  LFO2Waveform = flashData[7];
  OSC1Interval = flashData[8];
  OSC2Interval = flashData[9];
  oscSyncMode = flashData[10];
  portamentoTime = flashData[11];
  voiceMode = flashData[12];

  // int8_t
  ADSR3ToOscSelect = flashData[13];
  velocityToVCFVal = flashData[14];
  velocityToVCAVal = flashData[15];

  unisonDetune = flashData[16];
  ADSR1AttackCurveVal = flashData[17];
  ADSR1DecayCurveVal = flashData[18];
  ADSR2AttackCurveVal = flashData[19];
  ADSR2DecayCurveVal = flashData[20];
  unused_data = flashData[21];
  unused_data = flashData[22];
  unused_data = flashData[23];
  unused_data = flashData[24];
  unused_data = flashData[25];
  unused_data = flashData[26];
  unused_data = flashData[27];
  unused_data = flashData[28];
  unused_data = flashData[29];

  // int16_t
  VCFKeytrack = word(flashData[30], flashData[31]);
  SQR1LevelVal = word(flashData[32], flashData[33]);
  SQR2LevelVal = word(flashData[34], flashData[35]);
  SubLevelVal = word(flashData[36], flashData[37]);
  unused_data_uint16_t = word(flashData[38], flashData[39]);
  LFO1toDCOVal = word(flashData[40], flashData[41]);
  LFO1SpeedVal = word(flashData[42], flashData[43]);
  LFO2SpeedVal = word(flashData[44], flashData[45]);
  ADSR3toPWM = word(flashData[46], flashData[47]);
  ADSR3toDETUNE1 = word(flashData[48], flashData[49]);

  unused_data_uint16_t = word(flashData[50], flashData[51]);
  unused_data_uint16_t = word(flashData[52], flashData[53]);
  unused_data_uint16_t = word(flashData[54], flashData[55]);
  unused_data_uint16_t = word(flashData[56], flashData[57]);
  unused_data_uint16_t = word(flashData[58], flashData[59]);
  unused_data_uint16_t = word(flashData[60], flashData[61]);

  // uint16_t
  OSC2Detune = word(flashData[62], flashData[63]);
  LFO2toOSC2DETUNE = word(flashData[64], flashData[65]);
  VCALevel = word(flashData[66], flashData[67]);
  LFO1toVCA = word(flashData[68], flashData[69]);
  LFO2toPWM = word(flashData[70], flashData[71]);

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

  presetName[0] = flashData[119];
  presetName[1] = flashData[120];
  presetName[2] = flashData[121];
  presetName[3] = flashData[122];
  presetName[4] = flashData[123];
  presetName[5] = flashData[124];
  presetName[6] = flashData[125];
  presetName[7] = flashData[126];
  presetName[8] = flashData[127];
  presetName[9] = flashData[128];
  presetName[10] = flashData[129];
  presetName[11] = flashData[130];

  /**********************************************************************************/
  /////////////////// START NEW STUFF //

  serial_send_param_change_byte(124, 0, false); // PWM control Manual off after loading
  serial_send_param_change_byte(126, 0, false); // ADSR3Enabled OFF

  serial_send_param_change_byte(1, sawStatus, false);
  serial_send_param_change_byte(2, saw2Status, false);
  serial_send_param_change_byte(3, triStatus, false);
  serial_send_param_change_byte(4, sineStatus, false);
  serial_send_param_change_byte(5, sqr1Status, false);
  serial_send_param_change_byte(6, sqr2Status, false);
  
  update_LED_Control(16, 1);

delay(1);

  serial_send_param_change_byte(7, RESONANCEAmpCompensation, false);
  serial_send_param_change_byte(8, VCAADSRRestart, false);
  serial_send_param_change_byte(9, VCFADSRRestart, false);
  serial_send_param_change_byte(10, ADSR3ToOscSelect, false);

  // LFO1Waveform
  serial_send_param_change_byte(11, LFO1Waveform, false);
  // LFO2Waveform
  serial_send_param_change_byte(12, LFO2Waveform, false);

  serial_send_param_change_byte(13, OSC1Interval, false);
  serial_send_param_change_byte(14, OSC2Interval, false);

  serial_send_param_change_byte(17, oscSyncMode, false);

  serial_send_param_change_byte(18, portamentoTime, false);

  serial_send_param_change_byte(26, voiceMode, false);
delay(1);
  serial_send_param_change_byte(10, ADSR3ToOscSelect, false);

  serial_send_param_change_byte(20, velocityToVCFVal, false);
  serial_send_param_change_byte(21, velocityToVCAVal, false);

  serial_send_param_change_byte(22, SQR1LevelVal, false);
  serial_send_param_change_byte(23, SQR2LevelVal, false);
  serial_send_param_change_byte(24, SubLevelVal, false);

  serial_send_param_change_byte(27, unisonDetune, false); //  unisonDetune

  serial_send_param_change_byte(48, ADSR1AttackCurveVal, false);
  serial_send_param_change_byte(49, ADSR1DecayCurveVal, false);
  serial_send_param_change_byte(50, ADSR2AttackCurveVal, false);
  serial_send_param_change_byte(51, ADSR2DecayCurveVal, false);
delay(1);
  serial_send_param_change(40, LFO1toDCOVal, false); // LFO1toDCOVal  

  serial_send_param_change(41, LFO1SpeedVal, false); // LFO1SpeedVal  

  serial_send_param_change(42, LFO2SpeedVal, false); // LFO2SpeedVal 

  serial_send_param_change(43, VCALevel, false);

  serial_send_param_change(44, LFO1toVCA, false);

  serial_send_param_change(45, LFO2toPWM, false); // LFO2toPWM

  serial_send_param_change(46, ADSR3toPWM + 512, false); // ADSR3toPWM

  serial_send_param_change(47, ADSR3toDETUNE1, false); // ADSR3toDETUNE1

  serial_send_param_change(15, OSC2Detune, false); // OSC2Detune

  serial_send_param_change(16, LFO2toOSC2DETUNE, false); // LFO2toOSC2DETUNE
delay(1);
  serial_send_manual_controls(true); // includes:
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

  serial_send_preset_scroll(currentPreset, presetName);
}

void get_preset_name(byte presetN, byte (&myarray)[12])
{
  uint16_t startByteN = presetN * flashPresetSize;
  for (int i = 0; i < 12; i++)
  {
    myarray[i] = presetBank1Buffer[startByteN + 119 + i];
  }
}

void writePreset(uint16_t presetN)
{

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  VCAPotsControlManual = false;
  PWMPotsControlManual = false;
  ADSR3Enabled = false;
  
  uint16_t startByteN = presetN * flashPresetSize;
  byte *b;

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
  // bytes
  flashData[6] = LFO1Waveform;
  flashData[7] = LFO2Waveform;
  flashData[8] = OSC1Interval;
  flashData[9] = OSC2Interval;
  flashData[10] = oscSyncMode;
  flashData[11] = portamentoTime;
  flashData[12] = voiceMode;
  // int8_t
  flashData[13] = (byte)ADSR3ToOscSelect;
  flashData[14] = (byte)velocityToVCFVal;
  flashData[15] = (byte)velocityToVCAVal;
  flashData[16] = (byte)unisonDetune;
  flashData[17] = ADSR1AttackCurveVal;
  flashData[18] = ADSR1DecayCurveVal;
  flashData[19] = ADSR2AttackCurveVal;
  flashData[20] = ADSR2DecayCurveVal;
  flashData[21] = 0;
  flashData[22] = 0;
  flashData[23] = 0;
  flashData[24] = 0;
  flashData[25] = 0;
  flashData[26] = 0;
  flashData[27] = 0;
  flashData[28] = 0;
  flashData[29] = 0;
  // int16_t
  flashData[30] = highByte(VCFKeytrack);
  flashData[31] = lowByte(VCFKeytrack);
  flashData[32] = highByte(SQR1LevelVal);
  flashData[33] = lowByte(SQR1LevelVal);
  flashData[34] = highByte(SQR2LevelVal);
  flashData[35] = lowByte(SQR2LevelVal);
  flashData[36] = highByte(SubLevelVal);
  flashData[37] = lowByte(SubLevelVal);
  flashData[38] = highByte(0);
  flashData[39] = lowByte(0);
  flashData[40] = highByte(LFO1toDCOVal);
  flashData[41] = lowByte(LFO1toDCOVal);
  flashData[42] = highByte(LFO1SpeedVal);
  flashData[43] = lowByte(LFO1SpeedVal);
  flashData[44] = highByte(LFO2SpeedVal);
  flashData[45] = lowByte(LFO2SpeedVal);
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

  // byte noiseLevel;
  // uint16_t aftertouch;

  for (int i = 0; i < flashPresetSize; i++)
  {
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

  for (int i = 0; i > 12; i++) {
    presetName[i] = presetNameVal[i];
  }

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