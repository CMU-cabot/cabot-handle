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

void HandleVibrator::init(uint8_t vdd_pin) {
  this->power = 0;
  this->freq = 160;

  pinMode(vdd_pin, OUTPUT);
  digitalWrite(vdd_pin, LOW);
  delay(100);
  digitalWrite(vdd_pin, HIGH);

  is_ready_ = false;
  while (!is_ready_) {
    Wire.begin();
    is_ready_ = hapticDriver.begin(Wire);
    delay(100);
  }

  defaultHapticSettings.motorType = LRA_TYPE;
  defaultHapticSettings.nomVolt = 2.0;          // Nominal Voltage: 2.0V
  defaultHapticSettings.absVolt = 2.0;          // Absolute Voltage: 2.0V
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

void HandleVibrator::setVibratorPower(uint8_t power) {
  if (power > 100) {
    this->power = 0;
    hapticDriver.setVibratePower(0);
  } else {
    this->power = power;
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

uint8_t HandleVibrator::powerToCount(uint8_t power) {
  return map(power, 0, 100, 0, 30);
}
