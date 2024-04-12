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

#include <Wire.h>
#include "Cap1203.hpp"

#define DEVICE_ADDR 0x28

Cap1203::Cap1203() {
}

bool Cap1203::checkProdId() {
  uint8_t rb = readRegister(PRODUCT_ID);
  if (rb == CAP1203_PRODUCT_ID) {
    return true;
  } else {
    return false;
  }
}

bool Cap1203::isTouchCS1() {
  uint8_t reg = readRegister(SENSOR_INPUT_STATUS);
  if ((reg & 0x01) == 0x01) {
    clearInterrupt();
    return true;
  } else {
    return false;
  }
}

bool Cap1203::isTouchCS2() {
  uint8_t reg = readRegister(SENSOR_INPUT_STATUS);
  if ((reg & 0x02) == 0x02) {
    clearInterrupt();
    return true;
  } else {
    return false;
  }
}

bool Cap1203::isTouchCS3() {
  uint8_t reg = readRegister(SENSOR_INPUT_STATUS);
  if ((reg & 0x04) == 0x04) {
    clearInterrupt();
    return true;
  } else {
    return false;
  }
}

bool Cap1203::isTouch() {
  uint8_t reg = readRegister(GENERAL_STATUS);
  if ((reg & 0x01) == 0x01) {
    clearInterrupt();
    return true;
  } else {
    return false;
  }
}

uint8_t Cap1203::getThreshold() {
  uint8_t rb = readRegister(SENSOR_INPUT_1_THRESHOLD);
  return rb;
}

void Cap1203::setThreshold(uint8_t threshold) {
  writeRegister(SENSOR_INPUT_1_THRESHOLD, threshold);
}

int8_t Cap1203::getDeltaCountCS1() {
  int8_t rb = readRegister(SENSOR_INPUT_1_DELTA_COUNT);
  return rb;
}

int8_t Cap1203::getDeltaCountCS2() {
  int8_t rb = readRegister(SENSOR_INPUT_2_DELTA_COUNT);
  return rb;
}

int8_t Cap1203::getDeltaCountCS3() {
  int8_t rb = readRegister(SENSOR_INPUT_3_DELTA_COUNT);
  return rb;
}

void Cap1203::setSensitivity(uint8_t sensitivity) {
  uint8_t sensi_ctrl_reg = 0x0F;
  if (sensitivity == SENSITIVITY_128X) {
    sensi_ctrl_reg |= (SENSITIVITY_128X << 4);
  } else if (sensitivity == SENSITIVITY_64X) {
    sensi_ctrl_reg |= (SENSITIVITY_64X << 4);
  } else if (sensitivity == SENSITIVITY_32X) {
    sensi_ctrl_reg |= (SENSITIVITY_32X << 4);
  } else if (sensitivity == SENSITIVITY_16X) {
    sensi_ctrl_reg |= (SENSITIVITY_16X << 4);
  } else if (sensitivity == SENSITIVITY_8X) {
    sensi_ctrl_reg |= (SENSITIVITY_8X << 4);
  } else if (sensitivity == SENSITIVITY_4X) {
    sensi_ctrl_reg |= (SENSITIVITY_4X << 4);
  } else if (sensitivity == SENSITIVITY_1X) {
    sensi_ctrl_reg |= (SENSITIVITY_1X << 4);
  } else {
    sensi_ctrl_reg |= (SENSITIVITY_2X << 4);
  }
  writeRegister(SENSITIVITY_CONTROL, sensi_ctrl_reg);
}

void Cap1203::setInterruptEnabled(uint8_t cs_channel, bool state) {
  uint8_t org = readRegister(INTERRUPT_ENABLE);
  uint8_t mask;
  if (cs_channel == 1) {
    mask = 0x01;
  } else if (cs_channel == 2) {
    mask = 0x02;
  } else if (cs_channel == 3) {
    mask = 0x04;
  } else {
    mask = 0x00;
  }
  if (state) {
    writeRegister(INTERRUPT_ENABLE, (org | mask));
  } else {
    writeRegister(INTERRUPT_ENABLE, (org & ~mask));
  }
}

void Cap1203::setCS1Enabled(bool state) {
  uint8_t org = readRegister(SENSOR_INPUT_ENABLE);
  if (state) {
    writeRegister(SENSOR_INPUT_ENABLE, (org | 0x01));
  } else {
    writeRegister(SENSOR_INPUT_ENABLE, (org & 0x06));
  }
}

void Cap1203::setCS2Enabled(bool state) {
  uint8_t org = readRegister(SENSOR_INPUT_ENABLE);
  if (state) {
    writeRegister(SENSOR_INPUT_ENABLE, (org | 0x02));
  } else {
    writeRegister(SENSOR_INPUT_ENABLE, (org & 0x05));
  }
}

void Cap1203::setCS3Enabled(bool state) {
  uint8_t org = readRegister(SENSOR_INPUT_ENABLE);
  if (state) {
    writeRegister(SENSOR_INPUT_ENABLE, (org | 0x04));
  } else {
    writeRegister(SENSOR_INPUT_ENABLE, (org & 0x03));
  }
}

void Cap1203::setAveragingNumberOfSamples(uint8_t num_samples) {
  uint8_t org = readRegister(AVERAGING_AND_SAMPLING_CONFIG);
  uint8_t mask = 0x0F;
  if (num_samples == 1) {
    mask |= 0x00;
  } else if (num_samples == 2) {
    mask |= 0x10;
  } else if (num_samples == 4) {
    mask |= 0x20;
  } else if (num_samples == 8) {
    mask |= 0x30;
  } else if (num_samples == 16) {
    mask |= 0x40;
  } else if (num_samples == 32) {
    mask |= 0x50;
  } else if (num_samples == 64) {
    mask |= 0x60;
  } else if (num_samples == 128) {
    mask |= 0x70;
  } else {
    mask |= 0x30; // default: 8
  }
  writeRegister(AVERAGING_AND_SAMPLING_CONFIG, (org & mask));
}

