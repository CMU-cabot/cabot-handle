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

void HandleVibrator::init(uint8_t pin_r, uint8_t pin_c, uint8_t pin_l) {
  vibrator_pin_r = pin_r;
  vibrator_pin_c = pin_c;
  vibrator_pin_l = pin_l;
  pinMode(vibrator_pin_r, OUTPUT);
  pinMode(vibrator_pin_c, OUTPUT);
  pinMode(vibrator_pin_l, OUTPUT);
  analogWrite(vibrator_pin_r, 0);
  analogWrite(vibrator_pin_c, 0);
  analogWrite(vibrator_pin_l, 0);
}

void HandleVibrator::setVibratorState(uint8_t ch, uint8_t power) {
  if (power > 100) {
    stopAllVibrator();
  }
  if (ch == 1) {
    vib_power_r = power;
    analogWrite(vibrator_pin_r, powerToCount(vib_power_r));
  } else if (ch == 2) {
    vib_power_c = power;
    analogWrite(vibrator_pin_c, powerToCount(vib_power_c));
  } else if (ch == 3) {
    vib_power_l = power;
    analogWrite(vibrator_pin_l, powerToCount(vib_power_l));
  } else {
    stopAllVibrator();
  }
}

void HandleVibrator::stopAllVibrator() {
  vib_power_r = 0;
  vib_power_c = 0;
  vib_power_l = 0;
  analogWrite(vibrator_pin_r, vib_power_r);
  analogWrite(vibrator_pin_c, vib_power_c);
  analogWrite(vibrator_pin_l, vib_power_l);
}

uint8_t HandleVibrator::powerToCount(uint8_t power) {
  return map(power, 0, 100, 0, 255);
}
