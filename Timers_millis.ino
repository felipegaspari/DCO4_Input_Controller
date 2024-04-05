void millisTimer() {

  timer50microsFlag = 0;
  timer99microsFlag = 0;
  timer223microsFlag = 0;
  timer1msFlag = 0;
  timer2340microsFlag = 0;
  timer3543microsFlag = 0;
  timer5msFlag = 0;
  timer11msFlag = 0;
  timer23msFlag = 0;
  timer31msFlag = 0;
  timer67msFlag = 0;
    timer200msFlag = 0;
  //  timer500msFlag = 0;

  unsigned long currentMillis = millis();
  unsigned long currentMicros = micros();

  if ( currentMicros - timer50micros > 50) {
    timer50micros = currentMicros;
    timer50microsFlag = 1;
  }
  if ( currentMicros - timer99micros > 99) {
    timer99micros = currentMicros;
    timer99microsFlag = 1;
  }

  if ( currentMicros - timer223micros > 223) {
    timer223micros = currentMicros;
    timer223microsFlag = 1;
  }


  if ( currentMicros - timer1ms > 1001) {
    timer1ms = currentMicros;
    timer1msFlag = 1;
  }

  if ( currentMicros - timer2340micros > 2340) {
    timer2340micros = currentMicros;
    timer2340microsFlag = 1;
  }

  if ( currentMicros - timer3543micros > 3543) {
    timer3543micros = currentMicros;
    timer3543microsFlag = 1;
  }

  if ( currentMillis - timer5ms > 5) {
    timer5ms = currentMillis;
    timer5msFlag = 1;
  }

  if ( currentMillis - timer11ms > 11) {
    timer11ms = currentMillis;
    timer11msFlag = 1;
  }

  if ( currentMillis - timer23ms > 23) {
    timer23ms = currentMillis;
    timer23msFlag = 1;
  }

  if ( currentMillis - timer31ms > 31) {
    timer31ms = currentMillis;
    timer31msFlag = 1;
  }

  if ( currentMillis - timer67ms > 67) {
    timer67ms = currentMillis;
    timer67msFlag = 1;
  }

   if ( currentMillis - timer200ms > 200) {
     timer200ms = currentMillis;
     timer200msFlag = 1;
   }

  //    if ( currentMillis - timer500ms > 500) {
  //    timer500ms = currentMillis;
  //    timer500msFlag = 1;
  //  }

}

void millisTimer2() {

  timer50microsFlag2 = 0;
  timer99microsFlag2 = 0;
  timer223microsFlag2 = 0;
  timer1msFlag2 = 0;
  timer2340microsFlag2 = 0;
  timer3543microsFlag2 = 0;
  timer5msFlag2 = 0;
  timer11msFlag2 = 0;
  timer23msFlag2 = 0;
  timer31msFlag2 = 0;
  timer67msFlag2 = 0;
    timer200msFlag2 = 0;
  //  timer500msFlag2 = 0;

  unsigned long currentMillis2 = millis();
  unsigned long currentMicros2 = micros();

  if ( currentMicros2 - timer50micros2 > 50) {
    timer50micros2 = currentMicros2;
    timer50microsFlag2 = 1;
  }
  if ( currentMicros2 - timer99micros2 > 99) {
    timer99micros2 = currentMicros2;
    timer99microsFlag2 = 1;
  }

  if ( currentMicros2 - timer223micros2 > 223) {
    timer223micros2 = currentMicros2;
    timer223microsFlag2 = 1;
  }


  if ( currentMicros2 - timer1ms2 > 1001) {
    timer1ms2 = currentMicros2;
    timer1msFlag2 = 1;
  }

  if ( currentMicros2 - timer2340micros2 > 2340) {
    timer2340micros2 = currentMicros2;
    timer2340microsFlag2 = 1;
  }

  if ( currentMicros2 - timer3543micros2 > 3543) {
    timer3543micros2 = currentMicros2;
    timer3543microsFlag2 = 1;
  }

  if ( currentMillis2 - timer5ms2 > 5) {
    timer5ms2 = currentMillis2;
    timer5msFlag2 = 1;
  }

  if ( currentMillis2 - timer11ms2 > 11) {
    timer11ms2 = currentMillis2;
    timer11msFlag2 = 1;
  }

  if ( currentMillis2 - timer23ms2 > 23) {
    timer23ms2 = currentMillis2;
    timer23msFlag2 = 1;
  }

  if ( currentMillis2 - timer31ms2 > 31) {
    timer31ms2 = currentMillis2;
    timer31msFlag2 = 1;
  }

  if ( currentMillis2 - timer67ms2 > 67) {
    timer67ms2 = currentMillis2;
    timer67msFlag2 = 1;
  }

   if ( currentMillis2 - timer200ms2 > 200) {
     timer200ms2 = currentMillis2;
     timer200msFlag2 = 1;
   }

  //    if ( currentMillis2 - timer500ms2 > 500) {
  //    timer500ms2 = currentMillis2;
  //    timer500msFlag2 = 1;
  //  }

}

