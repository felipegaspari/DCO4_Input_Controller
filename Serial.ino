void sendUint16(uint16_t f) {
  byte *b = (byte *)&f;

  Serial2.write((char *)"u");

  Serial2.write(b, 2);
}

void sendFloat(float f) {
  byte *b = (byte *)&f;

  Serial2.print("t");
  byte ndata = 0;
  for (int i = 0; i < 4; i++) {

    Serial2.write(b[i]);
  }
  return;
}

void sendOK() {

  Serial2.write((char *)"k");
  //Serial.println("Sent OK");
}

void serial_send_autotune() {
  byte autotune_on = 255;
  Serial2.write((char *)"a");
  Serial2.write(autotune_on);
  Serial2.flush();
  //Serial.println("Sent autotune on");
}

void serial_send_signal(byte signal) {
#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"s");

  Serial1.write(signal);
#endif
}

void serial_send_param_change(byte param, uint16_t paramValue) {
  byte bytesArray[5] = { (uint8_t)'p', param, highByte(paramValue), lowByte(paramValue), finishByte };
#ifdef ENABLE_SERIAL1

  Serial1.write(bytesArray, 5);
#endif
#ifdef ENABLE_SERIAL2

  Serial2.write(bytesArray, 5);
#endif
}

void serial_send_param_change_byte(byte param, byte paramValue) {
  byte bytesArray[4] = { (uint8_t)'w', param, paramValue, finishByte };
#ifdef ENABLE_SERIAL1

  Serial1.write(bytesArray, 4);
#endif
#ifdef ENABLE_SERIAL2

  Serial2.write(bytesArray, 4);
#endif
}

void serial_send_preset_name_to_mainboard(){

  Serial2.write((char *)"q");

  Serial2.write(presetNameVal, 8);

  Serial2.write(finishByte);
}

void serial_send_preset_scroll(byte presetNumber, byte presetNameSerial[]) {

#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"q");

  Serial1.write(presetNumber);

  Serial1.write(presetNameSerial, 8);

  Serial1.write(finishByte);
#endif
}

void serial_send_save_char_select(byte serialPresetChar) {
#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"c");

  Serial1.write(serialPresetChar);
#endif
}

void serial_read_n() {
  while (Serial2.available() > 0) {
    char commandCharacter = Serial2.read();
    switch (commandCharacter) {
      case 'a':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR1_attack = word(byteArray[0], byteArray[1]);
          ADSR1_decay = word(byteArray[2], byteArray[3]);
          ADSR1_sustain = word(byteArray[4], byteArray[5]);
          ADSR1_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'b':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR2_attack = word(byteArray[0], byteArray[1]);
          ADSR2_decay = word(byteArray[2], byteArray[3]);
          ADSR2_sustain = word(byteArray[4], byteArray[5]);
          ADSR2_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'c':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          ADSR3_attack = word(byteArray[0], byteArray[1]);
          ADSR3_decay = word(byteArray[2], byteArray[3]);
          ADSR3_sustain = word(byteArray[4], byteArray[5]);
          ADSR3_release = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'd':
        {
          byte byteArray[8];
          Serial2.readBytes(byteArray, 8);

          CUTOFF = word(byteArray[0], byteArray[1]);
          RESONANCE = word(byteArray[2], byteArray[3]);
          ADSR2toVCF = word(byteArray[4], byteArray[5]);
          LFO2toVCF = word(byteArray[6], byteArray[7]);
          break;
        }
      case 'e':
        {
          byte byteArray[2];
          Serial2.readBytes(byteArray, 2);

          ADSR1toVCA = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'f':
        {
          byte byteArray[2];
          Serial2.readBytes(byteArray, 2);

          PW = word(byteArray[0], byteArray[1]);
          break;
        }
      case 'n':
        {
          byte byteArray[3];

          Serial2.readBytes(byteArray, 3);

          byte voice_n = byteArray[0];
          velocity[voice_n] = byteArray[1];
          note[voice_n] = byteArray[2];

          noteStart[voice_n] = 1;
          noteEnd[voice_n] = 0;

          break;
        }
      case 'o':
        {
          byte voice_n;

          voice_n = Serial2.read();
          noteEnd[voice_n] = 1;
          noteStart[voice_n] = 0;

          break;
        }
      case 'g':
        {
          byte dataArray[4];

          byte ndata = 0;
          while (ndata < 4) {
            //for (byte ndata = 0; ndata < 122; ndata++)
            //if (Serial2.available() > 0) {

            dataArray[ndata] = Serial2.read();
            ndata++;
            //}
          }
          float a;
          ((uint8_t *)&a)[0] = dataArray[0];
          ((uint8_t *)&a)[1] = dataArray[1];
          ((uint8_t *)&a)[2] = dataArray[2];
          ((uint8_t *)&a)[3] = dataArray[3];

          freq = a;
          break;
        }
    }
  }
}
