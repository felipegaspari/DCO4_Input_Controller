void read_encoder_buttons() {
  for (int i = 0; i < NUM_BUTTONS; i++) {

    ButtonStruct& button = buttons[i];

    ButtonAction currentButtonAction;

    ButtonState currentButtonState;

    button.button_n.update(valorMUX1[button.pin], 50, LOW);

    if (buttons[i].button_n.held()) {
      currentButtonState = HELD;
      if (funcKeyOn) {
        currentButtonAction = button.actionHeldAlt;
        Serial.println((String) "Button Held ALT " + i);
      } else {
        currentButtonAction = button.actionHeld;
        Serial.println((String) "Button Held " + i);
      }
    } else if (button.button_n.doublePressed()) {
      currentButtonState = DOUBLE;
      if (funcKeyOn) {
        currentButtonAction = button.actionDoubleAlt;
        Serial.println((String) "Button Double ALT " + i);
      } else {
        currentButtonAction = button.actionDouble;
        Serial.println((String) "Button Double " + i);
      }
    } else if (button.button_n.pressed()) {
      currentButtonState = PRESSED;
      if (funcKeyOn) {
        currentButtonAction = button.actionPressedAlt;
        Serial.println((String) "Button Pressed ALT " + i);
      } else {
        currentButtonAction = button.actionPressed;
        Serial.println((String) "Button Pressed " + i);
      }
    } else if (button.button_n.released(true)) {
      currentButtonState = RELEASED;
      if (funcKeyOn) {
        currentButtonAction = button.actionReleasedAlt;
        Serial.println((String) "Button ReleasedALT " + i);
      } else {
        currentButtonAction = button.actionReleased;
        Serial.println((String) "Button Released " + i);
      }
    } else {
      currentButtonState = BTN_STATE_NONE;
      currentButtonAction = BTN_ACTION_NONE;
    }

    switch (currentButtonAction) {
      case BTN_ACTION_NONE:
        break;
      case TG_SAW1:
        sawStatus = !sawStatus;
        //digitalWrite(PIN_SAW1, sawStatus);
        serial_send_param_change(1, !sawStatus);
        update_LED_Control(LEDPins[0], sawStatus);
        break;
      case TG_SAW2:
        saw2Status = !saw2Status;
        //digitalWrite(PIN_SAW2, saw2Status);
        serial_send_param_change_byte(2, !saw2Status);
        update_LED_Control(LEDPins[3], saw2Status);
        break;
      case TG_TRI:
        triStatus = !triStatus;
        //digitalWrite(PIN_TRI, triStatus);
        serial_send_param_change_byte(3, !triStatus);
        update_LED_Control(LEDPins[2], triStatus);
        break;
      case TG_SIN:
        sineStatus = !sineStatus;
        //digitalWrite(PIN_SIN, sineStatus);
        serial_send_param_change_byte(4, !sineStatus);
        //update_LED_Control();
        break;
      case TG_SQR1:
        sqr1Status = !sqr1Status;
        serial_send_param_change_byte(5, sqr1Status);
        update_LED_Control(LEDPins[1], sqr1Status);
        break;
      case TG_SQR2:
        sqr2Status = !sqr2Status;
        serial_send_param_change_byte(6, sqr2Status);
        update_LED_Control(LEDPins[4], sqr2Status);
        break;

      case TG_RESO_AMP_COMP:
        RESONANCEAmpCompensation = !RESONANCEAmpCompensation;
        serial_send_param_change_byte(7, RESONANCEAmpCompensation);
        break;

      case TG_ADSR1_RESTART:
        if (ADSR1CurveSelect == true) {
          ADSR1CurveSelect = false;
          serial_send_param_change_byte(48, 100);
        } else {
          VCAADSRRestart = !VCAADSRRestart;
          serial_send_param_change_byte(8, VCAADSRRestart);
        }
        break;

      case TG_ADSR2_RESTART:
        if (ADSR2CurveSelect == true) {
          ADSR2CurveSelect = false;
        } else {
          VCFADSRRestart = !VCFADSRRestart;
          serial_send_param_change_byte(9, VCFADSRRestart);
        }
        break;

      case SELECT_LFO_N:
        break;
      case TG_LFO1_WAVE:
        LFO1WaveformVal++;
        if (LFO1WaveformVal > 4) {
          LFO1WaveformVal = 1;
        }

        LFO1Waveform = LFO1WaveformVal;
        serial_send_LFO1toDCOWaveChangeFlag = true;
        serial_send_param_change_byte(11, LFO1Waveform);

        break;

      case TG_LFO2_WAVE:
        LFO2WaveformVal++;
        if (LFO2WaveformVal > 4) {
          LFO2WaveformVal = 1;
        }

        LFO2Waveform = LFO2WaveformVal;
        serial_send_param_change_byte(12, LFO2Waveform);
        break;

      case TG_VOICE_MODE:
        voiceMode++;
        if (voiceMode > 2) {
          voiceMode = 0;
        }
        serial_send_param_change_byte(26, voiceMode);
        break;

      case TG_FUNC:
        funcKeyOn = !funcKeyOn;
        serial_send_param_change_byte(127, (uint8_t)funcKeyOn);
        break;

      case WORK_WITH_PRESETS:
        break;

      case PRESET_SAVE_SELECT_MODE:
        if (presetSaveMode) {  // SAVE MODE EXIT
          presetSaveMode = false;
          presetSaveSelectMode = false;
          charSelectVal = 0;
          for (int i = 0; i < 12; i++) {
            presetNameVal[i] = presetName[i];
          }
          charSelectVal = 0;
          presetChar = 0;
          presetSelectVal = currentPreset;
          serial_send_signal(2);
          serial_send_preset_scroll(currentPreset, presetName);
        } else {
          presetSaveSelectMode = !presetSaveSelectMode;
          if (presetSaveSelectMode) {
            charSelectVal = 0;
            serial_send_signal(3);  // ENTER SAVE SELECT MODE
          } else {
            serial_send_signal(2);  // SAVE SELECT MODE EXIT
            serial_send_preset_scroll(currentPreset, presetName);
            presetSelectVal = currentPreset;
          }
        }
        break;

      case PRESET_SAVE_MODE:

        break;

      case SAVE_PRESET:
        if (presetSaveMode) {
          presetSaveMode = false;
          presetSaveSelectMode = false;

          //serial_send_signal(5);
          serial_send_preset_name_to_mainboard();
          serial_send_param_change_byte(142, presetSelectVal);
          writePreset(presetSelectVal);
          //writePresetActions(presetSelectVal);

          serial_send_signal(5);

        } else {
          if (presetSaveSelectMode) {
            serial_send_preset_scroll(presetSelectVal, presetNameVal);
            serial_send_signal(4);
            presetSaveMode = true;
            for (int i = 0; i < 13; i++) {
              presetNameVal[i] = presetName[i];
            }
            charSelectVal = presetNameVal[0];
            serial_send_save_char_select(0);
            serial_send_preset_scroll(presetSelectVal, presetNameVal);
          }
        }
        break;

      case TG_MAN_FADERS:
        faderControlManual = !faderControlManual;
        faderRow1ControlManual = faderControlManual;
        faderRow2ControlManual = faderControlManual;
        serial_send_param_change_byte(120, faderControlManual);
        //update_LED_Control();
        break;
      case TG_MAN_FADER_ROW1:
        faderRow1ControlManual = !faderRow1ControlManual;
        serial_send_param_change_byte(121, faderRow1ControlManual);
        update_LED_Control(LEDPins[10], faderRow1ControlManual);
        break;
      case TG_MAN_FADER_ROW2:
        faderRow2ControlManual = !faderRow2ControlManual;
        serial_send_param_change_byte(122, faderRow2ControlManual);
        update_LED_Control(LEDPins[11], faderRow2ControlManual);
        break;
      case TG_MAN_POTS:
        potsControlManual = !potsControlManual;
        VCFPotsControlManual = potsControlManual;
        VCAPotsControlManual = potsControlManual;
        PWMPotsControlManual = potsControlManual;
        serial_send_param_change_byte(129, potsControlManual);
        //update_LED_Control();
        break;
      case TG_MANUAL_VCF_POTS:
        VCFPotsControlManual = !VCFPotsControlManual;
        serial_send_param_change_byte(123, VCFPotsControlManual);
        update_LED_Control(LEDPins[7], VCFPotsControlManual);
        break;

      case TG_MANUAL_VCA_POTS:
        VCAPotsControlManual = !VCAPotsControlManual;
        serial_send_param_change_byte(128, VCAPotsControlManual);
        update_LED_Control(LEDPins[8], VCAPotsControlManual);
        break;

      case TG_MANUAL_PWM_POTS:
        PWMPotsControlManual = !PWMPotsControlManual;
        serial_send_param_change_byte(124, PWMPotsControlManual);
        update_LED_Control(LEDPins[9], PWMPotsControlManual);
        break;
      case TG_MANUAL_ALL:
        allControlsManual = !allControlsManual;
        VCFPotsControlManual = allControlsManual;
        faderRow2ControlManual = allControlsManual;
        faderRow1ControlManual = allControlsManual;
        PWMPotsControlManual = allControlsManual;
        serial_send_param_change_byte(125, allControlsManual);
        //update_LED_Control();
        break;

      case TG_ENABLE_ADSR3:
        ADSR3Enabled = !ADSR3Enabled;
        faderRow2ControlManual = false;
        serial_send_param_change_byte(126, (uint8_t)ADSR3Enabled);
        LED_Control_Mux.blinkPin(LEDPins[11], ADSR3Enabled);
        update_LED_Control(LEDPins[11], ADSR3Enabled);
        break;

      case ADSR1_CURVE_SEL:
        ADSR1CurveSelect = !ADSR1CurveSelect;
        serial_send_param_change_byte(48, 100);
        break;

      case ADSR2_CURVE_SEL:
        ADSR2CurveSelect = !ADSR2CurveSelect;
        serial_send_param_change_byte(50, 100);
        break;

      case SELECT_ENC_ACTION:
        break;

      case TG_ADSR3_TO_OSC_SELECT:
        ADSR3ToOscSelect++;
        if (ADSR3ToOscSelect > 2) {
          ADSR3ToOscSelect = 0;
        }
        serialSendADSR3ToOscSelectFlag = true;
        serial_send_param_change_byte(10, ADSR3ToOscSelect);
        break;
    }
  }
}