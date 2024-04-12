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

#define _TASK_TIMEOUT

#include <Arduino.h>
#include <TaskScheduler.h>  // https://github.com/arkhipenko/TaskScheduler.git
#include "HandleCommand.hpp"
#include "SerialQueue.hpp"

const int BAUDRATE = 115200;
const int RX_BUFF_LEN = 128;
const int SENSOR_UPDATE_DURATION_US = 10000;
unsigned int rx_data_count = 0;
static char temp_buffer[RX_BUFF_LEN];

Scheduler ts;

void readCommand();
void updateSensorData();
void sendSensorData();
void task_readCmdOnDisable();
void task_updateSensorDataOnDisable();

Task task_readCmd(TASK_IMMEDIATE, TASK_FOREVER, &readCommand, &ts, false, NULL, &task_readCmdOnDisable);
Task task_updateSensorData(10, TASK_ONCE, &updateSensorData, &ts, false, NULL, &task_updateSensorDataOnDisable);
Task task_sendSensorData(10, TASK_FOREVER, &sendSensorData, &ts, false, NULL, NULL);

SerialQueue rx_buffer = SerialQueue(RX_BUFF_LEN);
HandleCommand handleCommand;

void readCommand() {
  while (Serial1.available()) {
    rx_buffer.append(Serial1.read());
  }

  if (rx_buffer.count() > 0) {
    char data;
    while (rx_buffer.count() > 0) {
      data = rx_buffer.pop();
      if (data == '\n') {
        if (rx_data_count >= (RX_BUFF_LEN - 3)) {
          rx_data_count = 0;
          rx_buffer.clearBuffer();
        } else {
          temp_buffer[rx_data_count++] = '\r';
          temp_buffer[rx_data_count++] = '\n';
          temp_buffer[rx_data_count++] = '\0';
          Serial1.write(temp_buffer);
          handleCommand.parseCommand(temp_buffer);
          rx_data_count = 0;
        }
      } else if (data == '\r') {
        // nop
      } else {
        if (rx_data_count >= RX_BUFF_LEN) {
          rx_data_count = 0;
          rx_buffer.clearBuffer();
        } else {
          temp_buffer[rx_data_count++] = data;
        }
      }
    }
  }
}

void updateSensorData() {
  handleCommand.updateSensorData();
}

void sendSensorData() {
  handleCommand.sendSensorData();
  task_sendSensorData.delay(0);   // delay task for current execution interval (aInterval = 10msec)
}

void task_readCmdOnDisable() {
  if (task_readCmd.timedOut()) {
    rx_data_count = 0;
    memset(temp_buffer, '\0', sizeof(temp_buffer));
    rx_buffer.clearBuffer();
  }
  task_readCmd.enable();
}

void task_updateSensorDataOnDisable() {
  task_updateSensorData.setInterval(10);
  task_updateSensorData.setIterations(TASK_ONCE);
  task_updateSensorData.enable();
}

void setup() {
  memset(temp_buffer, '\0', sizeof(temp_buffer));
  handleCommand.init();
  Serial1.begin(BAUDRATE);
  while (!Serial1) {
  }
  delay(500);

  task_readCmd.setTimeout(10);
  ts.enableAll();
}

void loop() {
  ts.execute();
}
