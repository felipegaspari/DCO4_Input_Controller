void writePresetActions(uint16_t presetN) {

  faderRow1ControlManual = false;
  faderRow2ControlManual = false;
  VCFPotsControlManual = false;
  PWMPotsControlManual = false;
  VCAPotsControlManual = false;

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

  currentPreset = presetN;
  presetSelectVal = currentPreset;
}
