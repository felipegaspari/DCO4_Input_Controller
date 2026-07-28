## DCO4 – Input Controller (RP2040 front panel)

Firmware for the **DCO4 front-panel / input board**: an RP2040 Arduino sketch that scans **faders, potentiometers, encoders, and buttons**, drives **status LEDs**, stores **presets in LittleFS**, and fans control data out over UART to the **mainboard** and **screen**.

Dual-core: Core 0 scans the panel; Core 1 maps manual controls, talks serial, refreshes LEDs, and runs filesystem init.

How this board fits the instrument: [`docs/SYSTEM_OVERVIEW.md`](docs/SYSTEM_OVERVIEW.md) → canonical overview in sibling **DCO4_DCO**.

All detailed documentation lives under **[`docs/`](docs/)**. This README is the entry point.

---

## Documentation

| Doc | Status | Contents |
|-----|--------|----------|
| [`docs/SYSTEM_OVERVIEW.md`](docs/SYSTEM_OVERVIEW.md) | Current | Stub → canonical four-board overview + local UART table |
| [`docs/CONTROL_PIPELINE.md`](docs/CONTROL_PIPELINE.md) | Current | Dual-core scan → ParamId / `'a'..'f'` → Mainboard & Screen |
| [`docs/PANEL_AND_PINS.md`](docs/PANEL_AND_PINS.md) | Current | Mux, fader/pot indices, LED/UART pins |
| [`docs/PRESETS.md`](docs/PRESETS.md) | Current | LittleFS bank, 140-byte slots, load/save |
| [`docs/FILE_INDEX.md`](docs/FILE_INDEX.md) | Current | Every file + functions + call sites |
| [`docs/REFERENCE_AI.md`](docs/REFERENCE_AI.md) | Current | Deep semantic map for developers / AI |
| [`docs/README_serial_and_params.md`](docs/README_serial_and_params.md) | Current | Shared serial / ParamId how-to |

**Suggested reading:** this README → system stub → control pipeline / panel pins → presets → FILE_INDEX or REFERENCE_AI.

---

## Features

- **Panel:** CD74HC4067 muxed analog (8 faders + pots) and digital (encoders + 16 buttons).
- **Encoders:** 11× `MD_REncoder` with layered actions (normal / alt / preset / cal / menu).
- **Buttons:** Wave toggles, LFO, voice mode, manual fader/pot enable, preset load/save, function key, calibration UI.
- **LEDs:** Dual 74HC595 status indicators + PWM brightness.
- **Presets:** 256 × 140-byte LittleFS bank (`presetBank1`).
- **Serial:** 2.5 Mbaud to Mainboard (Serial2) and Screen (Serial1); USB Serial @ 2 Mbaud debug.

**Inactive today:** local `params.ino` apply router (commented); legacy `sendSerial()`; USB MIDI stack commented out.

---

## High-level architecture

| Subsystem | Files | Role |
|-----------|-------|------|
| Entry | `DCO4_Input_Controller.ino` | Dual-core setup/loop |
| Scan | `Controls.*`, `encoders.*`, `buttons.*` | Mux + actions |
| LEDs | `LED_control.*` | 595 mux |
| Serial | `Serial.*`, `Serial2.ino`, `serial_*.h` | TX blocks/params; RX `'x'` |
| Presets | `FS.h`, `presetStorage.ino` | LittleFS |
| Timing | `Timers_millis.*` | Soft timers both cores |

Details: [`docs/CONTROL_PIPELINE.md`](docs/CONTROL_PIPELINE.md).

---

## Hardware / UART summary

| Port | Pins | Baud | Peer |
|------|------|------|------|
| Serial | USB | 2 000 000 | Debug |
| Serial1 | RX1 / TX0 | 2 500 000 | Screen |
| Serial2 | RX5 / TX4 | 2 500 000 | Mainboard |

Mux select GP18–21; analog SIG GP27; digital SIG GP2/16/17. Full map: [`docs/PANEL_AND_PINS.md`](docs/PANEL_AND_PINS.md).

---

## Building

- **Toolchain:** Arduino IDE / CLI with Earle Philhower RP2040 core (or compatible).
- **Sketch:** `DCO4_Input_Controller.ino`.
- **Libraries:** `RoxMux` / `RoxMux_fela`, `MD_REncoder_fela`, `CD74HC4067`, `SimpleKalmanFilter`, LittleFS (core).

### Feature flags

| Flag | Default | Effect |
|------|---------|--------|
| `ENABLE_SERIAL` | on | USB debug |
| `ENABLE_SERIAL1` | on | Screen UART |
| `ENABLE_SERIAL2` | on | Mainboard UART |
| `NUM_VOICES` | 4 | Array sizing |

No float/fixed engine forks (no `ENGINE_OPTIONS.md`).

---

## Contributing / hacking

- Start with [`docs/REFERENCE_AI.md`](docs/REFERENCE_AI.md) and [`docs/FILE_INDEX.md`](docs/FILE_INDEX.md).
- Keep ParamIds aligned with Mainboard `params_def.h`.
- When adding continuous controls, respect manual flags + `serial_send_manual_controls`.
- When extending presets, update both `loadPreset` and `writePreset` layouts.
