//1 VCFKeytrack
//2 ADSR2toVCF
//3 LFO1toVCF
//4 LFO2toVCF
//5 ADSR3toPWM
//6 LFO1toPWM
//7 LFO1toVCA
//8 ADSR1toVCA
//9 LFO1toDCO
//10 ADSR3toDETUNE1

void formula_update(byte formulaN) {
  switch (formulaN) {
    case 1:
      if (VCFKeytrack > 0) {
        VCFKeytrackModifier = (float)VCFKeytrack / 8000;
      } else {
        VCFKeytrackModifier = 1;
      }
      break;
    case 2:
      ADSR2toVCF_formula = (float)1 / 512 * ADSR2toVCF;
      break;
    case 3:
      LFO1toVCF_formula = (float)1 / 512 * LFO1toVCF;
      break;
    case 4:
      LFO2toVCF_formula = (float)1 / 512 * LFO2toVCF;
      break;
    case 5:
      ADSR3toPWM_formula = (float)1 / 512 * ADSR3toPWM;
      break;
    case 6:
      LFO1toPWM_formula = (float)1 / 512 * LFO1toPWM;
      break;
    case 7:
      LFO1toVCA_formula = (float)1 / 512 * LFO1toVCA;
      break;
    case 8:
      ADSR1toVCA_formula = (float)1 / 512 * ADSR1toVCA;
      break;
    case 9:
      LFO1toDCO_formula = (float)1 / 1080000 * LFO1toDCO;
      break;
    case 10:
      ADSR3toDETUNE1_formula = (float)1 / 1080000 * ADSR3toDETUNE1;
      break;
    case 11:
    LFO2toPWM_formula = (float)1 / 512 * LFO2toPWM;
    break;
  }
}

void controls_formula_update(byte formulaN) {
  switch (formulaN) {
    case 1:
      LFO1Speed = expConverterFloat(LFO1SpeedVal, 5000);
      //LFO1_class.setMode0Freq(LFO1Speed, micros());
      break;
          case 2:
      LFO2Speed = expConverterFloat(LFO2SpeedVal, 5000);
      //LFO2_class.setMode0Freq(LFO2Speed, micros());
      break;
      case 3:
      LFO1toDCO = expConverterFloat(LFO1toDCOVal, 500);
      break;
      case 4:
      LFO2toVCF = expConverter(LFO2toVCFVal, 500);
      break;
      case 31:
      LFO1toVCF = expConverter(LFO1toVCFVal, 500); // NO usar para pots (si son log), solo para encoder
      break;

  }
}