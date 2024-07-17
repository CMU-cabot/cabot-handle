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

#include "HandleButtons.hpp"

HandleButtons::HandleButtons() {
}

void HandleButtons::init(uint8_t right_pin, uint8_t left_pin, uint8_t down_pin, uint8_t up_pin, uint8_t center_pin) {
  right_pin_ = right_pin;
  left_pin_ = left_pin;
  down_pin_ = down_pin;
  up_pin_ = up_pin;
  center_pin_ = center_pin;
  is_push_right = false;
  is_push_left = false;
  is_push_down = false;
  is_push_up = false;
  is_push_center = false;
  pinMode(right_pin_, INPUT_PULLUP);
  pinMode(left_pin_, INPUT_PULLUP);
  pinMode(down_pin_, INPUT_PULLUP);
  pinMode(up_pin_, INPUT_PULLUP);
  pinMode(center_pin_, INPUT_PULLUP);
}

void HandleButtons::update() {
  is_push_right = !digitalRead(right_pin_);
  is_push_left = !digitalRead(left_pin_);
  is_push_down = !digitalRead(down_pin_);
  is_push_up = !digitalRead(up_pin_);
  is_push_center = !digitalRead(center_pin_);
}
