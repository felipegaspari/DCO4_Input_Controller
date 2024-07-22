void init_tables() {
  for (int i = 0; i < LIN_TO_EXP_TABLE_SIZE; i++) {
    linToExpLookup[i] = linearToExponential(i, 50, maxADSRControlValue);
  }
}