#include "include_all.h"
void read_encoder_buttons() {

  if ((millis() - buttonActionSelectedMillis) > buttonActionSelectedTimeout) {
    buttonActionSelected = BTN_ACTION_NONE;
    buttonActionIsSelected = false;
  }

  for (int i = 0; i < NUM_BUTTONS; i++) {

    ButtonStruct& button = buttons[i];

    currentButtonAction = BTN_ACTION_NONE;
    currentButtonState = BTN_STATE_NONE;

    button.button_n.update(valorMUX1[button.pin], 50, LOW);


    if (currentControlMode == NORMAL) {
      if (button.button_n.latched()) {
        handleLatchedButton(i);
      } else if (button.button_n.held()) {
        currentButtonState = HELD;
        handleHeldButton(i);
      } else if (button.button_n.doublePressed()) {
        currentButtonState = DOUBLE;
        handleDoublePressedButton(i);
      } else if (button.button_n.pressed()) {
        currentButtonState = PRESSED;
        handlePressedButton(i);
      } else if (button.button_n.released(true)) {
        currentButtonState = RELEASED;
        handleReleasedButton(i);
      } else if (button.button_n.unlatched()) {
        handleUnlatchedButton(i);
      } else {
        currentButtonState = BTN_STATE_NONE;
        currentButtonAction = BTN_ACTION_NONE;
      }

      if (currentButtonState != BTN_STATE_NONE) {
        if (currentButtonAction == buttonActionSelected) {
          buttonActionIsSelected = true;
        } else {
          buttonActionSelected = currentButtonAction;
          buttonActionIsSelected = false;
        }

        buttonActionSelectedMillis = millis();
      }

    } else {
      if (button.button_n.held()) {
        currentButtonState = HELD;
        currentButtonAction = button.actionMenuNavigationHeld;
      } else if (button.button_n.released(true)) {
        currentButtonState = RELEASED;
        currentButtonAction = button.actionMenuNavigationReleased;
      }
    }

    switch (currentControlMode) {

      case PRESET_SAVE:
        // switch(currentButtonAction) {
        //   case EXIT:
        //         currentControlMode = NORMAL;
        //         currentButtonAction = BTN_ACTION_NONE;
        //       break;
        //       case BACK:
        //       currentButtonAction = BTN_ACTION_NONE;

        //       break;
        //       case SELECT:
        //       currentButtonAction = BTN_ACTION_NONE;
        //       break;
        //       case CONFIRM:
        //       currentButtonAction = BTN_ACTION_NONE;
        //       break;
        // }
        break;

      case MANUAL_CALIBRATION:
        switch (currentButtonAction) {
          case EXIT:
            currentControlMode = CALIBRATION_MENU;
            currentButtonAction = BTN_ACTION_NONE;
            manualCalibration = false;
            serial_send_param_change_byte(151, manualCalibration);
            //serialSendParamByteToScreen(199, 0);

            break;
          case BACK:
            currentControlMode = CALIBRATION_MENU;
            currentButtonAction = BTN_ACTION_NONE;
            manualCalibration = false;
            serial_send_param_change_byte(151, manualCalibration);
            //serialSendParamByteToScreen(199, 0);
            break;
          case SELECT:
            currentButtonAction = BTN_ACTION_NONE;
            break;
          case CONFIRM:
            currentControlMode = NORMAL;
            currentButtonAction = BTN_ACTION_NONE;
            manualCalibration = false;
            serial_send_param_change_byte(151, manualCalibration);
            break;
        }
        break;

      case CALIBRATION_MENU:
        switch (currentButtonAction) {
          case EXIT:
            currentControlMode = NORMAL;
            currentButtonAction = BTN_ACTION_NONE;
            serial_send_param_change_byte(199, 0);
            break;
          case BACK:
            currentControlMode = NORMAL;
            currentButtonAction = BTN_ACTION_NONE;
            serial_send_param_change_byte(199, 0);
            break;
          case SELECT:
            switch (menuPos) {
              case 0:
                serial_send_param_change_byte(150, 1);
                break;
              case 1:
                break;
              case 2:
                break;
              case 3:
                currentButtonAction = TG_MAN_CALIBRATION;
                break;
            }
            break;
          case CONFIRM:
            break;
        }
        break;
    }

    // if (button.button_n.latched()) {
    //   if (i <= 6) {
    //     buttonIsLatched[i] = true;
    //     update_LED_Control(i, true);
    //     LED_Control_Mux.blinkPin(LEDPins[i], true);
    //   }
    //   //Serial.println("* Button is latched (open)");
    // }

    // if (buttons[i].button_n.held()) {
    //   currentButtonState = HELD;

    //   if (funcKeyOn) {
    //     currentButtonAction = button.actionHeldAlt;
    //     //Serial.println((String) "Button Held ALT " + i);
    //   } else {
    //     currentButtonAction = button.actionHeld;
    //     //Serial.println((String) "Button Held " + i);
    //   }
    // } else if (button.button_n.doublePressed()) {
    //   currentButtonState = DOUBLE;
    //   if (funcKeyOn) {
    //     currentButtonAction = button.actionDoubleAlt;
    //     //Serial.println((String) "Button Double ALT " + i);
    //   } else {
    //     currentButtonAction = button.actionDouble;
    //     //Serial.println((String) "Button Double " + i);
    //   }
    // } else if (button.button_n.pressed()) {
    //   currentButtonState = PRESSED;
    //   if (funcKeyOn) {
    //     currentButtonAction = button.actionPressedAlt;
    //     //Serial.println((String) "Button Pressed ALT " + i);
    //   } else {
    //     currentButtonAction = button.actionPressed;
    //     //Serial.println((String) "Button Pressed " + i);
    //   }
    // } else if (button.button_n.released(true)) {
    //   currentButtonState = RELEASED;
    //   if (i <= 6) {
    //     buttonIsLatched[i] = false;
    //     set_LED_Status(16, 0);
    //     LED_Control_Mux.blinkPin(LEDPins[i], 0);
    //   }

    //   if (funcKeyOn) {
    //     currentButtonAction = button.actionReleasedAlt;
    //     //Serial.println((String) "Button ReleasedALT " + i);
    //   } else {
    //     currentButtonAction = button.actionReleased;
    //     //Serial.println((String) "Button Released " + i);
    //   }
    //   // } else if (button.button_n.latched()) {
    //   //Serial.println("* Button is Latched (closed)");

    // } else if (button.button_n.unlatched()) {
    //   if (i <= 6) {
    //     buttonIsLatched[i] = false;
    //     set_LED_Status(16, 0);
    //     LED_Control_Mux.blinkPin(LEDPins[i], 0);
    //   }
    //   //Serial.println("* Button is Unlatched (open)");
    // } else {
    //   currentButtonState = BTN_STATE_NONE;
    //   currentButtonAction = BTN_ACTION_NONE;
    // }

    switch (currentButtonAction) {
      case BTN_ACTION_NONE:
        break;
      case TG_SAW1:
        sawStatus = !sawStatus;
        //digitalWrite(PIN_SAW1, sawStatus);

        serial_send_param_change(1, sawStatus);
        set_LED_Status(0, sawStatus);
        break;
      case TG_SAW2:
        saw2Status = !saw2Status;
        //digitalWrite(PIN_SAW2, saw2Status);
        serial_send_param_change_byte(2, saw2Status);
        set_LED_Status(3, saw2Status);
        break;
      case TG_TRI:
        triStatus = !triStatus;
        //digitalWrite(PIN_TRI, triStatus);
        serial_send_param_change_byte(3, triStatus);
        set_LED_Status(2, triStatus);
        break;
      case TG_SIN:
        sineStatus = !sineStatus;
        //digitalWrite(PIN_SIN, sineStatus);
        serial_send_param_change_byte(4, sineStatus);
        //set_LED_Status();
        break;
      case TG_SQR1:
        sqr1Status = !sqr1Status;
        serial_send_param_change_byte(5, sqr1Status);
        set_LED_Status(1, sqr1Status);
        break;
      case TG_SQR2:
        sqr2Status = !sqr2Status;
        serial_send_param_change_byte(6, sqr2Status);
        set_LED_Status(4, sqr2Status);
        break;

      case TG_RESO_AMP_COMP:
        if (buttonActionIsSelected) {
          RESONANCEAmpCompensation = !RESONANCEAmpCompensation;
        }
        serial_send_param_change_byte(7, RESONANCEAmpCompensation);
        break;

      case TG_ADSR1_RESTART:
        if (ADSR1CurveSelect == true) {
          ADSR1CurveSelect = false;
          serial_send_param_change_byte(48, -1);
        } else {
          if (buttonActionIsSelected) {
            VCAADSRRestart = !VCAADSRRestart;
          }
          serial_send_param_change_byte(8, VCAADSRRestart);
        }
        break;

      case TG_ADSR2_RESTART:  //
        if (ADSR2CurveSelect == true) {
          ADSR2CurveSelect = false;
          serial_send_param_change_byte(48, -1);
        } else {
          if (buttonActionIsSelected) {
            VCFADSRRestart = !VCFADSRRestart;
          }
          serial_send_param_change_byte(9, VCFADSRRestart);
        }
        break;

      case SELECT_LFO_N:
        break;

      case TG_LFO1_WAVE:
        if (buttonActionIsSelected) {
          LFO1Waveform++;
          if (LFO1Waveform > 4) {
            LFO1Waveform = 1;
          }
        }
        serial_send_param_change_byte(11, LFO1Waveform);

        break;

      case TG_LFO2_WAVE:
        if (buttonActionIsSelected) {
          LFO2Waveform++;
          if (LFO2Waveform > 4) {
            LFO2Waveform = 1;
          }
        }
        serial_send_param_change_byte(12, LFO2Waveform);
        break;

      case TG_VOICE_MODE:
        if (buttonActionIsSelected) {
          voiceMode++;
          if (voiceMode > 2) {
            voiceMode = 0;
          }
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
          presetCharPos = 0;
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
          //serial_send_preset_name_to_mainboard();
          //serial_send_param_change_byte(142, presetSelectVal);
          writePreset(presetSelectVal);
          //writePresetActions(presetSelectVal);

          serial_send_signal(5);
          presetCharPos = 0;
        } else {
          if (presetSaveSelectMode) {
            serial_send_signal(4);
            presetSaveMode = true;
            for (int i = 0; i < 12; i++) {
              presetNameVal[i] = presetName[i];
            }

            charSelectVal = presetNameVal[0];
            presetCharPos = 0;
            // serial_send_save_char_select(0);
            // serial_send_preset_scroll(presetSelectVal, presetNameVal);
          }
        }
        break;

      case TG_MAN_FADERS:
        faderControlManual = !faderControlManual;
        faderRow1ControlManual = faderControlManual;
        faderRow2ControlManual = faderControlManual;
        serial_send_param_change_byte(120, faderControlManual);
        //set_LED_Status();
        break;
      case TG_MAN_FADER_ROW1:
        faderRow1ControlManual = !faderRow1ControlManual;
        serial_send_param_change_byte(121, faderRow1ControlManual);
        set_LED_Status(10, faderRow1ControlManual);
        break;
      case TG_MAN_FADER_ROW2:
        faderRow2ControlManual = !faderRow2ControlManual;
        serial_send_param_change_byte(122, faderRow2ControlManual);
        set_LED_Status(11, faderRow2ControlManual);
        break;
      case TG_MAN_POTS:
        potsControlManual = !potsControlManual;
        VCFPotsControlManual = potsControlManual;
        VCAPotsControlManual = potsControlManual;
        PWMPotsControlManual = potsControlManual;
        serial_send_param_change_byte(129, potsControlManual);
        //set_LED_Status();
        break;
      case TG_MANUAL_VCF_POTS:
        VCFPotsControlManual = !VCFPotsControlManual;
        serial_send_param_change_byte(123, VCFPotsControlManual);
        set_LED_Status(7, VCFPotsControlManual);
        break;

      case TG_MANUAL_VCA_POTS:
        VCAPotsControlManual = !VCAPotsControlManual;
        serial_send_param_change_byte(128, VCAPotsControlManual);
        set_LED_Status(8, VCAPotsControlManual);
        break;

      case TG_MANUAL_PWM_POTS:
        PWMPotsControlManual = !PWMPotsControlManual;
        serial_send_param_change_byte(124, PWMPotsControlManual);
        set_LED_Status(9, PWMPotsControlManual);
        break;
      case TG_MANUAL_ALL:
        allControlsManual = !allControlsManual;
        VCFPotsControlManual = allControlsManual;
        faderRow2ControlManual = allControlsManual;
        faderRow1ControlManual = allControlsManual;
        PWMPotsControlManual = allControlsManual;
        serial_send_param_change_byte(125, allControlsManual);
        //set_LED_Status();
        break;

      case TG_ENABLE_ADSR3:
        ADSR3Enabled = !ADSR3Enabled;
        faderRow2ControlManual = false;
        serial_send_param_change_byte(126, (uint8_t)ADSR3Enabled);
        serialSendADSR3ControlValuesFlag = true;
        LED_Control_Mux.blinkPin(LEDPins[11], ADSR3Enabled);
        set_LED_Status(11, faderRow2ControlManual);
        break;

      case TG_SYNC_MODE:
        if (buttonActionIsSelected) {
          syncMode++;
          if (syncMode > 2) {
            syncMode = 0;
          }
        }
        serial_send_param_change_byte(31, syncMode);
        break;

      case ADSR1_CURVE_SEL:
        if (buttonActionIsSelected) {
          ADSR1CurveSelect = !ADSR1CurveSelect;
        }
        serial_send_param_change_byte(48, -1);
        break;

      case ADSR2_CURVE_SEL:
        if (buttonActionIsSelected) {
          ADSR2CurveSelect = !ADSR2CurveSelect;
        }
        serial_send_param_change_byte(50, -1);
        break;

      case SELECT_ENC_ACTION:

        break;

      case TG_ADSR3_TO_OSC_SELECT:
        if (buttonActionIsSelected) {
          ADSR3ToOscSelect++;
          if (ADSR3ToOscSelect > 2) {
            ADSR3ToOscSelect = 0;
          }
        }
        serialSendADSR3ToOscSelectFlag = true;
        serial_send_param_change_byte(10, ADSR3ToOscSelect);
        break;

      case TG_CALIBRATION_MENU:
        menuPos = 0;
        menuPosMax = 3;
        currentControlMode = CALIBRATION_MENU;
        serial_send_param_change_byte(200, 1);
        serial_send_param_change_byte(190, (uint8_t)menuPos);
        break;

      case TG_MAN_CALIBRATION:
        manualCalibration = true;
        currentControlMode = MANUAL_CALIBRATION;
        manualCalibrationStage = 0;
        memset(manualCalibrationInitAmpCompOffset, 0, sizeof(manualCalibrationInitAmpCompOffset));
        serial_send_param_change_byte(151, manualCalibration);
        serial_send_param_change(152, (uint8_t)manualCalibrationStage);
        serial_send_param_change(153, (uint8_t)manualCalibrationInitAmpCompOffset[manualCalibrationStage / 2]);
        break;

      case BACK:

        break;
      case EXIT:

        break;
      case SELECT:

        break;
      case CONFIRM:

        break;
    }
  }
}

