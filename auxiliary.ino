void init_aux() {
  for ( byte i = 0; i < 2; i++) {
    samples1.add(2048);
    samples2.add(2048);
    samples3.add(2048);
    samples4.add(2048);
    samples5.add(2048);
    samples6.add(2048);
    samples7.add(2048);
    samples8.add(2048);
    samples9.add(2048);
    samples10.add(2048);
    samples11.add(2048);
    samples12.add(2048);
    samples13.add(2048);
    samples14.add(2048);
    samples15.add(2048);
    samples16.add(2048);
  }
}

void medianFilter() {

  if  (timer23msFlag) {

    //    samples1.add(muxAnalogData[1]);
    //    samples2.add(muxAnalogData[3]);
    //    samples3.add(muxAnalogData[7]);
    //    samples4.add(muxAnalogData[5]);
    //    samples5.add(muxAnalogData[6]);
    //    samples6.add(muxAnalogData[0]);
    //    samples7.add(muxAnalogData[4]);
    //    samples8.add(muxAnalogData[2]);
    samples1.add(samples1.getQuantile(0.5));
    samples2.add(samples2.getQuantile(0.5));
    samples3.add(samples3.getQuantile(0.5));
    samples4.add(samples4.getQuantile(0.5));
    samples5.add(samples5.getQuantile(0.5));
    samples6.add(samples6.getQuantile(0.5));
    samples7.add(samples7.getQuantile(0.5));
    samples8.add(samples8.getQuantile(0.5));

    samples9.add(samples9.getQuantile(0.5));
    samples10.add(samples10.getQuantile(0.5));
    samples11.add(samples11.getQuantile(0.5));
    samples12.add(samples12.getQuantile(0.5));
    samples13.add(samples13.getQuantile(0.5));
    samples14.add(samples14.getQuantile(0.5));
    samples15.add(samples15.getQuantile(0.5));
    samples16.add(samples16.getQuantile(0.5));
    //
    //    samples1.add(samples1.getAverage(averagePosition));
    //    samples2.add(samples2.getAverage(averagePosition));
    //    samples3.add(samples3.getAverage(averagePosition));
    //    samples4.add(samples4.getAverage(averagePosition));
    //    samples5.add(samples5.getAverage(averagePosition));
    //    samples6.add(samples6.getAverage(averagePosition));
    //    samples7.add(samples7.getAverage(averagePosition));
    //    samples8.add(samples8.getAverage(averagePosition));



    //    muxAnalogData[1] = samples1.getMedian();
    //    muxAnalogData[3] = samples2.getMedian();
    //    muxAnalogData[7] = samples3.getMedian();
    //    muxAnalogData[5] = samples4.getMedian();
    //    muxAnalogData[6] = samples5.getMedian();
    //    muxAnalogData[0] = samples6.getMedian();
    //    muxAnalogData[4] = samples7.getMedian();
    //    muxAnalogData[2] = samples8.getMedian();
    //


    //    muxAnalogData[1] = samples1.getAverage(averagePosition);
    //    muxAnalogData[3] = samples2.getAverage(averagePosition);
    //    muxAnalogData[7] = samples3.getAverage(averagePosition);
    //    muxAnalogData[5] = samples4.getAverage(averagePosition);
    //    muxAnalogData[6] = samples5.getAverage(averagePosition);
    //    muxAnalogData[0] = samples6.getAverage(averagePosition);
    //    muxAnalogData[4] = samples7.getAverage(averagePosition);
    //    muxAnalogData[2] = samples8.getAverage(averagePosition);
    //
    //        samples1.add(muxAnalogData[1]);
    //        samples2.add(muxAnalogData[3]);
    //        samples3.add(muxAnalogData[7]);
    //        samples4.add(muxAnalogData[5]);
    //        samples5.add(muxAnalogData[6]);
    //        samples6.add(muxAnalogData[0]);
    //        samples7.add(muxAnalogData[4]);
    //        samples8.add(muxAnalogData[2]);
  }

  if  (timer11msFlag) {

    samples1.add(samples1.getQuantile(0.95));
    samples2.add(samples2.getQuantile(0.95));
    samples3.add(samples3.getQuantile(0.95));
    samples4.add(samples4.getQuantile(0.95));
    samples5.add(samples5.getQuantile(0.95));
    samples6.add(samples6.getQuantile(0.95));
    samples7.add(samples7.getQuantile(0.95));
    samples8.add(samples8.getQuantile(0.95));

    samples9.add(samples9.getQuantile(0.95));
    samples10.add(samples10.getQuantile(0.95));
    samples11.add(samples11.getQuantile(0.95));
    samples12.add(samples12.getQuantile(0.95));
    samples13.add(samples13.getQuantile(0.95));
    samples14.add(samples14.getQuantile(0.95));
    samples15.add(samples15.getQuantile(0.95));
    samples16.add(samples16.getQuantile(0.95));

    //    samples1.add(samples1.getAverage(averagePosition));
    //    samples2.add(samples2.getAverage(averagePosition));
    //    samples3.add(samples3.getAverage(averagePosition));
    //    samples4.add(samples4.getAverage(averagePosition));
    //    samples5.add(samples5.getAverage(averagePosition));
    //    samples6.add(samples6.getAverage(averagePosition));
    //    samples7.add(samples7.getAverage(averagePosition));
    //    samples8.add(samples8.getAverage(averagePosition));



    //      muxAnalogData[1] = samples1.getMedian();
    //      muxAnalogData[3] = samples2.getMedian();
    //      muxAnalogData[7] = samples3.getMedian();
    //      muxAnalogData[5] = samples4.getMedian();
    //      muxAnalogData[6] = samples5.getMedian();
    //      muxAnalogData[0] = samples6.getMedian();
    //      muxAnalogData[4] = samples7.getMedian();
    //      muxAnalogData[2] = samples8.getMedian();

    //          samples1.add(muxAnalogData[1]);
    //    samples2.add(muxAnalogData[3]);
    //    samples3.add(muxAnalogData[7]);
    //    samples4.add(muxAnalogData[5]);
    //    samples5.add(muxAnalogData[6]);
    //    samples6.add(muxAnalogData[0]);
    //    samples7.add(muxAnalogData[4]);
    //    samples8.add(muxAnalogData[2]);


  }

  if  (timer3543microsFlag) {
//if  (timer5msFlag) {

    //        muxAnalogData[1] = samples1.getMedian();
    //        muxAnalogData[3] = samples2.getMedian();
    //        muxAnalogData[7] = samples3.getMedian();
    //        muxAnalogData[5] = samples4.getMedian();
    //        muxAnalogData[6] = samples5.getMedian();
    //        muxAnalogData[0] = samples6.getMedian();
    //        muxAnalogData[4] = samples7.getMedian();
    //        muxAnalogData[2] = samples8.getMedian();

    analogMedian[0] = samples1.getQuantile(quantile);
    analogMedian[1] = samples2.getQuantile(quantile);
    analogMedian[2] = samples3.getQuantile(quantile);
    analogMedian[3] = samples4.getQuantile(quantile);
    analogMedian[4] = samples5.getQuantile(quantile);
    analogMedian[5] = samples6.getQuantile(quantile);
    analogMedian[6] = samples7.getQuantile(quantile);
    analogMedian[7] = samples8.getQuantile(quantile);

    analogMedian[8] = samples9.getQuantile(quantile);
    analogMedian[9] = samples10.getQuantile(quantile);
    analogMedian[10] = samples11.getQuantile(quantile);
    analogMedian[11] = samples12.getQuantile(quantile);
    analogMedian[12] = samples13.getQuantile(quantile);
    analogMedian[13] = samples14.getQuantile(quantile);
    analogMedian[14] = samples15.getQuantile(quantile);
    analogMedian[15] = samples16.getQuantile(quantile);

    //        muxAnalogData[1] = samples1.getAverage(averagePosition);
    //    muxAnalogData[3] = samples2.getAverage(averagePosition);
    //    muxAnalogData[7] = samples3.getAverage(averagePosition);
    //    muxAnalogData[5] = samples4.getAverage(averagePosition);
    //    muxAnalogData[6] = samples5.getAverage(averagePosition);
    //    muxAnalogData[0] = samples6.getAverage(averagePosition);
    //    muxAnalogData[4] = samples7.getAverage(averagePosition);
    //    muxAnalogData[2] = samples8.getAverage(averagePosition);

    samples1.add(analogMedian[0]);
    samples2.add(analogMedian[1]);
    samples3.add(analogMedian[2]);
    samples4.add(analogMedian[3]);
    samples5.add(analogMedian[4]);
    samples6.add(analogMedian[5]);
    samples7.add(analogMedian[6]);
    samples8.add(analogMedian[7]);

    samples9.add(analogMedian[8]);
    samples10.add(analogMedian[9]);
    samples11.add(analogMedian[10]);
    samples12.add(analogMedian[11]);
    samples13.add(analogMedian[12]);
    samples14.add(analogMedian[13]);
    samples15.add(analogMedian[14]);
    samples16.add(analogMedian[15]);


  }



  if  (timer1msFlag) {

    samples1.add(muxAnalogData[0]);
    samples2.add(muxAnalogData[1]);
    samples3.add(muxAnalogData[2]);
    samples4.add(muxAnalogData[3]);
    samples5.add(muxAnalogData[4]);
    samples6.add(muxAnalogData[5]);
    samples7.add(muxAnalogData[6]);
    samples8.add(muxAnalogData[7]);

    samples9.add(muxAnalogData[8]);
    samples10.add(muxAnalogData[9]);
    samples11.add(muxAnalogData[10]);
    samples12.add(muxAnalogData[11]);
    samples13.add(muxAnalogData[12]);
    samples14.add(muxAnalogData[13]);
    samples15.add(muxAnalogData[14]);
    samples16.add(muxAnalogData[15]);


//        analogMedian[1] = samples1.getQuantile(quantile);
//    analogMedian[3] = samples2.getQuantile(quantile);
//    analogMedian[7] = samples3.getQuantile(quantile);
//    analogMedian[5] = samples4.getQuantile(quantile);
//    analogMedian[6] = samples5.getQuantile(quantile);
//    analogMedian[0] = samples6.getQuantile(quantile);
//    analogMedian[4] = samples7.getQuantile(quantile);
//    analogMedian[2] = samples8.getQuantile(quantile);

//    muxAnalogData[1] = samples1.getQuantile(quantile);
//    muxAnalogData[3] = samples2.getQuantile(quantile);
//    muxAnalogData[7] = samples3.getQuantile(quantile);
//    muxAnalogData[5] = samples4.getQuantile(quantile);
//    muxAnalogData[6] = samples5.getQuantile(quantile);
//    muxAnalogData[0] = samples6.getQuantile(quantile);
//    muxAnalogData[4] = samples7.getQuantile(quantile);
//    muxAnalogData[2] = samples8.getQuantile(quantile);


    // ESTO FUNCIONABA
    //    muxAnalogData[1] = samples1.getAverage(averagePosition);
    //    muxAnalogData[3] = samples2.getAverage(averagePosition);
    //    muxAnalogData[7] = samples3.getAverage(averagePosition);
    //    muxAnalogData[5] = samples4.getAverage(averagePosition);
    //    muxAnalogData[6] = samples5.getAverage(averagePosition);
    //    muxAnalogData[0] = samples6.getAverage(averagePosition);
    //    muxAnalogData[4] = samples7.getAverage(averagePosition);
    //    muxAnalogData[2] = samples8.getAverage(averagePosition);
  }
}
