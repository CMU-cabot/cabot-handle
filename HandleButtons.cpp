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

void HandleButtons::init(uint8_t right, uint8_t left, uint8_t under, uint8_t top, uint8_t center) {
  button_r_pin = right;
  button_l_pin = left;
  button_u_pin = under;
  button_t_pin = top;
  button_c_pin = center;
  is_push_r = false;
  is_push_l = false;
  is_push_u = false;
  is_push_t = false;
  is_push_c = false;
  pinMode(button_r_pin, INPUT_PULLUP);
  pinMode(button_l_pin, INPUT_PULLUP);
  pinMode(button_u_pin, INPUT_PULLUP);
  pinMode(button_t_pin, INPUT_PULLUP);
  pinMode(button_c_pin, INPUT_PULLUP);
}

void HandleButtons::update() {
  is_push_r = !digitalRead(button_r_pin);
  is_push_l = !digitalRead(button_l_pin);
  is_push_u = !digitalRead(button_u_pin);
  is_push_t = !digitalRead(button_t_pin);
  is_push_c = !digitalRead(button_c_pin);
}