void handleLatchedButton(int i) {
  if (i <= 6) {
    buttonIsLatched[i] = true;
    update_LED_Control(i, true);
    LED_Control_Mux.blinkPin(LEDPins[i], true);
  }
}

void handleHeldButton(int i) {
  ButtonStruct& button = buttons[i];
  currentButtonAction = funcKeyOn ? button.actionHeldAlt : button.actionHeld;
}

void handleDoublePressedButton(int i) {
  ButtonStruct& button = buttons[i];
  currentButtonAction = button.actionDouble;
}

void handlePressedButton(int i) {
  ButtonStruct& button = buttons[i];
  currentButtonAction = funcKeyOn ? button.actionPressedAlt : button.actionPressed;
}

void handleReleasedButton(int i) {
  ButtonStruct& button = buttons[i];
  if (i <= 6) {
    buttonIsLatched[i] = false;
    set_LED_Status(16, 0);
    LED_Control_Mux.blinkPin(LEDPins[i], 0);
  }
  currentButtonAction = funcKeyOn ? button.actionReleasedAlt : button.actionReleased;
}

void handleUnlatchedButton(int i) {
  if (i <= 6) {
    buttonIsLatched[i] = false;
    set_LED_Status(16, 0);
    LED_Control_Mux.blinkPin(LEDPins[i], 0);
  }
}