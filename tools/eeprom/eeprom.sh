#!/bin/bash

print_usage() {
    echo "$0 read"
    echo "$0 write <ssid> <password> <hostname>"
    exit 1
}

if [ $# -ne 1 ] && [ $# -ne 4 ]; then
    print_usage
fi

if [ $1 = "write" ] && [ $# -eq 4 ]; then
    operation=EEPROM_WRITE
    ssid=$2
    password=$3
    hostname=$4
elif [ $1 = "read" ] && [ $# -eq 1 ]; then
    operation=EEPROM_READ
else
    print_usage
fi

PLATFORMIO_BUILD_FLAGS='-D'$operation' -DEEPROM_SSID=\"'$ssid'\" -DEEPROM_PASSWORD=\"'$password'\" -DEEPROM_HOSTNAME=\"'$hostname'\"' pio run -t upload
