#ifndef __LED_CONTROL_H__
#define __LED_CONTROL_H__

#include <RoxMux.h>

Rox74HC595<2> LED_Control_Mux;

// pins for 74HC595
// #define PIN_DATA    PE_4 // pin 14 on 74HC595 (DATA)   / DS
// #define PIN_LATCH   PE_2  // pin 12 on 74HC595 (LATCH) / ST
// #define PIN_CLK     PE_3  // pin 11 on 74HC595 (CLK)   / SH

#define PIN_DATA 11       // pin 14 on 74HC595 (DATA)  / DS
#define PIN_LATCH 12      // pin 12 on 74HC595 (LATCH) / ST
#define PIN_CLK 13        // pin 11 on 74HC595 (CLK)   / SH
#define PIN_PWM -1

uint8_t LEDPins[16] ={5,4,3,2,1,0,7,6,11,12,9,10,8,8,8,8};

bool LEDBlink[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
#endif