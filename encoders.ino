void read_encoders() {
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

      if (presetSaveSelectMode) {
        if (presetSaveMode) {
          currentAction = actionArray[1];
        } else {
          currentAction = actionAltArray[1];
        }
      } else if (ADSR1CurveSelect == true || ADSR2CurveSelect == true) {
        currentAction = actionAltArray[2];
      } else if (funcKeyOn) {
        currentAction = actionAltArray[0];
      } else {
        currentAction = actionArray[0];
      }
    }

    switch (currentAction) {

      case ACTION_NONE:
        break;

      case ACTION_portamento_time:
        if (direction == DIR_CW) {
          portamentoTimeVal = portamentoTimeVal + (1 + (0.5 * speed));
        } else {
          portamentoTimeVal = portamentoTimeVal - (1 + (0.5 * speed));
        }
        portamentoTimeVal = constrain(portamentoTimeVal, 0, 255);
        portamentoTime = portamentoTimeVal;
        //serial_send_portamentoFlag = true;
        serial_send_param_change_byte(18, portamentoTime);
        break;

      case ACTION_LFO1_to_DCO:
        if (direction == DIR_CW) {
          LFO1toDCOVal = LFO1toDCOVal + (1 + (0.5 * speed));
        } else {
          LFO1toDCOVal = LFO1toDCOVal - (1 + (0.5 * speed));
        }

        LFO1toDCOVal = constrain(LFO1toDCOVal, 0, 511);
        controls_formula_update(3);
        serial_send_param_change(40, LFO1toDCOVal);

        //serial_send_LFO1toDCOFlag = true;  //DCO FM / LFO
        break;

      case ACTION_VCF_keytrack:
        if (direction == DIR_CW) {
          VCFKeytrackVal = VCFKeytrackVal + (1 + (0.5 * speed));
        } else {
          VCFKeytrackVal = VCFKeytrackVal - (1 + (0.5 * speed));
        }
        VCFKeytrackVal = constrain(VCFKeytrackVal, 0, 255);
        VCFKeytrack = VCFKeytrackVal;
        formula_update(1);
        serial_send_param_change_byte(19, VCFKeytrack);
        break;

      case ACTION_ADSR3_to_DETUNE1:
        if (direction == DIR_CW) {
          ADSR3toDETUNE1Val = ADSR3toDETUNE1Val + (1 + (1 * speed));
        } else {
          ADSR3toDETUNE1Val = ADSR3toDETUNE1Val - (1 + (1 * speed));
        }
        ADSR3toDETUNE1Val = constrain(ADSR3toDETUNE1Val, -511, 511);
        ADSR3toDETUNE1 = ADSR3toDETUNE1Val;
        //formula_update(10);
        //serialSendADSR3toDCOFlag = true;
        serial_send_param_change(47, ADSR3toDETUNE1);
        break;

      case ACTION_velocity_to_VCF:
        if (direction == DIR_CW) {
          velocityToVCFVal = velocityToVCFVal + 1;
        } else {
          velocityToVCFVal = velocityToVCFVal - 1;
        }
        velocityToVCFVal = constrain(velocityToVCFVal, 0, 20);
        velocityToVCF = (velocityToVCFVal)*0.0003935;
        serial_send_param_change_byte(20, velocityToVCFVal);
        break;

      case ACTION_velocity_to_VCA:
        if (direction == DIR_CW) {
          velocityToVCAVal = velocityToVCAVal + (1 + (1 * speed));
        } else {
          velocityToVCAVal = velocityToVCAVal - (1 + (1 * speed));
        }
        velocityToVCAVal = constrain(velocityToVCAVal, 0, 20);
        velocityToVCA = (velocityToVCAVal)*0.0003935;
        serial_send_param_change_byte(21, velocityToVCAVal);
        break;

      case ACTION_octave:
        if (direction == DIR_CW) {
          OSC1IntervalVal = OSC1IntervalVal + 12;
        } else {
          OSC1IntervalVal = OSC1IntervalVal - 12;
        }
        OSC1IntervalVal = constrain(OSC1IntervalVal, 0, 72);
        OSC1Interval = OSC1IntervalVal;
        serial_send_param_change_byte(13, OSC1Interval);  //Octave
        //serial_send_OSC1IntervalFlag = true;
        break;

      case ACTION_SQR1_level:
        if (direction == DIR_CW) {
          SQR1LevelVal = SQR1LevelVal + (1 + (1 * speed));
        } else {
          SQR1LevelVal = SQR1LevelVal - (1 + (1 * speed));
        }
        SQR1LevelVal = constrain(SQR1LevelVal, 0, 128);
        SQR1Level = 4096 - (SQR1LevelVal * 32);
        serial_send_param_change_byte(22, SQR1LevelVal);
        break;

      case ACTION_SQR2_level:
        if (direction == DIR_CW) {
          SQR2LevelVal = SQR2LevelVal + (1 + (1 * speed));
        } else {
          SQR2LevelVal = SQR2LevelVal - (1 + (1 * speed));
        }
        SQR2LevelVal = constrain(SQR2LevelVal, 0, 128);
        SQR2Level = 4096 - (SQR2LevelVal * 32);
        serial_send_param_change_byte(23, SQR2LevelVal);
        break;

      case ACTION_SUB_level:
        if (direction == DIR_CW) {
          SubLevelVal = SubLevelVal + (1 + (1 * speed));
        } else {
          SubLevelVal = SubLevelVal - (1 + (1 * speed));
        }
        SubLevelVal = constrain(SubLevelVal, 0, 128);
        SubLevel = 4096 - (SubLevelVal * 32);
        serial_send_param_change_byte(24, SubLevelVal);
        break;

      case ACTION_OSC2_interval:
        if (direction == DIR_CW) {
          OSC2IntervalVal = OSC2IntervalVal + 1;
        } else {
          OSC2IntervalVal = OSC2IntervalVal - 1;
        }
        OSC2IntervalVal = constrain(OSC2IntervalVal, 0, 48);
        OSC2Interval = OSC2IntervalVal;
        serial_send_param_change_byte(14, OSC2Interval);
        //serial_send_OSC2IntervalFlag = true;
        break;

      case ACTION_OSC2_detune:
        if (direction == DIR_CW) {
          OSC2DetuneVal = OSC2DetuneVal + (1 + (1 * speed));
        } else {
          OSC2DetuneVal = OSC2DetuneVal - (1 + (1 * speed));
        }
        OSC2DetuneVal = constrain(OSC2DetuneVal, 0, 512);
        OSC2Detune = OSC2DetuneVal;
        serial_send_param_change(15, OSC2Detune);
        break;

      case ACTION_LFO2_to_OSC2_detune:
        if (direction == DIR_CW) {
          LFO2toOSC2DETUNEVal = LFO2toOSC2DETUNEVal + (1 + (0.5 * speed));
        } else {
          LFO2toOSC2DETUNEVal = LFO2toOSC2DETUNEVal - (1 + (0.5 * speed));
        }
        LFO2toOSC2DETUNEVal = constrain(LFO2toOSC2DETUNEVal, 0, 255);
        LFO2toOSC2DETUNE = LFO2toOSC2DETUNEVal;
        serial_send_param_change_byte(16, LFO2toOSC2DETUNE);
        break;

      case ACTION_osc_sync_mode:
        if (direction == DIR_CW) {
          oscSyncModeVal = oscSyncModeVal + 1;
        } else {
          oscSyncModeVal = oscSyncModeVal - 1;
        }
        oscSyncModeVal = constrain(oscSyncModeVal, 0, 3);
        oscSyncMode = (byte)oscSyncModeVal;
        serial_send_oscSyncModeFlag = true;
        serial_send_param_change_byte(17, oscSyncMode);
        break;

      case ACTION_LFO1_speed:
        if (direction == DIR_CW) {
          LFO1SpeedVal = LFO1SpeedVal + (1 + (2 * speed));
        } else {
          LFO1SpeedVal = LFO1SpeedVal - (1 + (2 * speed));
        }
        LFO1SpeedVal = constrain(LFO1SpeedVal, 0, 4095);
        controls_formula_update(1);
        serial_send_param_change(41, LFO1SpeedVal);
        //serial_send_LFO1SpeedFlag = true;  // FM / DCO LFO
        break;

      case ACTION_LFO2_speed:
        if (direction == DIR_CW) {
          LFO2SpeedVal = LFO2SpeedVal + (1 + (2 * speed));
        } else {
          LFO2SpeedVal = LFO2SpeedVal - (1 + (2 * speed));
        }
        LFO2SpeedVal = constrain(LFO2SpeedVal, 0, 4095);
        controls_formula_update(2);
        serial_send_param_change(42, LFO2SpeedVal);
        break;

      case ACTION_VCA_level:
        if (direction == DIR_CW) {
          VCALevelVal = VCALevelVal + (2 + (5 * speed));
        } else {
          VCALevelVal = VCALevelVal - (2 + (5 * speed));
        }
        VCALevelVal = constrain(VCALevelVal, 0, 128);
        VCALevel = VCALevelVal * 32;
        serial_send_param_change_byte(43, VCALevelVal);
        break;

      case ACTION_LFO1_to_VCA:
        if (direction == DIR_CW) {
          LFO1toVCAVal = LFO1toVCAVal + (1 + (1 * speed));
        } else {
          LFO1toVCAVal = LFO1toVCAVal - (1 + (1 * speed));
        }
        LFO1toVCAVal = constrain(LFO1toVCAVal, 0, 1023);
        LFO1toVCA = LFO1toVCAVal;
        serial_send_param_change(44, LFO1toVCA);
        break;

      case ACTION_LFO2_to_PWM:
        if (direction == DIR_CW) {
          LFO2toPWMVal = LFO2toPWMVal + (1 + (1 * speed));
        } else {
          LFO2toPWMVal = LFO2toPWMVal - (1 + (1 * speed));
        }
        LFO2toPWMVal = constrain(LFO2toPWMVal, 0, 511);
        LFO2toPWM = LFO2toPWMVal;
        formula_update(10);
        serial_send_param_change(45, LFO2toPWM);
        break;

      case ACTION_ADSR3_to_PWM:
        if (direction == DIR_CW) {
          ADSR3toPWMVal = ADSR3toPWMVal + (1 + (1 * speed));
        } else {
          ADSR3toPWMVal = ADSR3toPWMVal - (1 + (1 * speed));
        }
        ADSR3toPWMVal = constrain(ADSR3toPWMVal, -512, 511);
        ADSR3toPWM = ADSR3toPWMVal;
        serial_send_param_change(46, ADSR3toPWM + 512);
        break;

      case ACTION_ADSR_CURVE_ATTACK:
        {
          int a = 0;
          if (direction == DIR_CW) {
            a = 1;
          } else {
            a = -1;
          }
          if (ADSR1CurveSelect == true) {
          ADSR1AttackCurveVal = constrain(ADSR1AttackCurveVal + a, 0, 7);
          serial_send_param_change_byte(48, (uint8_t)ADSR1AttackCurveVal);
          } else if (ADSR2CurveSelect == true) {
             ADSR2AttackCurveVal = constrain(ADSR2AttackCurveVal + a, 0, 7);
          serial_send_param_change_byte(50, (uint8_t)ADSR2AttackCurveVal);
          }
          break;
        }
      case ACTION_ADSR_CURVE_DECAY:
        {
          int a = 0;
          if (direction == DIR_CW) {
            a = 1;
          } else {
            a = -1;
          }
          if (ADSR1CurveSelect == true) {
          ADSR1DecayCurveVal = constrain(ADSR1DecayCurveVal + a, 0, 8);
          serial_send_param_change_byte(49, (uint8_t)ADSR1DecayCurveVal);
          } else if  (ADSR2CurveSelect == true) {
            ADSR2DecayCurveVal = constrain(ADSR2DecayCurveVal + a, 0, 8);
          serial_send_param_change_byte(51, (uint8_t)ADSR2DecayCurveVal);
          }
          break;
        }
      case ACTION_UNISON_DETUNE:
        if (direction == DIR_CW) {
          unisonDetune = unisonDetune + (1 + (0.5 * speed));
        } else {
          unisonDetune = unisonDetune - (1 + (1 * speed));
        }
        unisonDetune = constrain(unisonDetune, 0, 127);
        serial_send_param_change_byte(27, (uint8_t)unisonDetune);
        break;

      case ACTION_select_preset:
        if (direction == DIR_CW) {
          presetSelectVal = presetSelectVal + (1 + (1 * speed));
        } else {
          presetSelectVal = presetSelectVal - (1 + (1 * speed));
        }
        if (presetSaveSelectMode) {
          presetSelectVal = constrain(presetSelectVal, 0, 255);
          //load_preset_name(presetSelectVal);
          serial_send_param_change_byte(140, presetSelectVal);
        } else {
          presetSelectVal = constrain(presetSelectVal, 0, 255);
          loadPresetActions(presetSelectVal);
          serial_send_param_change_byte(141, presetSelectVal);
        }
        break;

      case ACTION_select_char:
        if (direction == DIR_CW) {
          charSelectVal = charSelectVal + 1;
        } else {
          charSelectVal = charSelectVal - 1;
        }
        charSelectVal = constrain(charSelectVal, 32, 255);
        presetNameVal[presetChar] = charSelectVal;
        serial_send_preset_scroll(presetSelectVal, presetNameVal);  // needs fix
        break;

      case ACTION_select_char_pos:
        if (direction == DIR_CW) {
          presetChar = presetChar + 1;
        } else {
          presetChar = presetChar - 1;
        }
        if (presetChar > 11) {
          presetChar = 0;
        }
        charSelectVal = presetNameVal[presetChar];
        serial_send_save_char_select(presetChar);
        break;

      case ACTION_calibration:

        if (direction == DIR_CW) {
          calibrationVal = calibrationVal + (1 + (0.5 * speed));
        } else {
          calibrationVal = calibrationVal - (1 + (0.5 * speed));
        }
        sendUint16(calibrationVal);
        serial_send_param_change(101, calibrationVal);
        break;
    }
  }
}