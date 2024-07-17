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

#ifndef HANDLEVIBRATOR_HPP_
#define HANDLEVIBRATOR_HPP_

#include <Arduino.h>

class HandleVibrator {
  private:
    uint8_t right_pin_;
    uint8_t center_pin_;
    uint8_t left_pin_;

  public:
    HandleVibrator();
    void init(uint8_t right_pin, uint8_t center_pin, uint8_t left_pin);
    void setVibratorState(uint8_t ch, uint8_t power);
    void stopAllVibrator();
    uint8_t powerToCount(uint8_t power);
    uint8_t power_right;
    uint8_t power_center;
    uint8_t power_left;
};

#endif  // HANDLEVIBRATOR_HPP_
