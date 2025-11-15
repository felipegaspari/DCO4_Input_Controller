// // Central parameter router for the Input Controller.
// //
// // This MCU is primarily a SOURCE of parameter changes (it sends 'p'/'w'
// // frames out to the mainboard and screen), but it can also receive parameters
// // in the future if we choose to route them here.
// //
// // The pattern is identical to the mainboard and DCO:
// //   - ParamId definitions live in params_def.h
// //   - apply_param_*() functions update local state
// //   - paramTable[] maps ParamId -> apply function
// //   - update_parameters() is the single entry point

// #include "param_router.h"

// using ParamValueT     = int16_t;             // 16-bit transport on this MCU
// using ParamDescriptor = ParamDescriptorT<ParamValueT>;

// // ---- Apply functions for parameters this MCU cares about ---------------

// // Voice mode (shared, ID 26)
// static void apply_param_voice_mode(ParamValueT v) {
//   voiceMode = (uint8_t)v;
// }

// // Unison detune (shared, ID 27)
// static void apply_param_unison_detune(ParamValueT v) {
//   unisonDetune = v;
// }

// // Analog drift amount/speed/spread (shared, IDs 28..30)
// static void apply_param_analog_drift_amount(ParamValueT v) {
//   analogDrift = v;
// }

// static void apply_param_analog_drift_speed(ParamValueT v) {
//   analogDriftSpeed = v;
// }

// static void apply_param_analog_drift_spread(ParamValueT v) {
//   analogDriftSpread = v;
// }

// // Portamento time/mode (shared, IDs 18,32)
// static void apply_param_portamento_time(ParamValueT v) {
//   portamentoTime = v;
// }

// static void apply_param_portamento_mode(ParamValueT v) {
//   portamentoMode = (uint8_t)v;
// }

// // Calibration value / flags (shared, IDs 25,150..153)
// static void apply_param_calibration_value(ParamValueT v) {
//   calibrationVal = v;
// }

// static void apply_param_calibration_flag(ParamValueT v) {
//   manualCalibration = (v != 0);
// }

// static void apply_param_manual_calibration_stage(ParamValueT v) {
//   manualCalibrationStage = (int8_t)v;
// }

// static void apply_param_manual_calibration_offset(ParamValueT v) {
//   // Store offsets per oscillator; details can be adjusted as needed.
//   uint8_t idx = (uint8_t)manualCalibrationStage;
//   if (idx < NUM_OSCILLATORS) {
//     manualCalibrationInitAmpCompOffset[idx] = (int8_t)v;
//   }
// }

// // ADSR curve parameters (shared IDs 48..51)
// static void apply_param_adsr1_attack_curve(ParamValueT v) {
//   ADSR1AttackCurveVal = (int8_t)v;
// }

// static void apply_param_adsr1_decay_curve(ParamValueT v) {
//   ADSR1DecayCurveVal = (int8_t)v;
// }

// static void apply_param_adsr2_attack_curve(ParamValueT v) {
//   ADSR2AttackCurveVal = (int8_t)v;
// }

// static void apply_param_adsr2_decay_curve(ParamValueT v) {
//   ADSR2DecayCurveVal = (int8_t)v;
// }

// // ADSR3 enable flag (ID 126)
// static void apply_param_adsr3_enabled(ParamValueT v) {
//   // On the input controller we can treat non-zero as "enabled";
//   // exact use depends on UI logic.
//   // (ADSR3Enabled global is defined on other MCUs; here we may mirror that
//   //  via local flags if needed.)
//   // For now, no extra state beyond what the UI already tracks.
//   (void)v;
// }

// // Function key (ID 127) – reserved / handled at higher UI level
// static void apply_param_function_key(ParamValueT /*v*/) {
//   // No-op here; actual behavior handled in higher-level UI code if needed.
// }

// // ---- Parameter table ----------------------------------------------------

// static const ParamDescriptor paramTable[] = {
//   { PARAM_VOICE_MODE,               apply_param_voice_mode               },
//   { PARAM_UNISON_DETUNE,            apply_param_unison_detune            },
//   { PARAM_ANALOG_DRIFT_AMOUNT,      apply_param_analog_drift_amount      },
//   { PARAM_ANALOG_DRIFT_SPEED,       apply_param_analog_drift_speed       },
//   { PARAM_ANALOG_DRIFT_SPREAD,      apply_param_analog_drift_spread      },

//   { PARAM_PORTAMENTO_TIME,          apply_param_portamento_time          },
//   { PARAM_PORTAMENTO_MODE,          apply_param_portamento_mode          },

//   { PARAM_CALIBRATION_VALUE,        apply_param_calibration_value        },
//   { PARAM_CALIBRATION_FLAG,         apply_param_calibration_flag         },
//   { PARAM_MANUAL_CALIBRATION_STAGE, apply_param_manual_calibration_stage },
//   { PARAM_MANUAL_CALIBRATION_OFFSET,apply_param_manual_calibration_offset},

//   { PARAM_ADSR1_ATTACK_CURVE,       apply_param_adsr1_attack_curve       },
//   { PARAM_ADSR1_DECAY_CURVE,        apply_param_adsr1_decay_curve        },
//   { PARAM_ADSR2_ATTACK_CURVE,       apply_param_adsr2_attack_curve       },
//   { PARAM_ADSR2_DECAY_CURVE,        apply_param_adsr2_decay_curve        },

//   { PARAM_ADSR3_ENABLED,            apply_param_adsr3_enabled            },
//   { PARAM_FUNCTION_KEY,             apply_param_function_key             },
// };

// static const size_t paramTableSize =
//   sizeof(paramTable) / sizeof(paramTable[0]);

// // Public entry point: can be called from Serial/MIDI/UI code
// // if this MCU ever needs to react to incoming parameters.
// inline void update_parameters(uint16_t rawId, ParamValueT value) {
//   param_router_apply<ParamValueT>(
//     paramTable,
//     paramTableSize,
//     rawId,
//     value
//   );
// }