void Cap1203::setAveragingSamplingTime(uint16_t samp_time_us) {
  uint8_t org = readRegister(AVERAGING_AND_SAMPLING_CONFIG);
  uint8_t mask = 0x73;
  if (samp_time_us == 320) {
    mask |= 0x03;
  } else if (samp_time_us == 640) {
    mask |= 0x07;
  } else if (samp_time_us == 1280) {
    mask |= 0x0B;
  } else if (samp_time_us == 2560) {
    mask |= 0x0F;
  } else {
    mask |= 0x0B; // default: 1280us = 1.28msec
  }
  writeRegister(AVERAGING_AND_SAMPLING_CONFIG, (org & mask));
}

void Cap1203::setAveragingCycleTime(uint8_t cycle_time_ms) {
  uint8_t org = readRegister(AVERAGING_AND_SAMPLING_CONFIG);
  uint8_t mask = 0x7C;
  if (cycle_time_ms == 35) {
    mask |= 0x00;
  } else if (cycle_time_ms == 70) {
    mask |= 0x01;
  } else if (cycle_time_ms == 105) {
    mask |= 0x02;
  } else if (cycle_time_ms == 140) {
    mask |= 0x03;
  } else {
    mask |= 0x01; // default: 70msec
  }
  writeRegister(AVERAGING_AND_SAMPLING_CONFIG, (org & mask));
}

void Cap1203::setNegativeDeltaCounts(uint8_t counts) {
  uint8_t org = readRegister(RECALIBRATION_CONFIGURATION);
  uint8_t mask = 0xE7;
  if (counts == 8) {
    mask |= 0x00;
  } else if (counts == 16) {
    mask |= 0x08;
  } else if (counts == 32) {
    mask |= 0x10;
  } else if (counts == 0) {
    mask |= 0x18;
  } else {
    mask |= 0x08; // default: 16
  }
  writeRegister(RECALIBRATION_CONFIGURATION, (org & mask));
}

void Cap1203::setAutomaticRecalibNumberOfSamples(uint16_t num_samples, uint16_t update_time) {
  uint8_t org = readRegister(RECALIBRATION_CONFIGURATION);
  uint8_t mask = 0xF8;
  if ((num_samples == 16) && (update_time == 16)) {
    mask |= 0x00;
  } else if ((num_samples == 32) && (update_time == 32)) {
    mask |= 0x01;
  } else if ((num_samples == 64) && (update_time == 64)) {
    mask |= 0x02;
  } else if ((num_samples == 128) && (update_time == 128)) {
    mask |= 0x03;
  } else if ((num_samples == 256) && (update_time == 256)) {
    mask |= 0x04;
  } else if ((num_samples == 256) && (update_time == 1024)) {
    mask |= 0x05;
  } else if ((num_samples == 256) && (update_time == 2048)) {
    mask |= 0x06;
  } else if ((num_samples == 256) && (update_time == 4096)) {
    mask |= 0x07;
  } else {
    mask |= 0x02; // default: (num_samples, update_time) = (64, 64)
  }
  writeRegister(RECALIBRATION_CONFIGURATION, (org & mask));
}

void Cap1203::setCS1RepeatRateEnabled(bool state) {
  uint8_t org = readRegister(REPEAT_RATE_ENABLE);
  if (state) {
    writeRegister(REPEAT_RATE_ENABLE, (org | 0x01));
  } else {
    writeRegister(REPEAT_RATE_ENABLE, (org & 0x06));
  }
}

void Cap1203::setCS2RepeatRateEnabled(bool state) {
  uint8_t org = readRegister(REPEAT_RATE_ENABLE);
  if (state) {
    writeRegister(REPEAT_RATE_ENABLE, (org | 0x02));
  } else {
    writeRegister(REPEAT_RATE_ENABLE, (org & 0x05));
  }
}

void Cap1203::setCS3RepeatRateEnabled(bool state) {
  uint8_t org = readRegister(REPEAT_RATE_ENABLE);
  if (state) {
    writeRegister(REPEAT_RATE_ENABLE, (org | 0x04));
  } else {
    writeRegister(REPEAT_RATE_ENABLE, (org & 0x03));
  }
}

void Cap1203::clearInterrupt() {
  uint8_t org = readRegister(MAIN_CONTROL);
  writeRegister(MAIN_CONTROL, (org & 0xFE));
}

void Cap1203::setDIS_ANA_NOISE(bool state) {
  uint8_t org = readRegister(CONFIGURATION);
  if (state) {
    writeRegister(CONFIGURATION, (org | 0x10));
  } else {
    writeRegister(CONFIGURATION, (org & 0xEF));
  }
}

void Cap1203::setDIS_RF_NOISE(bool state) {
  uint8_t org = readRegister(CONFIGURATION_2);
  if (state) {
    writeRegister(CONFIGURATION_2, (org | 0x04));
  } else {
    writeRegister(CONFIGURATION_2, (org & 0xFB));
  }
}

uint8_t Cap1203::readRegister(uint8_t reg) {
  uint8_t rb = 0;
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(DEVICE_ADDR, 1);
  if (Wire.available()) {
    rb = Wire.read();
  }
  return rb;
}

void Cap1203::writeRegister(uint8_t reg, uint8_t data) {
  Wire.beginTransmission(DEVICE_ADDR);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

bool Cap1203::beginConnection() {
  Wire.begin();
  bool is_ready = checkProdId();
  return is_ready;
}
