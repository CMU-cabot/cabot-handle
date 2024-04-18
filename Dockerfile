FROM jpconstantineau/arduino-cli:0.33.0

RUN arduino-cli core update-index
RUN arduino-cli core install arduino:mbed_nano@4.1.1
RUN arduino-cli lib install "nRF52_MBED_PWM@1.0.3"
RUN arduino-cli lib install "TaskScheduler@3.7.0"
