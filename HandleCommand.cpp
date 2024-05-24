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

// #define USE_USB_PORT

#define TX_DATA_SIZE 64

#include "HandleCommand.hpp"

const uint8_t vibrator_c_pin = 2;
const uint8_t vibrator_l_pin = 3;
const uint8_t vibrator_r_pin = 4;
const uint8_t button_l_pin   = 5;
const uint8_t button_r_pin   = 6;
const uint8_t button_u_pin   = 7;
const uint8_t button_t_pin   = 8;
const uint8_t pwm_servo_pin  = 9;
const uint8_t button_c_pin   = 10;

static char tx_data[TX_DATA_SIZE];
const char delimiter[2] = ",";
const uint8_t vibrator_num = 3;

HandleButtons   handleButtons;
HandleServo     handleServo;
HandleTouch     handleTouch;
HandleVibrator  handleVibrator;

HandleCommand::HandleCommand() {
}

void HandleCommand::init() {
  handleServo.init(pwm_servo_pin);
  handleButtons.init(button_r_pin,
                     button_l_pin,
                     button_u_pin,
                     button_t_pin,
                     button_c_pin);
  handleTouch.init();
  handleVibrator.init(vibrator_r_pin,
                      vibrator_c_pin,
                      vibrator_l_pin);
  is_send_start_ = true;
}

void HandleCommand::updateSensorData() {
  handleButtons.update();
  handleTouch.update();
}

void HandleCommand::sendSensorData() {
  if (is_send_start_) {
    snprintf(tx_data, TX_DATA_SIZE, "DAT,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
             handleTouch.is_touch,
             handleTouch.touch_raw,
             handleTouch.touch_threshold,
             handleVibrator.vib_power_r,
             handleVibrator.vib_power_c,
             handleVibrator.vib_power_l,
             handleButtons.is_push_t,
             handleButtons.is_push_u,
             handleButtons.is_push_l,
             handleButtons.is_push_r,
             handleButtons.is_push_c,
             handleServo.servo_pos);
    sendCommand(tx_data);
  }
}

void HandleCommand::parseCommand(char *command) {
  if (strncmp(command, "start", 5) == 0) {
    sendStart();
  } else if (strncmp(command, "stop", 4) == 0) {
    sendStop();
  } else if (strncmp(command, "reset", 5) == 0) {
    softReset();
  } else if (strncmp(command, "MOT,", 4) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    for (uint8_t i = 1; i <= vibrator_num; i++) {
      token = strtok(NULL, delimiter);
      if (token != nullptr) {
        power = strtol(token, NULL, 10);
        handleVibrator.setVibratorState(i, power);
      }
    }
  } else if (strncmp(command, "R,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      handleVibrator.setVibratorState(1, power);
    }
  } else if (strncmp(command, "C,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      handleVibrator.setVibratorState(2, power);
    }
  } else if (strncmp(command, "L,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      handleVibrator.setVibratorState(3, power);
    }
  } else if (strncmp(command, "THRESH,", 7) == 0) {
    char *token;
    uint8_t threshold;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      threshold = strtol(token, NULL, 10);
      handleTouch.updateThreshold(threshold);
    }
  } else if (strncmp(command, "SENSI,", 6) == 0) {
    char *token;
    uint8_t gain;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      gain = strtol(token, NULL, 10);
      if (!handleTouch.updateSensitivity(gain)) {
        Serial1.println("ERROR_SENSI\r\n");
      }
    }
  } else if (strncmp(command, "SERVO,", 6) == 0) {
    char *token;
    int16_t pos;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      pos = strtol(token, NULL, 10);
      if (pos == -999) {
        handleServo.setServoFree();
      } else {
        handleServo.setServoPosition(pos);
      }
    }
  } else {
    // nop
  }
}

void HandleCommand::sendCommand(char *tx_data) {
  #ifdef USE_USB_PORT
    Serial.write(tx_data);
  #else
  #endif
  Serial1.write(tx_data);
}

void HandleCommand::sendStart() {
  is_send_start_ = true;
}

void HandleCommand::sendStop() {
  is_send_start_ = false;
}

void HandleCommand::softReset() {
  NVIC_SystemReset(); 
}
