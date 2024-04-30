# Cabot-Handle

## Pre-requisites

### Hardware

- 3D print parts
- [Arduino Nano 33 BLE](https://store-usa.arduino.cc/products/arduino-nano-33-ble?selectedStore=us)
- [CAP1203](https://www.microchip.com/en-us/product/cap1203) capacitive touch sensor
- [DA7280](https://github.com/sparkfun/SparkFun_Qwiic_Haptic_Driver_DA7280_Arduino_Library) haptic driver
- 1 [servo](https://kondo-robot.com/product/03211)
- 1 [linear resonant actuator](https://tech.alpsalpine.com/e/products/detail/AFT14A903A/)
- 4 [push buttons](https://tech.alpsalpine.com/e/products/detail/SKRPABE010/)
- Conductive Material (ex. [Copper foil tape](https://www.adafruit.com/product/3483))
- Wires and headers

### Software (docker, arduino-cli)

```
  host $ docker-compose build
  host $ docker-compose run arduino
docker $ ./build.sh all                # build and upload (with -b arduino:mbed_nano:nano33ble -p /dev/ttyACM0)
                                       # you can set board by ARDUINO_BOARD, and port by ARDUINO_PORT environment variables

or use arduino-cli
docker $ arduino-cli compile -b arduino:mbed_nano:nano33ble .
docker $ arduino-cli upload -b arduino:mbed_nano:nano33ble -p /dev/ttyACM0 .
```
- change `-b <board type> -p <port>` for your environment
- linux is required to upload built sketch (Windows/Mac docker container does not support)
