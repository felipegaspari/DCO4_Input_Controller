# DCO4_Input_Controller — Reference (AI / developers)

Semantic map of the RP2040 front-panel firmware. Prefer [`FILE_INDEX.md`](FILE_INDEX.md) for call sites.

- System: [`SYSTEM_OVERVIEW.md`](SYSTEM_OVERVIEW.md) → DCO4_DCO canonical
- Pipeline: [`CONTROL_PIPELINE.md`](CONTROL_PIPELINE.md)
- Pins: [`PANEL_AND_PINS.md`](PANEL_AND_PINS.md)
- Presets: [`PRESETS.md`](PRESETS.md)
- Serial how-to: [`README_serial_and_params.md`](README_serial_and_params.md)
- Entry: [`../README.md`](../README.md)

---

## What this board owns

| Owns | Does not own |
|------|----------------|
| Panel scan (faders, pots, encoders, buttons) | Voice allocation / DCO pitch |
| LittleFS preset bank | ADSR/LFO CV generation (Mainboard) |
| UART fan-out of controls/params to Mainboard + Screen | TFT UI (Screen) |
| Manual-mode continuous control streaming | Amp/PW calibration measurement (DCO) |

Primarily a **protocol sender**. Live inbound apply-router is almost unused (`params.ino` commented).

---

## Runtime model

**Core 0:** scan hardware (`readControls` → mux / encoders / buttons). Encoder/button handlers emit ParamIds, UI signals, preset ops.

**Core 1:** map filtered ADC when manual flags set; TX `'a'..'f'` blocks + params; LED refresh; parse inbound `'x'` on Serial1.

---

## Modules

| Module | Role |
|--------|------|
| `Controls.*` | Mux GPIO, ADC Kalman, `setControlValues` |
| `encoders.*` | 11 encoders + `EncoderAction` table |
| `buttons.*` | 16 buttons + mode machine |
| `LED_control.*` | Dual 595 status LEDs |
| `Serial.ino` / `Serial2.ino` | TX helpers; manual blocks; inbound parser |
| `presetStorage.ino` / `FS.h` | LittleFS bank |
| `params_def.h` | Shared IDs (fork may lag Mainboard — sync carefully) |
| `Timers_millis.*` | Soft timers for both cores |
| `auxiliary.*` | Kalman + lin→exp table |

---

## Edit carefully

- **ParamId numbers** — keep aligned with Mainboard copy (coordination point).
- **`'a'..'f'` payload sizes** — must match Mainboard `serial_input_protocol.h` / handlers.
- **Screen `'q'` is 16 chars; Mainboard `'q'` is 8** — do not conflate.
- **Serial2 peer is Mainboard**, not DCO (despite some comments).
- **GP5** LED PWM vs Serial2 RX overlap.
- Preset **140-byte** layout — extend only by updating both load and write paths.

---

## Dead / inactive

- `sendSerial()` — not scheduled
- `params.ino` / most `formulas.ino` — commented
- TinyUSB MIDI — include commented
- Legacy preset-save encoder path in `Controls.ino` — superseded by main encoder/button modes
