#ifndef SERIAL_INPUT_PROTOCOL_H
#define SERIAL_INPUT_PROTOCOL_H

#include <stdint.h>

// -----------------------------------------------------------------------------
// Serial8 input protocol: command byte definitions and payload sizes.
//
// This describes the protocol used between the INPUT BOARD MCU and the
// MAINBOARD over Serial8. All frames have the form:
//
//   [1 byte] command character
//   [N bytes] payload (length depends on command, defined below)
//
// The mainboard uses serial_parser.h and this header to parse incoming frames.
// The input board firmware can include this file to ensure it sends frames
// with the same command bytes and payload sizes.
// -----------------------------------------------------------------------------

// Command bytes sent BY the input board TO the mainboard on Serial8.
//
//   'a' : ADSR1 block
//   'b' : ADSR2 block
//   'c' : ADSR3 block
//   'd' : filter block
//   'e' : ADSR1->VCA amount
//   'f' : PWM value
//   'p' : PARAM 16-bit (ParamId + int16 + finish)
//   'w' : PARAM 8-bit  (ParamId + int8  + finish)
//   'q' : preset name (8 chars + finish byte)
//
// NOTE: 'p'/'w' use the same layouts and semantics as the shared
// serial_param_protocol.h helpers for 'p'/'w' on other links.
enum InputSerialCmd : char {
  INPUT_CMD_ADSR1_BLOCK     = 'a',
  INPUT_CMD_ADSR2_BLOCK     = 'b',
  INPUT_CMD_ADSR3_BLOCK     = 'c',
  INPUT_CMD_FILTER_BLOCK    = 'd',
  INPUT_CMD_ADSR1_TO_VCA    = 'e',
  INPUT_CMD_PW_VALUE        = 'f',
  INPUT_CMD_PARAM_16        = 'p',
  INPUT_CMD_PARAM_8         = 'w',
  INPUT_CMD_PRESET_NAME     = 'q',
};

// Payload sizes (NOT counting the command byte itself).
//
// ADSR1/2/3 blocks ('a','b','c'):
//   payload[0..1] = attack   (input-board mapped, big-endian)
//   payload[2..3] = decay    (input-board mapped, big-endian)
//   payload[4..5] = sustain  (big-endian)
//   payload[6..7] = release  (input-board mapped, big-endian)
static constexpr uint8_t INPUT_SERIAL_LEN_ADSR_BLOCK   = 8;

// Filter block ('d'):
//   payload[0..1] = CUTOFF   (big-endian)
//   payload[2..3] = RESONANCE(big-endian)
//   payload[4..5] = ADSR2toVCF (big-endian)
//   payload[6..7] = LFO2toVCF  (big-endian)
static constexpr uint8_t INPUT_SERIAL_LEN_FILTER_BLOCK = 8;

// ADSR1->VCA amount ('e'):
//   payload[0..1] = ADSR1toVCA (big-endian)
static constexpr uint8_t INPUT_SERIAL_LEN_ADSR1_TO_VCA = 2;

// PWM value ('f'):
//   payload[0..1] = PW (big-endian)
static constexpr uint8_t INPUT_SERIAL_LEN_PW_VALUE     = 2;

// PARAM 16-bit ('p'):
//   payload[0]   = paramNumber (ParamId)
//   payload[1..2]= int16 value (big-endian)
//   payload[3]   = finish byte (usually 1)
static constexpr uint8_t INPUT_SERIAL_LEN_PARAM_16     = 4;

// PARAM 8-bit ('w'):
//   payload[0]   = paramNumber (ParamId)
//   payload[1]   = int8 value (will be sign-extended)
//   payload[2]   = finish byte (usually 1)
static constexpr uint8_t INPUT_SERIAL_LEN_PARAM_8      = 3;

// Preset name ('q'):
//   payload[0..7]= 8 ASCII chars of preset name
//   payload[8]   = finish byte (usually 1)
static constexpr uint8_t INPUT_SERIAL_LEN_PRESET_NAME  = 9;

// Optional helper: return payload length for an input command.
static inline uint8_t input_serial_payload_len(char cmd) {
  switch (cmd) {
    case INPUT_CMD_ADSR1_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_ADSR2_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_ADSR3_BLOCK:   return INPUT_SERIAL_LEN_ADSR_BLOCK;
    case INPUT_CMD_FILTER_BLOCK:  return INPUT_SERIAL_LEN_FILTER_BLOCK;
    case INPUT_CMD_ADSR1_TO_VCA:  return INPUT_SERIAL_LEN_ADSR1_TO_VCA;
    case INPUT_CMD_PW_VALUE:      return INPUT_SERIAL_LEN_PW_VALUE;
    case INPUT_CMD_PARAM_16:      return INPUT_SERIAL_LEN_PARAM_16;
    case INPUT_CMD_PARAM_8:       return INPUT_SERIAL_LEN_PARAM_8;
    case INPUT_CMD_PRESET_NAME:   return INPUT_SERIAL_LEN_PRESET_NAME;
    default:                      return 0;
  }
}

#endif // SERIAL_INPUT_PROTOCOL_H



