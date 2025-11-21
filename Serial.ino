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


void serial_send_param_change(byte param, uint16_t paramValue, bool sendToAll) {
  byte bytesArray[5] = { (uint8_t)'p', param, highByte(paramValue), lowByte(paramValue), finishByte };
#ifdef ENABLE_SERIAL1
  if (sendToAll) {
    Serial1.write(bytesArray, 5);
  }
#endif
#ifdef ENABLE_SERIAL2
  if (paramValue != -1) {  // paramValue 100 = send to screen only
    Serial2.write(bytesArray, 5);
  }
#endif
}

void serial_send_param_change_byte(byte param, byte paramValue, bool sendToAll) {
  byte bytesArrayByte[4] = { (uint8_t)'w', param, paramValue, finishByte };
#ifdef ENABLE_SERIAL1
  if (sendToAll) {
    Serial1.write(bytesArrayByte, 4);
  }
#endif
#ifdef ENABLE_SERIAL2
  if (paramValue != -1) {  // paramValue 100 = send to screen only
    Serial2.write(bytesArrayByte, 4);
  }
#endif
}

void serial_send_preset_name_to_mainboard() {
  Serial2.write((char *)"q");
  // Mainboard-side 'q' (input link) expects 8 chars; send first 8 only.
  Serial2.write(presetNameVal, 8);
  Serial2.write(finishByte);
}

void serial_send_preset_scroll(byte presetNumber, byte presetNameSerial[]) {

#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"q");

  Serial1.write(presetNumber);
  // Screen-side 'q' uses 16-character names.
  Serial1.write(presetNameSerial, 16);
  Serial1.write(finishByte);
#endif
}

void serial_send_save_char_select(byte serialPresetChar) {
#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"c");

  Serial1.write(serialPresetChar);
#endif
}

void serialSendParamByteToScreen(byte paramNumber, byte paramValue)
{
 while(Serial1.availableForWrite() < 1) {};
  byte bytesArray[4] = {(uint8_t)'y', paramNumber, paramValue, finishByte};
  Serial1.write(bytesArray, 4);
}

// ---------------------------------------------------------------------------
// Parser-based receiver for mainboard/DCO frames on Serial1
// ---------------------------------------------------------------------------

// Handle 32-bit PARAM ('x') from the mainboard/DCO path.
// Used here only for PARAM_MANUAL_CALIBRATION_OFFSET_FROM_DCO (155):
//   value (uint32) lower 16 bits = [oscIndex:8 | offset:8]
static void input_handle_param32_from_mainboard(char, const uint8_t* payload, uint8_t len) {
  if (len != SERIAL_PAYLOAD_LEN_PARAM_32) {
    return;
  }

  ParamFrame frame;
  decode_param_x(payload, frame);

  if (frame.id != (uint8_t)PARAM_MANUAL_CALIBRATION_OFFSET_FROM_DCO) {
    return;
  }

  uint16_t packed  = (uint16_t)frame.value;
  uint8_t  oscIndex = (uint8_t)(packed >> 8);
  int8_t   offset   = (int8_t)(packed & 0xFF);

  // Serial.print("[IN] RX PARAM32 id=155 idx=");
  // Serial.print((int)oscIndex);
  // Serial.print(" offset=");
  // Serial.println((int)offset);

  if (oscIndex < NUM_OSCILLATORS) {
    manualCalibrationInitAmpCompOffset[oscIndex] = offset;
    // If we are currently in manual calibration and this oscillator
    // matches the selected stage, push the freshly loaded offset to
    // the screen so the initial value reflects the DCO's stored one.
    if (manualCalibration) {
      uint8_t currentIndex = (uint8_t)manualCalibrationStage / 2;
      if (oscIndex == currentIndex) {
        serialSendParamByteToScreen(
          ParamId::PARAM_MANUAL_CALIBRATION_OFFSET,
          (uint8_t)manualCalibrationInitAmpCompOffset[currentIndex]
        );
      }
    }
  }
}

// Command table and parser context for Serial1 (mainboard->input link).
static const SerialCommandDef mainboardSerial1Commands[] = {
  { SERIAL_CMD_PARAM_32, SERIAL_PAYLOAD_LEN_PARAM_32, input_handle_param32_from_mainboard },
};

static SerialParserContext mainboardSerial1Parser = {
  SERIAL_WAIT_FOR_CMD,
  0,
  {0},
  0,
  0,
  0
};

void serial_read_from_mainboard() {
#ifdef ENABLE_SERIAL1
  // Expire any stale partial frame (only if we're in a frame).
  if (mainboardSerial1Parser.state == SERIAL_READ_PAYLOAD) {
    uint32_t now = micros();
    serial_parser_check_timeout(mainboardSerial1Parser, now);
  }

  // Consume all available bytes without blocking.
  if (Serial1.available() > 0) {
    uint32_t now = micros();  // one timestamp per batch is enough
    while (Serial1.available() > 0) {
      uint8_t b = Serial1.read();
      serial_parser_process_byte(
        mainboardSerial1Parser,
        mainboardSerial1Commands,
        sizeof(mainboardSerial1Commands) / sizeof(mainboardSerial1Commands[0]),
        b,
        now
      );
    }
  }
#endif
}
