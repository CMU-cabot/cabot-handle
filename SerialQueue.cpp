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

#include "SerialQueue.hpp"

SerialQueue::SerialQueue(uint16_t buff_size) {
  head = 0;
  tail = 0;
  counter = 0;
  max_length = buff_size;
  buff = new char[max_length + 1];
}

SerialQueue::~SerialQueue() {
  delete buff;
}

void SerialQueue::append(const char data) {
  if (counter < max_length) {
    buff[tail++] = data;
    counter++;
    if (tail == max_length) {
      tail = 0;
    }
  }
}

char SerialQueue::pop() {
  if (counter == 0) {
    return '\0';
  }
  char pop_data = buff[head++];
  counter--;
  if (head == max_length) {
    head = 0;
  }
  return pop_data;
}

uint16_t SerialQueue::count() {
  return counter;
}

void SerialQueue::clearBuffer() {
  delete buff;
  head = 0;
  tail = 0;
  buff = new char[max_length + 1];
}
