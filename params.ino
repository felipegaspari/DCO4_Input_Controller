/*void update_parameters(byte paramNumber, uint16_t paramValue) {
  switch (paramNumber) {
    case 1:
      paramName = " OSC1 SAW";
      break;
    case 2:
      paramName = " OSC2 SAW";
      break;
    case 3:
      paramName = " OSC1 TRI";
      break;
    case 4:
      paramName = " OSC1 SIN";
      break;
    case 5:
      paramName = " OSC1 SQR";
      break;
    case 6:
      paramName = " OSC2 SQR";
      break;
    case 7:
      paramName = " ResoAmpComp";
      break;
    case 8:
      paramName = " ADSR1 Restart";
      break;
    case 9:
      paramName = " ADSR2 Restart";
      break;
    case 10:
      switch (paramValue) {
        case 0:
          paramName = " ADSR3 TO OSC1";
          break;
        case 1:
          paramName = " ADSR3 TO OSC2";
          break;
        case 2:
          paramName = " ADSR3 TO BOTH";
      }
      break;
    case 11:
      paramName = " LFO1 Shape";
      break;
    case 12:
      paramName = " LFO2 Shape";
      break;
    case 13:
      paramName = " Octave";
      paramValue = (paramValue - 36) / 12;
      break;
    case 14:
      paramName = " OSC2 Interval";
      paramValue -= 24;
      break;
    case 15:
      paramName = " OSC2 Detune";
      paramValue -= 127;
      break;
    case 16:
      paramName = " LFO2->OSC2 Pitch";
      break;
    case 17:
      paramName = " OscPhaseSync";
      break;
    case 18:
      paramName = " Portamento";
      break;
    case 19:
      paramName = " VCF Keytrack";
      break;
    case 20:
      paramName = " Velocity -> VCF";
      break;
    case 21:
      paramName = " Velocity -> VCA";
      break;
    case 22:
      paramName = " SQR1 Level";
      break;
    case 23:
      paramName = " SQR2 Level";
      break;
    case 24:
      paramName = " SUB Level";
      break;
    case 25:
      paramName = " CALIBRATION VAL";
      break;


    case 40:
      paramName = " LFO1 -> Pitch";
      break;
    case 41:
      paramName = " LFO1 Speed";
      break;
    case 42:
      paramName = " LFO2 Speed";
      break;
    case 43:
      paramName = " VCA -> LEVEL";
      break;
    case 44:
      paramName = " LFO1 -> VCA";
      break;
    case 45:
      paramName = " LFO2 -> PWM";
      break;
    case 46:
      paramName = " ADSR3 -> PWM";
      paramValue -= 512;
      break;
    case 47:
      paramName = " ADSR3 -> Pitch";
      break;
    case 48:
      paramName = " ADSR1 Curve";
      break;
    case 49:
      paramName = " ADSR2 Curve";
      break;

    case 126:
      paramName = " ADSR3 ENABLED";
      break;
    case 127:
      paramName = " FUNCTION KEY";
      break;


    case 101:
      paramName = " CALIB MODE";
      break;

    case 200:
      paramName = " VOICE MODE";
      break;
    case 201:
      paramName = " UNISON DETUNE";
      break;

    case 210:
      paramName = " PW";
      break;
    case 211:
      paramName = " LFO3 Speed";
      break;
    case 212:
      paramName = " LFO3 Shape";
      break;
    case 214:
      paramName = " ADSR3 Restart";
      break;
    case 215:
      paramName = " VCA -> LEVEL";
      break;

    default:
      break;
  }
}*/