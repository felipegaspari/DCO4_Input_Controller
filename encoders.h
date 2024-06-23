#ifndef __ENCODERS_H__
#define __ENCODERS_H__

enum EncoderAction {
  ACTION_NONE,

  ACTION_portamento_time,

  ACTION_LFO1_to_DCO,

  ACTION_VCF_keytrack,

  ACTION_velocity_to_VCF,
  ACTION_velocity_to_VCA,

  ACTION_SQR1_level,
  ACTION_SQR2_level,
  ACTION_SUB_level,

  ACTION_octave,
  ACTION_OSC2_interval,
  ACTION_OSC2_detune,
  ACTION_UNISON_DETUNE,
  
  ACTION_LFO2_to_OSC2_detune,

  ACTION_osc_sync_mode,

  ACTION_LFO1_speed,
  ACTION_LFO2_speed,

  ACTION_VCA_level,

  ACTION_LFO1_to_VCA,
  ACTION_LFO2_to_PWM,

  ACTION_ADSR3_to_PWM,
  ACTION_ADSR3_to_DETUNE1,
  ACTION_ADSR_CURVE_ATTACK,
  ACTION_ADSR_CURVE_DECAY,

  ACTION_select_preset,

  ACTION_select_char,

  ACTION_select_char_pos,
  
  ACTION_calibration
};

struct EncoderStruct {
  MD_REncoder MD_REncoder_Name;
  uint8_t muxPin1;
  uint8_t muxPin2;
  EncoderAction action1;
  EncoderAction action2;
  EncoderAction action3;
  EncoderAction actionAlt1;
  EncoderAction actionAlt2;
  EncoderAction actionAlt3;
};

EncoderStruct encoders[] = {
  { enc1, 13, 14, ACTION_LFO1_to_DCO,    ACTION_NONE,             ACTION_NONE,        ACTION_ADSR3_to_DETUNE1,             ACTION_NONE,                ACTION_NONE },
  { enc2, 10, 11, ACTION_osc_sync_mode,  ACTION_NONE,             ACTION_NONE,        ACTION_portamento_time,              ACTION_NONE,                ACTION_NONE },
  { enc3, 7, 8, ACTION_octave,           ACTION_NONE,             ACTION_NONE,        ACTION_OSC2_interval,                ACTION_NONE,         ACTION_ADSR_CURVE_ATTACK },
  { enc4, 4, 5, ACTION_SQR1_level,       ACTION_NONE,             ACTION_NONE,        ACTION_UNISON_DETUNE,                ACTION_NONE,         ACTION_ADSR_CURVE_DECAY },
  { enc5, 1, 2, ACTION_OSC2_detune,      ACTION_NONE,             ACTION_NONE,        ACTION_LFO2_to_OSC2_detune,          ACTION_NONE,                ACTION_NONE },
  { enc6, 30, 31, ACTION_SQR2_level,     ACTION_NONE,             ACTION_NONE,        ACTION_VCF_keytrack,                 ACTION_NONE,                ACTION_NONE },
  { enc7, 27, 28, ACTION_SUB_level,      ACTION_NONE,             ACTION_NONE,        ACTION_velocity_to_VCA,              ACTION_NONE,                ACTION_NONE },
  { enc8, 24, 25, ACTION_LFO1_speed,     ACTION_select_char,      ACTION_NONE,        ACTION_velocity_to_VCF,              ACTION_NONE,                ACTION_NONE },
  { enc9, 21, 22, ACTION_LFO2_speed,     ACTION_select_char_pos,  ACTION_NONE,        ACTION_select_preset,                ACTION_select_preset,       ACTION_NONE },
  { enc10, 42, 17, ACTION_LFO1_to_VCA,   ACTION_NONE,             ACTION_NONE,        ACTION_VCA_level,                    ACTION_NONE,                ACTION_NONE },
  { enc11, 18, 19, ACTION_LFO2_to_PWM,   ACTION_NONE,             ACTION_NONE,        ACTION_ADSR3_to_PWM,                 ACTION_NONE,                ACTION_NONE },
};

#endif