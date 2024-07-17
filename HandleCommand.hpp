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

#ifndef HANDLECOMMAND_HPP_
#define HANDLECOMMAND_HPP_

#include <Arduino.h>
#include <string.h>
#include <stdlib.h>

#include "HandleButtons.hpp"
#include "HandleServo.hpp"
#include "HandleTouch.hpp"
#include "HandleVibrator.hpp"

class HandleCommand {
  private:
    bool is_send_start_;

  public:
    HandleCommand();
    void init(
      uint8_t vib_right_pin, uint8_t vib_center_pin, uint8_t vib_left_pin,
      uint8_t btn_right_pin, uint8_t btn_left_pin, uint8_t btn_down_pin, uint8_t btn_up_pin, uint8_t btn_center_pin,
      uint8_t pwm_servo_pin);
    void updateSensorData();
    void sendSensorData();
    void parseCommand(char *command);
    void sendCommand(char *tx_data);
    void sendStart();
    void sendStop();
    void softReset();
};

#endif  // HANDLECOMMAND_HPP_
