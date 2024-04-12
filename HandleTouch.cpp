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

#include "HandleTouch.hpp"

Cap1203 cap1203;

HandleTouch::HandleTouch() {
}

void HandleTouch::init() {
  is_ready_ = false;
  while (!is_ready_) {
    is_ready_ = cap1203.beginConnection();
  }
  cap1203.setCS1Enabled(true);
  cap1203.setCS2Enabled(false);
  cap1203.setCS3Enabled(false);
  cap1203.setNegativeDeltaCounts(0);  // disable negative delta count recalibration
  cap1203.setDIS_ANA_NOISE(true);
  cap1203.setDIS_RF_NOISE(true);
  cap1203.setSensitivity(SENSITIVITY_2X);
  cap1203.setThreshold(64);
  touch_threshold = cap1203.getThreshold();
}

void HandleTouch::updateThreshold(uint8_t threshold) {
  cap1203.setThreshold(threshold);
  touch_threshold = cap1203.getThreshold();
}

bool HandleTouch::updateSensitivity(uint8_t sensi) {
  uint8_t sensi_bit;
  if (sensi == 1) {
    sensi_bit = SENSITIVITY_1X;
  } else if (sensi == 2) {
    sensi_bit = SENSITIVITY_2X;
  } else if (sensi == 4) {
    sensi_bit = SENSITIVITY_4X;
  } else if (sensi == 8) {
    sensi_bit = SENSITIVITY_8X;
  } else if (sensi == 16) {
    sensi_bit = SENSITIVITY_16X;
  } else if (sensi == 32) {
    sensi_bit = SENSITIVITY_32X;
  } else if (sensi == 64) {
    sensi_bit = SENSITIVITY_64X;
  } else if (sensi == 128) {
    sensi_bit = SENSITIVITY_128X;
  } else {
    return false;
  }
  cap1203.setSensitivity(sensi_bit);
  return true;
}

void HandleTouch::update() {
  if (is_ready_) {
    is_touch = cap1203.isTouchCS1();
    touch_raw = cap1203.getDeltaCountCS1();
  } else {
    is_touch = false;
    touch_raw = -1;
  }
}
