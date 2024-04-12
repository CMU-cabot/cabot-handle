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
  public:
    HandleButtons();
    void init(uint8_t right, uint8_t left, uint8_t under, uint8_t top, uint8_t center);
    void update();
    uint8_t button_r_pin;
    uint8_t button_l_pin;
    uint8_t button_u_pin;
    uint8_t button_t_pin;
    uint8_t button_c_pin;
    bool is_push_r;
    bool is_push_l;
    bool is_push_u;
    bool is_push_t;
    bool is_push_c;
};

#endif  // HANDLEBUTTONS_HPP_
