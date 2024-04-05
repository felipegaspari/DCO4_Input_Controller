#ifndef __BUTTONS_H__
#define __BUTTONS_H__

#define NUM_BUTTONS 16

enum ButtonState {
  BTN_STATE_NONE,
  RELEASED,
  PRESSED,
  HELD,
  DOUBLE
};

enum ButtonAction {
  BTN_ACTION_NONE,

  TG_SAW1,
  TG_SAW2,
  TG_TRI,
  TG_SIN,
  TG_SQR1,
  TG_SQR2,

  TG_RESO_AMP_COMP,
  TG_ADSR1_RESTART,
  TG_ADSR2_RESTART,
  TG_ADSR3_TO_OSC_SELECT,
  TG_VOICE_MODE,

  SELECT_LFO_N,
  TG_LFO1_WAVE,
  TG_LFO2_WAVE,

  TG_FUNC,

  WORK_WITH_PRESETS,
  PRESET_SAVE_MODE,
  SAVE_PRESET,

  TG_MAN_FADERS,
  TG_MAN_POTS,
  TG_MAN_FADER_ROW1,
  TG_MAN_FADER_ROW2,
  TG_MANUAL_VCF_POTS,
  TG_MANUAL_VCA_POTS,
  TG_MANUAL_PWM_POTS,
  TG_MANUAL_ALL,
  TG_ENABLE_ADSR3,

  SELECT_ENC_ACTION,
};

struct ButtonStruct {
  RoxButton button_n;
  uint8_t pin; //pin or mux array position
  ButtonAction actionReleased;
  ButtonAction actionPressed;
  ButtonAction actionHeld;
  ButtonAction actionDouble;
  ButtonAction actionReleasedAlt;
  ButtonAction actionPressedAlt;
  ButtonAction actionHeldAlt;
  ButtonAction actionDoubleAlt;
  uint8_t encoderActionModifierN;
  uint8_t encoderActionModifierAltN;
};

ButtonStruct buttons[NUM_BUTTONS] = {
  { button1,  15, TG_SAW1,              BTN_ACTION_NONE, TG_FUNC,             BTN_ACTION_NONE, /* ALT: */ TG_ADSR3_TO_OSC_SELECT,   BTN_ACTION_NONE, TG_FUNC,         BTN_ACTION_NONE, 0, 0 },
  { button2,  12, TG_TRI,               BTN_ACTION_NONE, TG_MANUAL_ALL,       BTN_ACTION_NONE, /* ALT: */ TG_RESO_AMP_COMP,         BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button3,   9, TG_SIN,               BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ TG_ADSR1_RESTART,         BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button4,   6, TG_SQR1,              BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ TG_ADSR2_RESTART,         BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button5,   3, TG_SAW2,              BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ TG_VOICE_MODE,            BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button6,   0, TG_SQR2,              BTN_ACTION_NONE, SELECT_ENC_ACTION,   BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button7,  29, BTN_ACTION_NONE,      BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button8,  26, TG_LFO1_WAVE,         BTN_ACTION_NONE, SELECT_ENC_ACTION,   BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, TG_ENABLE_ADSR3, BTN_ACTION_NONE, 0, 0 },
  { button9,  23, TG_LFO2_WAVE,         BTN_ACTION_NONE, TG_FUNC,             BTN_ACTION_NONE, /* ALT: */ PRESET_SAVE_MODE,         BTN_ACTION_NONE, SAVE_PRESET,     BTN_ACTION_NONE, 0, 0 },
  { button10, 16, SELECT_ENC_ACTION,    BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ SELECT_ENC_ACTION,        BTN_ACTION_NONE, TG_MAN_FADERS,   BTN_ACTION_NONE, 0, 0 },
  { button11, 20, SELECT_ENC_ACTION,    BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ SELECT_ENC_ACTION,        BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button12, 43, TG_MANUAL_VCF_POTS,   BTN_ACTION_NONE, TG_MAN_POTS,         BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button13, 44, TG_MANUAL_VCA_POTS,   BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button14, 45, TG_MANUAL_PWM_POTS,   BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ BTN_ACTION_NONE,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
  { button15, 46, TG_MAN_FADER_ROW2,    BTN_ACTION_NONE, TG_ENABLE_ADSR3,     BTN_ACTION_NONE, /* ALT: */ TG_MAN_FADER_ROW2,          BTN_ACTION_NONE, TG_ENABLE_ADSR3, BTN_ACTION_NONE, 0, 0 },
  { button16, 47, TG_MAN_FADER_ROW1,    BTN_ACTION_NONE, BTN_ACTION_NONE,     BTN_ACTION_NONE, /* ALT: */ TG_MAN_FADER_ROW1,          BTN_ACTION_NONE, BTN_ACTION_NONE, BTN_ACTION_NONE, 0, 0 },
};

#endif