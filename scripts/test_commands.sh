#!/bin/bash

SOCKET="/tmp/sensor_socket"

send_command() {
    echo -n "$1" | socat - UNIX-CONNECT:$SOCKET
}

if [ -z "$1" ]; then
    echo "Usage: $0 <command>"
    echo "Commands:"
    echo "  GET  - Retrieve the last 5 temperature readings"
    echo "  STOP - Stop the simulation"
    exit 1
fi

COMMAND=$1
echo "Sending $COMMAND command:"
send_command "$COMMAND"
echo -e "\n"