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

#include "HandleVibrator.hpp"

Haptic_Driver hapticDriver;
hapticSettings defaultHapticSettings;

HandleVibrator::HandleVibrator() {
}

void HandleVibrator::init(bool enable_da7280, uint8_t right_pin, uint8_t center_pin, uint8_t left_pin) {
  enable_da7280_ = enable_da7280;
  right_pin_ = right_pin;
  center_pin_ = center_pin;
  left_pin_ = left_pin;
  if (enable_da7280_) {
    init_da7280_(center_pin_);
  } else {
    pinMode(right_pin_, OUTPUT);
    pinMode(center_pin_, OUTPUT);
    pinMode(left_pin_, OUTPUT);
    analogWrite(right_pin_, 0);
    analogWrite(center_pin_, 0);
    analogWrite(left_pin_, 0);
  }
}

void HandleVibrator::init_da7280_(uint8_t vdd_pin) {
  power_center = 0;
  freq = 160;

  pinMode(vdd_pin, OUTPUT);
  digitalWrite(vdd_pin, LOW);
  delay(100);
  digitalWrite(vdd_pin, HIGH);

  is_da7280_ready_ = false;
  while (!is_da7280_ready_) {
    Wire.begin();
    is_da7280_ready_ = hapticDriver.begin(Wire);
    delay(100);
  }

  defaultHapticSettings.motorType = LRA_TYPE;
  defaultHapticSettings.nomVolt = 1.0;          // Nominal Voltage: 1.0V
  defaultHapticSettings.absVolt = 1.0;          // Absolute Voltage: 1.0V
  defaultHapticSettings.currMax = 100;          // Maximum Current: 100 mA
  defaultHapticSettings.impedance = 8;          // Channel Impedance: 8 Ohms
  defaultHapticSettings.lraFreq = 166;          // LRA Frequency: 166 Hz
  while (!hapticDriver.setMotor(defaultHapticSettings)) {
    delay(100);
  }

  hapticDriver.setOperationMode(DRO_MODE);
  hapticDriver.enableEmbeddedOperation(false);
  hapticDriver.enableFreqTrack(false);
  hapticDriver.enableAcceleration(false);
  hapticDriver.enableRapidStop(false);
  hapticDriver.enableV2iFactorFreeze(true);
  hapticDriver.enableDoubleRange(false);
  hapticDriver.setActuatorLRAfreq(160);
}

void HandleVibrator::setVibratorPower(uint8_t ch, uint8_t power) {
  if (power > 100) {
    stopAllVibrator();
  } else {
    if (ch == 1) {
      power_right = power;
      analogWrite(right_pin_, powerToCount(power_right));
    } else if (ch == 2) {
      power_center = power;
      analogWrite(center_pin_, powerToCount(power_center));
    } else if (ch == 3) {
      power_left = power;
      analogWrite(left_pin_, powerToCount(power_left));
    } else {
      stopAllVibrator();
    }
  }
}

void HandleVibrator::setVibratorPower(uint8_t power) {
  if (power > 100) {
    power_center = 0;
    hapticDriver.setVibratePower(0);
  } else {
    power_center = power;
    hapticDriver.setVibratePower(powerToCount(power));
  }
}

void HandleVibrator::setVibratorFreq(uint16_t freq) {
  if (freq < 50) {
    this->freq = 50;
  } else if (freq > 1000) {
    this->freq = 1000;
  } else {
    this->freq = freq;
    hapticDriver.setActuatorLRAfreq((float)freq);
  }
}

void HandleVibrator::stopAllVibrator() {
  power_right = 0;
  power_center = 0;
  power_left = 0;
  analogWrite(right_pin_, power_right);
  analogWrite(center_pin_, power_center);
  analogWrite(left_pin_, power_left);
}

uint8_t HandleVibrator::powerToCount(uint8_t power) {
  if (enable_da7280_) {
    return map(power, 0, 100, 0, 30);
  } else {
    return map(power, 0, 100, 0, 255);
  }
}
