#ifndef __AUX_H__
#define __AUX_H__

#include <SimpleKalmanFilter.h>

static constexpr float e_mea = 30;  // Measurement Uncertainty 
static constexpr float e_est = 25;  // Estimation Uncertainty 
static constexpr float q_value = 0.02;    // Process Noise

static constexpr float e_mea_2 = 2;  // Measurement Uncertainty 
static constexpr float e_est_2 = 2;  // Estimation Uncertainty 
static constexpr float q_value_2 = 0.01;    // Process Noise

SimpleKalmanFilter simpleKalmanFilter[32] = {
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea, e_est, q_value),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
SimpleKalmanFilter(e_mea_2, e_est_2, q_value_2),
}; 

#define LIN_TO_EXP_TABLE_SIZE 4096
uint16_t linToExpLookup[LIN_TO_EXP_TABLE_SIZE];
uint16_t maxADSRControlValue = 25000;

float mapFloat(float x, float in_min, float in_max, float out_min,
               float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint16_t linearToExponential(uint16_t linearValue, float base, uint16_t maxValue) {

  if (linearValue < 0) linearValue = 0;
  if (linearValue > 4095) linearValue = 4095;


  float normalizedValue = (float)linearValue / 4095.0;


  float expValue = pow(base, normalizedValue) - 1;


  float maxExpValue = pow(base, 1.0) - 1;


  uint16_t scaledExpValue = (uint16_t)(expValue * (maxValue / maxExpValue));

  return scaledExpValue;
}

#endif
