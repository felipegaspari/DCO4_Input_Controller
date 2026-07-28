# Input Controller — presets (LittleFS)

Preset ownership for DCO4 lives on the **Input Controller** (not Mainboard `flashData`, which is inactive).

---

## Storage

| Item | Value |
|------|--------|
| FS | LittleFS |
| File | `"presetBank1"` |
| Presets | `NUM_PRESETS` = **256** |
| Slot size | `flashPresetSize` = **140** bytes |
| Bank size | 256 × 140 |
| RAM | Full bank in `presetBank1Buffer[]`; working slot in `flashData[140]` |

`initFS()` creates/extends the file, loads the bank into RAM, then `loadPreset(1)`.

---

## Name field

Within each 140-byte slot, name characters are at offsets **119..130** (12 chars used in load/save UI; Screen `'q'` sends 16 bytes; Mainboard `'q'` gets first 8).

Helpers: `load_preset_name`, `get_preset_name`.

---

## Load / save flow

1. **Select** — encoder/button UI sets `presetSelectVal`; Screen gets `'q'` scroll updates.
2. **Load** — `loadPreset(n)` copies slot → `flashData`, unpacks into locals/flags, runs `loadPresetActions` (re-TX params / control blocks).
3. **Save** — UI gathers name via char select (`'c'` / `'s'` signals); `writePreset` / `writePresetActions` pack `flashData` and write through the RAM bank back to LittleFS.

Exact byte layout for every ParamId is encoded in `loadPreset` / `writePreset` in `presetStorage.ino` — treat those functions as the source of truth when extending the format.

---

## Related flags

`presetSelect`, `presetSaveSelectMode`, `presetSaveMode`, `presetSaved`, `funcKeyOn` — see `Controls.h` and button actions in `buttons.ino`.
