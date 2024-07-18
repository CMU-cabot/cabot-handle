#!/bin/bash

function help() {
    echo "$0 [options] [build|upload|all]"
    echo ""
    echo "build         build the code (default action)"
    echo "upload        upload the code"
    echo "all           build and upload if build is success"
    echo ""
    echo "-h, --help    show this help"
    echo "-b            set board (default=arduino:mbed_nano:nano33ble)"
    echo "-p            set port (if port is blank, find Arduino Nano 33 BLE's port from board list)"
    echo "--lra         use Linear Resonant Actuator (LRA)"
}

: ${ARDUINO_BOARD:="arduino:mbed_nano:nano33ble"}
: ${ARDUINO_PORT:=""}
: ${ARDUINO_MODE:=""}

board=$ARDUINO_BOARD
port=$ARDUINO_PORT
mode=$ARDUINO_MODE

while getopts "hb:p:-:" arg; do
    case $arg in
    h)
        help
        exit
        ;;
    b)
        board=$OPTARG
        ;;
    p)
        port=$OPTARG
        ;;
    -)
        case "${OPTARG}" in
            help)
                help
                exit
                ;;
            lra)
                mode="USE_LINEAR_RESONANT_ACTUATOR"
                ;;
        esac
        ;;
    esac
done
shift $((OPTIND-1))

if [ -z $port ]; then
    port=$(arduino-cli board list | awk '/Arduino Nano 33 BLE/ { print $1 }')
fi

target=$1
if [ -z $target ]; then
    target=build
fi

function build() {
    if [ -z $mode ]; then
      echo "building for $board..."
      echo "arduino-cli compile -b $board ."
      arduino-cli compile -b $board .
    else
      echo "building for $board, $mode..."
      echo "arduino-cli compile -b $board --build-property build.extra_flags=-D$mode ."
      arduino-cli compile -b $board --build-property build.extra_flags=-D$mode .
    fi
}

function upload() {
    echo "uploading for $board at $port..."
    arduino-cli upload -b $board -p $port .
    while [ $? -ne 0 ]; do
	arduino-cli upload -b $board -p $port .
    done	
}    

if [ $target == "build" ]; then
    build
fi

if [ $target == "upload" ]; then
    upload
fi

if [ $target == "all" ]; then
    build && upload
fi
