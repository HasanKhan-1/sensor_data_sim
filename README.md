# Sensor Simulation System

## Overview

This project implements a sensor simulation system with the following components:
- **Sensor Device Simulator**: Generates random temperature readings every 500 milliseconds.
- **Data Logger**: Periodically writes sensor data to a log file every 2 seconds.
- **Command Interface**: Allows external interaction via a Unix socket, supporting `GET` and `STOP` commands.

## Requirements

- Requirements for each submodule:

1. Sensor Device Simulator:

- Runs in a separate thread and generates random temperature readings (e.g., between -50°C and 150°C) every 500 milliseconds.
The generated data should be stored in a shared buffer (e.g., a queue protected by a mutex).

2. Data Logger:
- Runs in another separate thread and periodically writes sensor data to a log file "sensor_log.txt" every 2 seconds.
It should append new readings without overwriting previous data.

3. Command Interface via Unix Socket:
- Listens on a socket "/tmp/sensor_socket"
- Accepts the following commands: 
  - GET: Returns the last five temperature readings
  - STOP: Stops the simulation gracefully
    
4. Bash Script for Automation:
- Compiles the program: Runs the test scenarios and summarize the results

## Build Instructions

1. Create a build directory:
   ```sh
   mkdir -p build
   ```
2. Go to the build folder
   ```sh
   cd build
   ```
3. Run the CMake
   ```sh
   cmake ..
   ```
4. Build project
   ```sh
   make ..
   ```
## Running the Program
1. To run the main program(simulates the data)
```sh
   ./sensor_logger_simulator
```
2. Open a new terminal and run this command after running the previous command for about 3 seconds
```sh
  ./scripts/test_commands.sh GET
```
3. Stopping the simulation data stream
```sh
  ./scripts/test_commands.sh STOP
```

## Automation Script
1. Run the automation script (Make sure that this is done after running sensor
```sh
  ./scripts/automation_script.sh
```
