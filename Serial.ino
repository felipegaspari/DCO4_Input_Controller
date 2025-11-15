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


void serial_send_param_change(ParamId param, int16_t paramValue, bool sendToAll) {
  byte bytesArray[5] = {
    (uint8_t)SERIAL_CMD_PARAM_16,
    (uint8_t)param,
    highByte((uint16_t)paramValue),
    lowByte((uint16_t)paramValue),
    finishByte
  };
#ifdef ENABLE_SERIAL1
  if (sendToAll) {
    Serial1.write(bytesArray, 5);
  }
#endif
#ifdef ENABLE_SERIAL2
  if (paramValue != -1) {  // paramValue -1 = send to screen only
    Serial2.write(bytesArray, 5);
  }
#endif
}

void serial_send_param_change_byte(ParamId param, int8_t paramValue, bool sendToAll) {
  byte bytesArrayByte[4] = {
    (uint8_t)SERIAL_CMD_PARAM_8,
    (uint8_t)param,
    (uint8_t)paramValue,
    finishByte
  };
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

  Serial2.write(presetNameVal, 12);

  Serial2.write(finishByte);
}

void serial_send_preset_scroll(byte presetNumber, byte presetNameSerial[]) {

#ifdef ENABLE_SERIAL1

  Serial1.write((char *)"q");

  Serial1.write(presetNumber);

  Serial1.write(presetNameSerial, 12);

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

// -------------------------------
// Serial2 parser (non-blocking, shared core)
// -------------------------------
//
// This section wires the generic serial_parser.h core to the Input
// Controller's Serial2 link. The Input Controller receives from the
// mainboard/DCO:
//
//   'a' : ADSR1 block (8 bytes)
//   'b' : ADSR2 block (8 bytes)
//   'c' : ADSR3 block (8 bytes)
//   'd' : filter block (8 bytes)
//   'e' : ADSR1->VCA amount (2 bytes)
//   'f' : PWM value (2 bytes)
//   'n' : NOTE ON  [voice, velocity, note]
//   'o' : NOTE OFF [voice]
//   'g' : float frequency (4 bytes, raw IEEE-754)
//
// The parser core is shared; only the handlers below are input-board specific.

// Local payload sizes (not counting command byte).
static constexpr uint8_t INPUT_RX_LEN_ADSR_BLOCK   = 8;
static constexpr uint8_t INPUT_RX_LEN_FILTER       = 8;
static constexpr uint8_t INPUT_RX_LEN_ADSR1_TO_VCA = 2;
static constexpr uint8_t INPUT_RX_LEN_PW           = 2;
static constexpr uint8_t INPUT_RX_LEN_NOTE_ON      = 3;
static constexpr uint8_t INPUT_RX_LEN_NOTE_OFF     = 1;
static constexpr uint8_t INPUT_RX_LEN_FREQ_FLOAT   = 4;

// ADSR1 block ('a')
static void input_rx_handle_adsr1(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_ADSR_BLOCK) return;
  ADSR1_attack  = word(payload[0], payload[1]);
  ADSR1_decay   = word(payload[2], payload[3]);
  ADSR1_sustain = word(payload[4], payload[5]);
  ADSR1_release = word(payload[6], payload[7]);
}

// ADSR2 block ('b')
static void input_rx_handle_adsr2(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_ADSR_BLOCK) return;
  ADSR2_attack  = word(payload[0], payload[1]);
  ADSR2_decay   = word(payload[2], payload[3]);
  ADSR2_sustain = word(payload[4], payload[5]);
  ADSR2_release = word(payload[6], payload[7]);
}

// ADSR3 block ('c')
static void input_rx_handle_adsr3(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_ADSR_BLOCK) return;
  ADSR3_attack  = word(payload[0], payload[1]);
  ADSR3_decay   = word(payload[2], payload[3]);
  ADSR3_sustain = word(payload[4], payload[5]);
  ADSR3_release = word(payload[6], payload[7]);
}

// Filter block ('d')
static void input_rx_handle_filter(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_FILTER) return;
  CUTOFF     = word(payload[0], payload[1]);
  RESONANCE  = word(payload[2], payload[3]);
  ADSR2toVCF = word(payload[4], payload[5]);
  LFO2toVCF  = word(payload[6], payload[7]);
}

// ADSR1->VCA amount ('e')
static void input_rx_handle_adsr1_to_vca(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_ADSR1_TO_VCA) return;
  ADSR1toVCA = word(payload[0], payload[1]);
}

// PWM value ('f')
static void input_rx_handle_pw(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_PW) return;
  PW = word(payload[0], payload[1]);
}

// NOTE ON ('n')
static void input_rx_handle_note_on(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_NOTE_ON) return;
  uint8_t voice_n   = payload[0];
  velocity[voice_n] = payload[1];
  note[voice_n]     = payload[2];
  noteStart[voice_n]= 1;
  noteEnd[voice_n]  = 0;
}

// NOTE OFF ('o')
static void input_rx_handle_note_off(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_NOTE_OFF) return;
  uint8_t voice_n = payload[0];
  noteEnd[voice_n]   = 1;
  noteStart[voice_n] = 0;
}

// Float frequency ('g')
static void input_rx_handle_freq(char, const uint8_t* payload, uint8_t len) {
  if (len != INPUT_RX_LEN_FREQ_FLOAT) return;
  float a;
  ((uint8_t*)&a)[0] = payload[0];
  ((uint8_t*)&a)[1] = payload[1];
  ((uint8_t*)&a)[2] = payload[2];
  ((uint8_t*)&a)[3] = payload[3];
  freq = a;
}

// Command table for Serial2 on the Input Controller.
static const SerialCommandDef inputSerial2Commands[] = {
  { 'a', INPUT_RX_LEN_ADSR_BLOCK,   input_rx_handle_adsr1        },
  { 'b', INPUT_RX_LEN_ADSR_BLOCK,   input_rx_handle_adsr2        },
  { 'c', INPUT_RX_LEN_ADSR_BLOCK,   input_rx_handle_adsr3        },
  { 'd', INPUT_RX_LEN_FILTER,       input_rx_handle_filter       },
  { 'e', INPUT_RX_LEN_ADSR1_TO_VCA, input_rx_handle_adsr1_to_vca },
  { 'f', INPUT_RX_LEN_PW,           input_rx_handle_pw           },
  { 'n', INPUT_RX_LEN_NOTE_ON,      input_rx_handle_note_on      },
  { 'o', INPUT_RX_LEN_NOTE_OFF,     input_rx_handle_note_off     },
  { 'g', INPUT_RX_LEN_FREQ_FLOAT,   input_rx_handle_freq         },
};

static SerialParserContext inputSerial2Parser = {
  SERIAL_WAIT_FOR_CMD,
  0,
  {0},
  0,
  0,
  0
};

void serial_read_n() {
#ifdef ENABLE_SERIAL2
  // Expire any stale partial frame first.
  uint32_t now = micros();
  serial_parser_check_timeout(inputSerial2Parser, now);

  // Consume all available bytes without blocking.
  while (Serial2.available() > 0) {
    uint8_t b = Serial2.read();
    now = micros();
    serial_parser_process_byte(
      inputSerial2Parser,
      inputSerial2Commands,
      sizeof(inputSerial2Commands) / sizeof(inputSerial2Commands[0]),
      b,
      now
    );
  }
#endif
}
