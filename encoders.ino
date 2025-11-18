
#include "include_all.h"
void read_encoders() {

  if ((millis() - encoderActionSelectedMillis) > encoderActionSelectedTimeout) {
    encoderActionSelected = ACTION_NONE;
    encoderActionIsSelected = false;
  }

  for (int i = 0; i < sizeof(encoders) / sizeof(encoders[0]); i++) {

    EncoderAction currentAction = ACTION_NONE;
    EncoderAction currentAltAction = ACTION_NONE;

    EncoderStruct& encoder = encoders[i];

    EncoderAction actionArray[3] = { encoder.action1, encoder.action2, encoder.action3 };
    EncoderAction actionAltArray[3] = { encoder.actionAlt1, encoder.actionAlt2, encoder.actionAlt3 };

    uint8_t direction = encoder.MD_REncoder_Name.read(valorMUX1[encoder.muxPin1], valorMUX1[encoder.muxPin2]);
    uint16_t speed = encoder.MD_REncoder_Name.speed();

    if (direction) {
      speed = encoder.MD_REncoder_Name.speed();

      switch (currentControlMode) {
        case NORMAL:

          if (presetSaveSelectMode) {
            if (presetSaveMode) {
              currentAction = actionArray[1];
            } else {
              currentAction = actionAltArray[1];
            }
          } else if (ADSR1CurveSelect == true || ADSR2CurveSelect == true) {
            currentAction = actionAltArray[2];
          } else if (funcKeyOn) {
            if (buttonIsLatched[i] == true) {
              currentAction = actionAltArray[1];
            } else {
              currentAction = actionAltArray[0];
            }
          } else {
            if (buttonIsLatched[i] == true) {
              currentAction = actionArray[1];
            } else {
              currentAction = actionArray[0];
            }
          }

          if (currentAction == encoderActionSelected) {
            encoderActionIsSelected = true;
          } else {
            encoderActionSelected = currentAction;
            encoderActionIsSelected = false;
          }

           encoderActionSelectedMillis = millis();

          break;

        case MANUAL_CALIBRATION:
          currentAction = manualCalibrationActions[i];
          break;
        case MENU_NAVIGATION:
          currentAction = menuNavigationActions[i];
          break;
        case CALIBRATION_MENU:
        currentAction = menuNavigationActions[i];
        break;
      }
    }

    switch (currentAction) {

      case ACTION_NONE:
        break;

      case ACTION_portamento_time:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            portamentoTime = portamentoTime + (1 + (0.5 * speed));
          } else {
            portamentoTime = portamentoTime - (1 + (0.5 * speed));
          }
          portamentoTime = constrain(portamentoTime, 0, 255);
        }
        //serial_send_portamentoFlag = true;
        serial_send_param_change_byte(ParamId::PARAM_PORTAMENTO_TIME, (uint8_t)portamentoTime);
        break;

      case ACTION_LFO1_to_DCO:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO1toDCO = LFO1toDCO + (1 + (0.5 * speed));
          } else {
            LFO1toDCO = LFO1toDCO - (1 + (0.5 * speed));
          }
        LFO1toDCO = constrain(LFO1toDCO, 0, 511);
        }
        serial_send_param_change(ParamId::PARAM_LFO1_TO_DCO, (uint16_t)LFO1toDCO);

        //serial_send_LFO1toDCOFlag = true;  //DCO FM / LFO
        break;

      case ACTION_VCF_keytrack:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            VCFKeytrack = VCFKeytrack + (1 + (0.5 * speed));
          } else {
            VCFKeytrack = VCFKeytrack - (1 + (0.5 * speed));
          }
          VCFKeytrack = constrain(VCFKeytrack, -256, 255);
        }
        serial_send_param_change(ParamId::PARAM_VCF_KEYTRACK, (uint16_t)VCFKeytrack);
        break;

      case ACTION_ADSR3_to_DETUNE1:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            ADSR3toDETUNE1 = ADSR3toDETUNE1 + (1 + (1 * speed));
          } else {
            ADSR3toDETUNE1 = ADSR3toDETUNE1 - (1 + (1 * speed));
          }
          ADSR3toDETUNE1 = constrain(ADSR3toDETUNE1, -511, 511);
          //formula_update(10);
          //serialSendADSR3toDCOFlag = true;
        }
        serial_send_param_change(ParamId::PARAM_ADSR3_TO_DETUNE1, (uint16_t)ADSR3toDETUNE1);
        break;

      case ACTION_velocity_to_VCF:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            velocityToVCF = velocityToVCF + 1;
          } else {
            velocityToVCF = velocityToVCF - 1;
          }
          velocityToVCF = constrain(velocityToVCF, 0, 20);
        }
        serial_send_param_change_byte(ParamId::PARAM_VELOCITY_TO_VCF, (uint8_t)velocityToVCF);
        break;

      case ACTION_velocity_to_VCA:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            velocityToVCA = velocityToVCA + (1 + (1 * speed));
          } else {
            velocityToVCA = velocityToVCA - (1 + (1 * speed));
          }
          velocityToVCA = constrain(velocityToVCA, 0, 20);
        }
        serial_send_param_change_byte(ParamId::PARAM_VELOCITY_TO_VCA, (uint8_t)velocityToVCA);
        break;

      case ACTION_octave:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            OSC1Interval = OSC1Interval + 12;
          } else {
            OSC1Interval = OSC1Interval - 12;
          }
          OSC1Interval = constrain(OSC1Interval, 0, 72);
        }
        serial_send_param_change_byte(ParamId::PARAM_OSC1_INTERVAL, (uint8_t)OSC1Interval);  // Octave
        //serial_send_OSC1IntervalFlag = true;
        break;

      case ACTION_SQR1_level:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            SQR1Level = SQR1Level + (1 + (1 * speed));
          } else {
            SQR1Level = SQR1Level - (1 + (1 * speed));
          }
          SQR1Level = constrain(SQR1Level, 0, 128);
        }
        serial_send_param_change_byte(ParamId::PARAM_SQR1_LEVEL, (uint8_t)SQR1Level);
        break;

      case ACTION_SQR2_level:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            SQR2Level = SQR2Level + (1 + (1 * speed));
          } else {
            SQR2Level = SQR2Level - (1 + (1 * speed));
          }
          SQR2Level = constrain(SQR2Level, 0, 128);
        }
        serial_send_param_change_byte(ParamId::PARAM_SQR2_LEVEL, (uint8_t)SQR2Level);
        break;

      case ACTION_SUB_level:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            SubLevel = SubLevel + (1 + (1 * speed));
          } else {
            SubLevel = SubLevel - (1 + (1 * speed));
          }
          SubLevel = constrain(SubLevel, 0, 128);
        }
        serial_send_param_change_byte(ParamId::PARAM_SUB_LEVEL, (uint8_t)SubLevel);
        break;

      case ACTION_OSC2_interval:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            OSC2Interval = OSC2Interval + 1;
          } else {
            OSC2Interval = OSC2Interval - 1;
          }
          OSC2Interval = constrain(OSC2Interval, 0, 48);
        }
        serial_send_param_change_byte(ParamId::PARAM_OSC2_INTERVAL, (uint8_t)OSC2Interval);
        //serial_send_OSC2IntervalFlag = true;
        break;

      case ACTION_OSC2_detune:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            OSC2Detune = OSC2Detune + (1 + (1 * speed));
          } else {
            OSC2Detune = OSC2Detune - (1 + (1 * speed));
          }
          OSC2Detune = constrain(OSC2Detune, 0, 512);
        }
        serial_send_param_change(ParamId::PARAM_OSC2_DETUNE_VAL, (uint16_t)OSC2Detune);
        break;

      case ACTION_LFO2_to_OSC2:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO2toOSC2DETUNE = LFO2toOSC2DETUNE + (1 + (0.5 * speed));
          } else {
            LFO2toOSC2DETUNE = LFO2toOSC2DETUNE - (1 + (0.5 * speed));
          }
          LFO2toOSC2DETUNE = constrain(LFO2toOSC2DETUNE, 0, 255);
        }
        serial_send_param_change_byte(ParamId::PARAM_LFO2_TO_DETUNE2, (uint8_t)LFO2toOSC2DETUNE);
        break;

      case ACTION_osc_sync_mode:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            oscSyncMode = oscSyncMode + 1;
          } else {
            oscSyncMode = oscSyncMode - 1;
          }
          oscSyncMode = constrain(oscSyncMode, 0, 225);
        }
        serial_send_oscSyncModeFlag = true;
        serial_send_param_change_byte(ParamId::PARAM_OSC_SYNC_MODE, (uint8_t)oscSyncMode);
        break;

      case ACTION_LFO1_speed:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO1Speed = LFO1Speed + (1 + (2 * speed));
          } else {
            LFO1Speed = LFO1Speed - (1 + (2 * speed));
          }
          LFO1Speed = constrain(LFO1Speed, 0, 4095);
        }
        serial_send_param_change(ParamId::PARAM_LFO1_SPEED, (uint16_t)LFO1Speed);
        //serial_send_LFO1SpeedFlag = true;  // FM / DCO LFO
        break;

      case ACTION_LFO2_speed:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO2Speed = LFO2Speed + (1 + (2 * speed));
          } else {
            LFO2Speed = LFO2Speed - (1 + (2 * speed));
          }
          LFO2Speed = constrain(LFO2Speed, 0, 4095);
        }
        serial_send_param_change(ParamId::PARAM_LFO2_SPEED, (uint16_t)LFO2Speed);
        break;

      case ACTION_VCA_level:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            VCALevel = VCALevel + (2 + (5 * speed));
          } else {
            VCALevel = VCALevel - (2 + (5 * speed));
          }
          VCALevel = constrain(VCALevel, 0, 128);
        }
        serial_send_param_change_byte(ParamId::PARAM_VCA_LEVEL, (uint8_t)VCALevel);
        break;

      case ACTION_LFO1_to_VCA:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO1toVCA = LFO1toVCA + (1 + (1 * speed));
          } else {
            LFO1toVCA = LFO1toVCA - (1 + (1 * speed));
          }
          LFO1toVCA = constrain(LFO1toVCA, 0, 1023);
        }
        serial_send_param_change(ParamId::PARAM_LFO1_TO_VCA, (uint16_t)LFO1toVCA);
        break;

      case ACTION_LFO2_to_PWM:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            LFO2toPWM = LFO2toPWM + (1 + (1 * speed));
          } else {
            LFO2toPWM = LFO2toPWM - (1 + (1 * speed));
          }
          LFO2toPWM = constrain(LFO2toPWM, 0, 511);
        }
        serial_send_param_change(ParamId::PARAM_LFO2_TO_PW, (uint16_t)LFO2toPWM);
        break;

      case ACTION_ADSR3_to_PWM:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            ADSR3toPWM = ADSR3toPWM + (1 + (1 * speed));
          } else {
            ADSR3toPWM = ADSR3toPWM - (1 + (1 * speed));
          }
          ADSR3toPWM = constrain(ADSR3toPWM, -512, 511);
        }
        serial_send_param_change(ParamId::PARAM_ADSR3_TO_PWM, (uint16_t)ADSR3toPWM + 512);
        break;

      case ACTION_ADSR_CURVE_ATTACK:
        {
          int a = 0;
          if (encoderActionIsSelected) {
            if (direction == DIR_CW) {
              a = 1;
            } else {
              a = -1;
            }
          }
          if (ADSR1CurveSelect == true) {
            ADSR1AttackCurveVal = constrain(ADSR1AttackCurveVal + a, 0, 7);
            serial_send_param_change_byte(ParamId::PARAM_ADSR1_ATTACK_CURVE, (uint8_t)ADSR1AttackCurveVal);
          } else if (ADSR2CurveSelect == true) {
            ADSR2AttackCurveVal = constrain(ADSR2AttackCurveVal + a, 0, 7);
            serial_send_param_change_byte(ParamId::PARAM_ADSR2_ATTACK_CURVE, (uint8_t)ADSR2AttackCurveVal);
          }
          break;
        }
      case ACTION_ADSR_CURVE_DECAY:
        {
          int a = 0;
          if (encoderActionIsSelected) {
            if (direction == DIR_CW) {
              a = 1;
            } else {
              a = -1;
            }
          }
          if (ADSR1CurveSelect == true) {
            ADSR1DecayCurveVal = constrain(ADSR1DecayCurveVal + a, 0, 7);
            serial_send_param_change_byte(ParamId::PARAM_ADSR1_DECAY_CURVE, (uint8_t)ADSR1DecayCurveVal);
          } else if (ADSR2CurveSelect == true) {
            ADSR2DecayCurveVal = constrain(ADSR2DecayCurveVal + a, 0, 7);
            serial_send_param_change_byte(ParamId::PARAM_ADSR2_DECAY_CURVE, (uint8_t)ADSR2DecayCurveVal);
          }
          break;
        }
      case ACTION_ANALOG_DETUNE:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            unisonDetune = unisonDetune + (1 + (0.5 * speed));
          } else {
            unisonDetune = unisonDetune - (1 + (1 * speed));
          }
          unisonDetune = constrain(unisonDetune, 0, 127);
        }
        serial_send_param_change_byte(ParamId::PARAM_UNISON_DETUNE, (uint8_t)unisonDetune);
        break;

      case ACTION_ANALOG_DRIFT:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            analogDrift = analogDrift + (1 + (0.5 * speed));
          } else {
            analogDrift = analogDrift - (1 + (1 * speed));
          }
          analogDrift = constrain(analogDrift, 0, 127);
        }
        serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_AMOUNT, (uint8_t)analogDrift);
        break;

      case ACTION_ANALOG_DRIFT_SPEED:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            analogDriftSpeed = analogDriftSpeed + (1 + (0.5 * speed));
          } else {
            analogDriftSpeed = analogDriftSpeed - (1 + (1 * speed));
          }
          analogDriftSpeed = constrain(analogDriftSpeed, 1, 255);
        }
        serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_SPEED, (uint8_t)analogDriftSpeed);
        break;

      case ACTION_ANALOG_DRIFT_SPREAD:
        if (encoderActionIsSelected) {
          if (direction == DIR_CW) {
            analogDriftSpread = analogDriftSpread + (1 + (0.5 * speed));
          } else {
            analogDriftSpread = analogDriftSpread - (1 + (1 * speed));
          }
          analogDriftSpread = constrain(analogDriftSpread, 1, 127);
        }
        serial_send_param_change_byte(ParamId::PARAM_ANALOG_DRIFT_SPREAD, (uint8_t)analogDriftSpread);
        break;

      case ACTION_select_preset:
        if (direction == DIR_CW) {
          presetSelectVal = presetSelectVal + (1 + (1 * speed));
        } else {
          presetSelectVal = presetSelectVal - (1 + (1 * speed));
        }
        if (presetSaveSelectMode) {
          presetSelectVal = constrain(presetSelectVal, 0, 255);

          // Update screen with selected preset name (16 chars)
          byte presetNameScroll[16];
          get_preset_name(presetSelectVal, presetNameScroll);
          serial_send_preset_scroll((uint8_t)presetSelectVal, presetNameScroll);
        } else {
          presetSelectVal = constrain(presetSelectVal, 0, 255);

          loadPreset(presetSelectVal);
          //serial_send_param_change_byte(141, presetSelectVal);
        }
        break;

      case ACTION_select_char:
        if (direction == DIR_CW) {
          charSelectVal = charSelectVal + 1;
        } else {
          charSelectVal = charSelectVal - 1;
        }
        charSelectVal = constrain(charSelectVal, 32, 255);
        presetNameVal[presetCharPos] = charSelectVal;
        serial_send_preset_scroll(presetSelectVal, presetNameVal);  // needs fix
        break;

      case ACTION_select_char_pos:
        if (direction == DIR_CW) {
          presetCharPos = presetCharPos + 1;
        } else {
          presetCharPos = presetCharPos - 1;
        }
        if (presetCharPos > 15) {
          presetCharPos = 0;
        }
        charSelectVal = presetNameVal[presetCharPos];
        serial_send_save_char_select(presetCharPos);
        break;

      case ACTION_CALIBRATION_STAGE:
        {
          if (direction == DIR_CW) {
            manualCalibrationStage = manualCalibrationStage + 1;
          } else {
            manualCalibrationStage = manualCalibrationStage - 1;
          }
          manualCalibrationStage = constrain(manualCalibrationStage, 0, 15);
          uint8_t index = (uint8_t)manualCalibrationStage / 2;
          serial_send_param_change_byte(ParamId::PARAM_MANUAL_CALIBRATION_STAGE, (uint8_t)manualCalibrationStage);
          serial_send_param_change_byte(ParamId::PARAM_MANUAL_CALIBRATION_OFFSET, (uint8_t)manualCalibrationInitAmpCompOffset[index]);
          break;
        }
      case ACTION_CALIBRATION_OFFSET:
        {
          uint8_t index = (uint8_t)manualCalibrationStage / 2;
          if (direction == DIR_CW) {
            manualCalibrationInitAmpCompOffset[index] = manualCalibrationInitAmpCompOffset[index] + 1;
          } else {
            manualCalibrationInitAmpCompOffset[index] = manualCalibrationInitAmpCompOffset[index] - 1;
          }
          manualCalibrationInitAmpCompOffset[index] = constrain(manualCalibrationInitAmpCompOffset[index], -15, 15);
          serial_send_param_change_byte(ParamId::PARAM_MANUAL_CALIBRATION_OFFSET, (uint8_t)manualCalibrationInitAmpCompOffset[index]);
        }
        break;

      case ACTION_MENU_POS:
        if (direction == DIR_CW) {
          menuPos = menuPos + 1;
        } else {
          menuPos = menuPos - 1;
        }
        menuPos = constrain(menuPos, 0, menuPosMax);
        serial_send_param_change_byte(ParamId::PARAM_UI_MENU_POSITION, (uint8_t)menuPos);  // menu position
        // switch (currentControlMode) {
        //   case CALIBRATION_MENU:
        // break;
        // }
        break;


        // case ACTION_calibration:

        //   if (direction == DIR_CW) {
        //     calibrationVal = calibrationVal + (1 + (0.5 * speed));
        //   } else {
        //     calibrationVal = calibrationVal - (1 + (0.5 * speed));
        //   }
        //   sendUint16(calibrationVal);
        //   serial_send_param_change(101, (uint16_t)calibrationVal);
        //   break;
    }
  }
}