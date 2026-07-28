# System overview (Input Controller pointer)

This board is the **DCO4 input / front-panel controller** (RP2040): muxed **faders, pots, encoders, buttons**, **status LEDs**, **LittleFS preset storage**, and UART fan-out to the **mainboard** and **screen**.

The **canonical four-board system overview** lives in the sibling DCO repo:

**[`../../DCO4_DCO/docs/SYSTEM_OVERVIEW.md`](../../DCO4_DCO/docs/SYSTEM_OVERVIEW.md)**

Do not fork a second full system document here. If a UART pin, baud, or ownership fact disagrees with this firmware, fix the **DCO** copy.

### This board’s UARTs (verified in firmware)

| Port | Pins (RX / TX) | Baud | Peer |
|------|----------------|------|------|
| `Serial` | USB | 2 000 000 | Debug |
| `Serial1` | GP1 / GP0 | 2 500 000 | Screen (TX UI frames; also hosts the live inbound `'x'` parser today) |
| `Serial2` | GP5 / GP4 | 2 500 000 | Mainboard `Serial8` (TX control blocks / params) |

**Note:** `PIN_LED_PWM` is also **GP5** (same as Serial2 RX) — confirm hardware sharing. See [`PANEL_AND_PINS.md`](PANEL_AND_PINS.md).

Board-specific detail: [`CONTROL_PIPELINE.md`](CONTROL_PIPELINE.md), [`PRESETS.md`](PRESETS.md), [`REFERENCE_AI.md`](REFERENCE_AI.md).
