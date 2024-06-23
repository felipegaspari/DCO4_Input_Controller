void init_controls() {
  analogReadResolution(12);

  enc1.begin();
  enc2.begin();
  enc3.begin();
  enc4.begin();
  enc5.begin();
  enc6.begin();
  enc7.begin();
  enc8.begin();
  enc9.begin();
  enc10.begin();
  enc11.begin();

  pinMode(digitalMUX1_PIN_SIG0, INPUT);
  pinMode(digitalMUX2_PIN_SIG0, INPUT);
  pinMode(digitalMUX3_PIN_SIG0, INPUT);

  pinMode(muxAnalog_PIN_CH0, OUTPUT);
  pinMode(muxAnalog_PIN_CH1, OUTPUT);
  pinMode(muxAnalog_PIN_CH2, OUTPUT);
  pinMode(muxAnalog_PIN_CH3, OUTPUT);

  pinMode(muxAnalog_PIN_SIG, INPUT);
}

void readControls() {

  if (timer1msFlag) {
    read_digitalMux(1);
    read_AnalogMux();
  } else {
    read_digitalMux(0);
  }

  if (timer99microsFlag) {
    // if (!presetSaved) {           /// OLD METHOD FOR SAVING PRESETS
    //   read_encoders_preset_save();
    //   read_encoder_buttons_preset_save();
    // } else {
    read_encoders();
    read_encoder_buttons();
  }
}

void setControlValues() {

  if (faderRow1ControlManual) {
    ADSR1_attack = faderExpConverter(analogMedian[fader1ArrayPos]);
    ADSR1_decay = faderExpConverter(analogMedian[fader2ArrayPos]);
    ADSR1_sustain = analogMedian[fader3ArrayPos];
    ADSR1_release = faderExpConverter(analogMedian[fader4ArrayPos]);
  }

  if (faderRow2ControlManual) {
    if (ADSR3Enabled) {
      ADSR3_attack = faderExpConverter(analogMedian[fader5ArrayPos]);
      ADSR3_decay = faderExpConverter(analogMedian[fader6ArrayPos]);
      ADSR3_sustain = analogMedian[fader7ArrayPos];
      ADSR3_release = faderExpConverter(analogMedian[fader8ArrayPos]);
    } else {
      ADSR2_attack = faderExpConverter(analogMedian[fader5ArrayPos]);
      ADSR2_decay = faderExpConverter(analogMedian[fader6ArrayPos]);
      ADSR2_sustain = analogMedian[fader7ArrayPos];
      ADSR2_release = faderExpConverter(analogMedian[fader8ArrayPos]);
    }
  }

  if (VCFPotsControlManual) {
    CUTOFF = 4095 - analogMedian[pot2ArrayPos];
    RESONANCE = analogMedian[pot3ArrayPos];
    //    ADSR2toVCF = muxAnalogData[5];
    //    LFO1toVCF = muxAnalogData[1];
    ADSR2toVCF = constrain((507 - (analogMedian[pot4ArrayPos] / 8)), 0, 512);
    LFO2toVCF = constrain((507 - (analogMedian[pot1ArrayPos] / 8)), 0, 512);
    //controls_formula_update(5);
  }
  // if (VCAPotsControlManual) {
  if (VCAPotsControlManual) {
    //ADSR1toVCA = constrain((507 - (analogMedian[6]/ 8)), 0, 4095);
    ADSR1toVCA = 512 - (analogMedian[pot5ArrayPos] / 8);
  }
  if (PWMPotsControlManual) {
    PW = analogMedian[pot6ArrayPos];
  }

  if (RESONANCEAmpCompensation) {
    if (RESONANCE <= 2100) {
      VCAResonanceCompensation = (float)RESONANCE / 2100 * 2.25;
    } else if (RESONANCE <= 3720) {
      VCAResonanceCompensation = ((float)constrain((3720 - RESONANCE), 0, 1200) / 960) + 1;
    } else {
      VCAResonanceCompensation = 1;
    }
  }
}

