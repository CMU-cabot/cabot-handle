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

#include <nRF52_MBED_PWM.h> // https://github.com/khoih-prog/nRF52_MBED_PWM
#include "HandleServo.hpp"

const int16_t SERVO_DEGREE_MIN     = -135;
const int16_t SERVO_DEGREE_MAX     = 135;
const uint16_t PULSE_WIDTH_MIN_US  = 700;
const uint16_t PULSE_WIDTH_MAX_US  = 2300;
const uint16_t PULSE_WIDTH_FREE_US = 50;
const float PWM_FREQ               = 50.0f;
const float PWM_CYCLE_US           = 1000000.0 / PWM_FREQ;

mbed::PwmOut* pwm = NULL;

HandleServo::HandleServo() {
}

void HandleServo::init(uint8_t servo_pin) {
  pwm_servo_pin = servo_pin;
  servo_pos = 0;
  pinMode(pwm_servo_pin, OUTPUT);
  digitalWrite(pwm_servo_pin, LOW);
  setPWM(pwm, pwm_servo_pin, PWM_FREQ, 7.5);  // set neutral position
}

void HandleServo::setServoPosition(int16_t pos) {
  if (pos < SERVO_DEGREE_MIN) {
    servo_pos = SERVO_DEGREE_MIN;
  } else if (pos > SERVO_DEGREE_MAX) {
    servo_pos = SERVO_DEGREE_MAX;
  } else {
    servo_pos = pos;
  }
  uint16_t pulse_us = degreeToPulse(servo_pos);
  float duty = pulseToDuty(pulse_us);
  setPWM(pwm, pwm_servo_pin, PWM_FREQ, duty);
}

void HandleServo::setServoFree() {
  float duty = pulseToDuty(PULSE_WIDTH_FREE_US);
  setPWM(pwm, pwm_servo_pin, PWM_FREQ, duty);
}

uint16_t HandleServo::degreeToPulse(int16_t degree) {
  return map(degree, SERVO_DEGREE_MIN, SERVO_DEGREE_MAX, PULSE_WIDTH_MIN_US, PULSE_WIDTH_MAX_US);
}

float HandleServo::pulseToDuty(uint16_t pulse) {
  return 100 * pulse / PWM_CYCLE_US;
}
