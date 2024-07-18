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

static char tx_data[TX_DATA_SIZE];
const char delimiter[2] = ",";
const uint8_t vibrator_num = 3;

HandleButtons   handleButtons;
HandleServo     handleServo;
HandleTouch     handleTouch;
HandleVibrator  handleVibrator;

HandleCommand::HandleCommand() {
}

void HandleCommand::init(
    bool enable_da7280, uint8_t vib_right_pin, uint8_t vib_center_pin, uint8_t vib_left_pin,
    uint8_t btn_right_pin, uint8_t btn_left_pin, uint8_t btn_down_pin, uint8_t btn_up_pin, uint8_t btn_center_pin,
    uint8_t pwm_servo_pin) {
  handleServo.init(pwm_servo_pin);
  handleButtons.init(btn_right_pin, btn_left_pin, btn_down_pin, btn_up_pin, btn_center_pin);
  handleTouch.init();
  handleVibrator.init(enable_da7280, vib_right_pin, vib_center_pin, vib_left_pin);
  enable_da7280_ = enable_da7280;
  is_send_start_ = true;
}

void HandleCommand::updateSensorData() {
  handleButtons.update();
  handleTouch.update();
}

void HandleCommand::sendSensorData() {
  if (is_send_start_) {
    if (enable_da7280_) {
      snprintf(tx_data, TX_DATA_SIZE, "DAT,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
               handleTouch.is_touch,
               handleTouch.touch_raw,
               handleTouch.touch_threshold,
               handleVibrator.power_center,
               handleVibrator.power_center,
               handleVibrator.freq,
               handleButtons.is_push_up,
               handleButtons.is_push_down,
               handleButtons.is_push_left,
               handleButtons.is_push_right,
               handleButtons.is_push_center,
               handleServo.servo_pos);
    } else {
      snprintf(tx_data, TX_DATA_SIZE, "DAT,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\r\n", 
               handleTouch.is_touch,
               handleTouch.touch_raw,
               handleTouch.touch_threshold,
               handleVibrator.power_right,
               handleVibrator.power_center,
               handleVibrator.power_left,
               handleButtons.is_push_up,
               handleButtons.is_push_down,
               handleButtons.is_push_left,
               handleButtons.is_push_right,
               handleButtons.is_push_center,
               handleServo.servo_pos);
    }
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
  } else if ((strncmp(command, "FREQ,", 5) == 0) && enable_da7280_) {
    char *token;
    uint16_t freq;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      freq = strtol(token, NULL, 10);
      handleVibrator.setVibratorFreq(freq);
    }
  } else if (strncmp(command, "MOT,", 4) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    for (uint8_t i = 1; i <= vibrator_num; i++) {
      token = strtok(NULL, delimiter);
      if (token != nullptr) {
        power = strtol(token, NULL, 10);
        if (enable_da7280_) {
          handleVibrator.setVibratorPower(power);
        } else {
          handleVibrator.setVibratorPower(i, power);
        }
      }
    }
  } else if (strncmp(command, "R,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      if (enable_da7280_) {
        handleVibrator.setVibratorPower(power);
      } else {
        handleVibrator.setVibratorPower(1, power);
      }
    }
  } else if (strncmp(command, "C,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      if (enable_da7280_) {
        handleVibrator.setVibratorPower(power);
      } else {
        handleVibrator.setVibratorPower(2, power);
      }
    }
  } else if (strncmp(command, "L,", 2) == 0) {
    char *token;
    uint8_t power;
    token = strtok(command, delimiter);
    token = strtok(NULL, delimiter);
    if (token != nullptr) {
      power = strtol(token, NULL, 10);
      if (enable_da7280_) {
        handleVibrator.setVibratorPower(power);
      } else {
        handleVibrator.setVibratorPower(3, power);
      }
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