void read_AnalogMux() {

  for (uint8_t i = 0; i < 16; i++) {

    // muxAnalog.channel(i);
    // delayMicroseconds(2);
    // muxAnalogRaw[i] = analogRead(muxAnalog_PIN_SIG);

    if (muxAnalogRaw[i] > (((muxAnalogDataPrev[i] + analogMedian[i]) / 2) + 10)) {
      muxAnalogData[i] = (muxAnalogRaw[i] + analogMedian[i] + muxAnalogDataPrev[i] - 8) / 3;
    } else if (muxAnalogRaw[i] < (((muxAnalogDataPrev[i] + analogMedian[i]) / 2) - 10)) {
      muxAnalogData[i] = (muxAnalogRaw[i] + analogMedian[i] + muxAnalogDataPrev[i] + 8) / 3;
    }

    // muxAnalogDataPrev[i] = analogMedian[i];
    // muxAnalogDataPrev[i] = (muxAnalogRaw[i] + analogMedian[i]) / 2;
    muxAnalogDataPrev[i] = (muxAnalogData[i] + analogMedian[i]) / 2;
  }
  // for (uint8_t i = 0; i < 8; i++) {
  //   muxPotsRaw[i] = muxAnalog.read(i + 8);
  //   //        if ( muxPotsRaw[i] > (((muxAnalogDataPrev[i] + analogMedian[i]) / 2) + 10)) {
  //   //      muxAnalogData[i] = (muxPotsRaw[i] + analogMedian[i] - 8) / 2;
  //   //    } else if (muxPotsRaw[i] < (((muxAnalogDataPrev[i] + analogMedian[i]) / 2) - 10)) {
  //   //      muxAnalogData[i] = (muxPotsRaw[i] + analogMedian[i] + 8) / 2;
  //   //    }

  //   //    muxAnalogData[i] = muxPotsRaw[i];
  //   muxAnalogData[i] = (muxPotsRaw[i] + muxAnalogDataPrev[i] + analogMedian[i]) / 3;
  //   muxAnalogDataPrev[i] = (muxPotsRaw[i] + analogMedian[i]) / 2;
  // }
}

void read_digitalMux(bool readPots) {

  for (activeDigitalMuxChannel = 0; activeDigitalMuxChannel < 16; activeDigitalMuxChannel++) {

    muxDigital.channel(activeDigitalMuxChannel);
    delayMicroseconds(1);
    valorMUX1[activeDigitalMuxChannel] = digitalRead(digitalMUX1_PIN_SIG0);
    valorMUX1[activeDigitalMuxChannel + 16] = digitalRead(digitalMUX2_PIN_SIG0);
    valorMUX1[activeDigitalMuxChannel + 32] = digitalRead(digitalMUX3_PIN_SIG0);

    if (readPots) {
      muxAnalogRaw[activeDigitalMuxChannel] = analogRead(muxAnalog_PIN_SIG);
    }

    //activeDigitalMuxChannel++;
    //if (activeDigitalMuxChannel > 15) activeDigitalMuxChannel = 0;
  }
}

void read_encoders_preset_save() {
  byte x = enc5.read(valorMUX1[0], valorMUX1[1]);

  if (x) {
    if (x == DIR_CW) {
      charSelectVal = charSelectVal + (1 + (0.5 * enc5.speed()));
    } else {
      charSelectVal = charSelectVal - (1 + (0.5 * enc5.speed()));
    }
    charSelectVal = constrain(charSelectVal, 32, 255);
    presetNameVal[presetChar] = charSelectVal;
    serial_send_preset_scroll(presetSelectVal, presetNameVal);

    byte presetName4Chars[4];
    for (byte i = 0; i < 4; i++) {
      presetName4Chars[i] = presetNameVal[i];
    }
  }
}

void read_encoder_buttons_preset_save() {
  button5.update(valorMUX1[14], 50, LOW);
  if (button5.held()) {
    for (int i = 0; i < 13; i++) {
      presetName[i] = presetNameVal[i];
    }
    //writePreset(presetSelectVal);

    currentPreset = presetSelectVal;
    serial_send_signal(5);
    presetSaved = true;
    //  presetSave = false;
    presetChar = 0;
    charSelectVal = 0;
  } else if (button5.released(true)) {
    presetChar++;

    if (presetChar > 11) {
      presetChar = 0;
    }
    charSelectVal = presetNameVal[presetChar];
    serial_send_save_char_select(presetChar);
  }
}


uint16_t faderExpConverter(uint16_t readingValue) {
  uint16_t pow3Calc = readingValue / 4;
  uint16_t expValOut = pow3Calc * pow3Calc * pow3Calc / 20000;
  return expValOut;
}

float expConverterFloat(uint16_t readingValue, uint16_t curve) {
  uint16_t pow3Calc = readingValue;
  float expValOut = (float)pow3Calc * pow3Calc / curve;
  if (expValOut < 0.005) {
    expValOut = 0;
  }
  return expValOut;
}

uint16_t expConverter(uint16_t readingValue, uint16_t curve) {
  uint16_t pow3Calc = readingValue;
  uint16_t expValOut = (float)pow3Calc * pow3Calc / curve;
  if (expValOut < 0.1) {
    expValOut = 0;
  }
  return expValOut;
}

uint16_t expConverterReverse(uint16_t readingValue, uint16_t curve) {
  uint16_t expValOut = sqrt((float)readingValue / curve);
  return expValOut;
}

uint16_t expConverterFloatReverse(float readingValue, uint16_t curve) {
  uint16_t expValOut = sqrt(readingValue / curve);
  return expValOut;
}
