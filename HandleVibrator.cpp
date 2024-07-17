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

HandleVibrator::HandleVibrator() {
}

void HandleVibrator::init(uint8_t right_pin, uint8_t center_pin, uint8_t left_pin) {
  right_pin_ = right_pin;
  center_pin_ = center_pin;
  left_pin_ = left_pin;
  pinMode(right_pin_, OUTPUT);
  pinMode(center_pin_, OUTPUT);
  pinMode(left_pin_, OUTPUT);
  analogWrite(right_pin_, 0);
  analogWrite(center_pin_, 0);
  analogWrite(left_pin_, 0);
}

void HandleVibrator::setVibratorState(uint8_t ch, uint8_t power) {
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

void HandleVibrator::stopAllVibrator() {
  power_right = 0;
  power_center = 0;
  power_left = 0;
  analogWrite(right_pin_, power_right);
  analogWrite(center_pin_, power_center);
  analogWrite(left_pin_, power_left);
}

uint8_t HandleVibrator::powerToCount(uint8_t power) {
  return map(power, 0, 100, 0, 255);
}
