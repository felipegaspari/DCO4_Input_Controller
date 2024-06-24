#ifndef __FS_H__
#define __FS_H__

#include "LittleFS.h"

static const uint8_t flashPresetSize = 140;
static const int flashBankSize = flashPresetSize * 512;

byte flashData[flashPresetSize];
byte presetBank1Buffer[flashBankSize];

File fileBank1;

#endif