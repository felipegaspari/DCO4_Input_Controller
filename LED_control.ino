void init_LED_control() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  LED_Control_Mux.begin(PIN_DATA, PIN_LATCH, PIN_CLK, -1);
  LED_Control_Mux.setBrightness(20);
  LED_Control_Mux.allOff();
}

void set_LED_Status(byte LEDNumber, byte LEDStatus) {

  if (LEDNumber == 16) {

    LEDState[0] = sawStatus;
    LEDState[1] = sqr1Status;
    LEDState[2] = triStatus;
    LEDState[3] = saw2Status;
    LEDState[4] = sqr2Status;
    LEDState[5] = 0;
    LEDState[6] = 0;
    LEDState[7] = VCFPotsControlManual;
    LEDState[8] = VCAPotsControlManual;
    LEDState[9] = PWMPotsControlManual;
    LEDState[10] = faderRow1ControlManual;
    LEDState[11] = faderRow2ControlManual;
    LEDState[12] = 0;
    LEDState[13] = 0;
    LEDState[14] = 0;
    LEDState[15] = 0;

    update_LED_Control(16, 0);

  } else {
    LEDState[LEDNumber] = LEDState;
    update_LED_Control(LEDNumber, LEDStatus);
  }
}

void update_LED_Control(byte LEDnumber, byte LEDStatus) {

  if (LEDnumber == 16) {

    LED_Control_Mux.writePin(LEDPins[0], LEDState[0]);
    LED_Control_Mux.writePin(LEDPins[1], LEDState[1]);
    LED_Control_Mux.writePin(LEDPins[2], LEDState[2]);
    LED_Control_Mux.writePin(LEDPins[3], LEDState[3]);
    LED_Control_Mux.writePin(LEDPins[4], LEDState[4]);
    LED_Control_Mux.writePin(LEDPins[5], LEDState[5]);
    LED_Control_Mux.writePin(LEDPins[6], LEDState[6]);
    LED_Control_Mux.writePin(LEDPins[7], LEDState[7]);
    LED_Control_Mux.writePin(LEDPins[8], LEDState[8]);
    LED_Control_Mux.writePin(LEDPins[9], LEDState[9]);
    LED_Control_Mux.writePin(LEDPins[10], LEDState[10]);
    LED_Control_Mux.writePin(LEDPins[11], LEDState[11]);
    LED_Control_Mux.writePin(LEDPins[12], LEDState[12]);
    LED_Control_Mux.writePin(LEDPins[13], LEDState[13]);
    LED_Control_Mux.writePin(LEDPins[14], LEDState[14]);
    LED_Control_Mux.writePin(LEDPins[15], LEDState[15]);
  } else {
    LED_Control_Mux.writePin(LEDPins[LEDnumber], LEDStatus);
  }
}