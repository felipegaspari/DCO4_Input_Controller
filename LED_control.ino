void init_LED_control() {
  pinMode(PIN_LATCH, OUTPUT);
  pinMode(PIN_DATA, OUTPUT);
  pinMode(PIN_CLK, OUTPUT);
  LED_Control_Mux.begin(PIN_DATA, PIN_LATCH, PIN_CLK, PIN_PWM);
  LED_Control_Mux.setBrightness(255);
  LED_Control_Mux.allOff();
}

void update_LED_Control(byte LEDPin, byte LEDStatus) {

  if (LEDPin == 16) {

    LED_Control_Mux.writePin(LEDPins[0], sawStatus);
    LED_Control_Mux.writePin(LEDPins[1], sqr1Status);
    LED_Control_Mux.writePin(LEDPins[2], triStatus);
    LED_Control_Mux.writePin(LEDPins[3], saw2Status);
    LED_Control_Mux.writePin(LEDPins[4], sqr2Status);
    LED_Control_Mux.writePin(LEDPins[5], 0);
    LED_Control_Mux.writePin(LEDPins[6], 0);
    LED_Control_Mux.writePin(LEDPins[7], VCFPotsControlManual);
    LED_Control_Mux.writePin(LEDPins[8], VCAPotsControlManual);
    LED_Control_Mux.writePin(LEDPins[9], PWMPotsControlManual);
    LED_Control_Mux.writePin(LEDPins[10], faderRow1ControlManual);
    LED_Control_Mux.writePin(LEDPins[11], faderRow2ControlManual);
    LED_Control_Mux.writePin(LEDPins[12], 0);
    LED_Control_Mux.writePin(LEDPins[13], 0);
    LED_Control_Mux.writePin(LEDPins[14], 0);
    LED_Control_Mux.writePin(LEDPins[15], 0);
  } else {
    LED_Control_Mux.writePin(LEDPin, LEDStatus);
  }
}