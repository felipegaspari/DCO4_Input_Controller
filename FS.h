#ifndef __FS_H__
#define __FS_H__

  #include <stdint.h>
  #include "LittleFS.h"

  static constexpr uint16_t NUM_PRESETS    = 256;
  static constexpr uint16_t flashPresetSize = 140;
  static constexpr uint32_t flashBankSize   = (uint32_t)NUM_PRESETS * (uint32_t)flashPresetSize;

byte flashData[flashPresetSize];
byte presetBank1Buffer[flashBankSize];

File fileBank1;

#endif