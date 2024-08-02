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

#ifndef HANDLEBUTTONS_HPP_
#define HANDLEBUTTONS_HPP_

#include <Arduino.h>

class HandleButtons {
  private:
    uint8_t right_pin_;
    uint8_t left_pin_;
    uint8_t down_pin_;
    uint8_t up_pin_;
    uint8_t center_pin_;

  public:
    HandleButtons();
    void init(uint8_t right_pin, uint8_t left_pin, uint8_t down_pin, uint8_t up_pin, uint8_t center_pin);
    void update();
    bool is_push_right;
    bool is_push_left;
    bool is_push_down;
    bool is_push_up;
    bool is_push_center;
};

#endif  // HANDLEBUTTONS_HPP_
