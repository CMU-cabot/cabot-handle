/*******************************************************************************
 * Copyright (c) 2024  ALPS ALPINE CO., LTD.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *******************************************************************************/

#ifndef CAP1203_HPP_
#define CAP1203_HPP_

#include <Arduino.h>

#define CAP1203_PRODUCT_ID 0x6D
#define SENSITIVITY_128X 0x00
#define SENSITIVITY_64X 0x01
#define SENSITIVITY_32X 0x02
#define SENSITIVITY_16X 0x03
#define SENSITIVITY_8X 0x04
#define SENSITIVITY_4X 0x05
#define SENSITIVITY_2X 0x06
#define SENSITIVITY_1X 0x07

class Cap1203 {
  private:
    uint8_t readRegister(uint8_t reg);
    void writeRegister(uint8_t reg, uint8_t data);

  public:
    Cap1203();
    bool checkProdId();
    bool isTouchCS1();
    bool isTouchCS2();
    bool isTouchCS3();
    bool isTouch();
    uint8_t getThreshold();
    void setThreshold(uint8_t threshold);
    int8_t getDeltaCountCS1();
    int8_t getDeltaCountCS2();
    int8_t getDeltaCountCS3();
    void setSensitivity(uint8_t sensitivity);
    void setInterruptEnabled(uint8_t cs_channel, bool state);
    void setCS1Enabled(bool state);
    void setCS2Enabled(bool state);
    void setCS3Enabled(bool state);
    void setAveragingNumberOfSamples(uint8_t num_samples);
    void setAveragingSamplingTime(uint16_t samp_time_us);
    void setAveragingCycleTime(uint8_t cycle_time_ms);
    void setNegativeDeltaCounts(uint8_t counts);
    void setAutomaticRecalibNumberOfSamples(uint16_t num_samples, uint16_t update_time);
    void setCS1RepeatRateEnabled(bool state);
    void setCS2RepeatRateEnabled(bool state);
    void setCS3RepeatRateEnabled(bool state);
    void clearInterrupt();
    void setDIS_ANA_NOISE(bool state);
    void setDIS_RF_NOISE(bool state);
    bool beginConnection();
};

enum CAP1203_Register {
  // Registers
  MAIN_CONTROL = 0x00,
  GENERAL_STATUS = 0x02,
  SENSOR_INPUT_STATUS = 0x03,
  NOISE_FLAG_STATUS = 0x0A,
  SENSOR_INPUT_1_DELTA_COUNT = 0x10,
  SENSOR_INPUT_2_DELTA_COUNT = 0x11,
  SENSOR_INPUT_3_DELTA_COUNT = 0x12,
  SENSITIVITY_CONTROL = 0x1F,
  CONFIGURATION = 0x20,
  SENSOR_INPUT_ENABLE = 0x21,
  SENSOR_INPUT_CONFIGURATION = 0x22,
  SENSOR_INPUT_CONFIGURATION_2 = 0x23,
  AVERAGING_AND_SAMPLING_CONFIG = 0x24,
  CALIBRATION_ACTIVATE_AND_STATUS = 0x26,
  INTERRUPT_ENABLE = 0x27,
  REPEAT_RATE_ENABLE = 0x28,
  MULTIPLE_TOUCH_CONFIGURATION = 0x2A,
  MULTIPLE_TOUCH_PATTERN_CONFIGURATION = 0x2B,
  MULTIPLE_TOUCH_PATTERN = 0x2D,
  BASE_COUNT_OUT_OF_LIMIT = 0x2E,
  RECALIBRATION_CONFIGURATION = 0x2F,
  SENSOR_INPUT_1_THRESHOLD = 0x30,
  SENSOR_INPUT_2_THRESHOLD = 0x31,
  SENSOR_INPUT_3_THRESHOLD = 0x32,
  SENSOR_INPUT_NOISE_THRESHOLD = 0x38,
  // Standby Configuration Registers
  STANDBY_CHANNEL = 0x40,
  STANDBY_CONFIGURATION = 0x41,
  STANDBY_SENSITIVITY = 0x42,
  STANDBY_THRESHOLD = 0x43,
  CONFIGURATION_2 = 0x44,
  // Base Controll Registers
  SENSOR_INPUT_1_BASE_COUNT = 0x50,
  SENSOR_INPUT_2_BASE_COUNT = 0x51,
  SENSOR_INPUT_3_BASE_COUNT = 0x52,
  // Power Button Registers
  POWER_BUTTON = 0x60,
  POWER_BUTTON_CONFIGURATION = 0x61,
  // Caribration Registers
  SENSOR_INPUT_1_CALIBRATION = 0xB1,
  SENSOR_INPUT_2_CALIBRATION = 0xB2,
  SENSOR_INPUT_3_CALIBRATION = 0xB3,
  SENSOR_INPUT_CALIBRATION_LSB_1 = 0xB9,
  // ID Registers
  PRODUCT_ID = 0xFD,
  MANUFACTURER_ID = 0xFE,
  REVISION = 0xFF,
};

#endif  // CAP1203_HPP_
