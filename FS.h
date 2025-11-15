#ifndef __FS_H__
#define __FS_H__

#include <stdint.h>
#include "LittleFS.h"

static constexpr uint8_t flashPresetSize        = 140;
static constexpr int     flashBankSize         = flashPresetSize * 512;
static constexpr uint16_t NUM_PRESETS          = flashBankSize / flashPresetSize;
static constexpr uint8_t PRESET_FORMAT_VERSION = 1;

byte flashData[flashPresetSize];
byte presetBank1Buffer[flashBankSize];

File fileBank1;

#endif