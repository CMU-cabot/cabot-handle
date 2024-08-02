FROM jpconstantineau/arduino-cli:0.33.0

RUN arduino-cli core update-index
RUN arduino-cli core install arduino:mbed_nano@4.1.1
RUN arduino-cli lib install "nRF52_MBED_PWM@1.0.3"
RUN arduino-cli lib install "TaskScheduler@3.7.0"
ENV ARDUINO_LIBRARY_ENABLE_UNSAFE_INSTALL=true
RUN arduino-cli lib install --git-url https://github.com/KenichiroSameshima/SparkFun_Qwiic_Haptic_Driver_DA7280_Arduino_Library
