#!/bin/bash

# Set the project directory
PROJECT_DIR="/home/hasan/sensor_data_sim"

# Set the build directory
BUILD_DIR="$PROJECT_DIR/build"

# Set the log file
LOG_FILE="$BUILD_DIR/automation_log.txt"

# Create the build directory if it doesn't exist
mkdir -p $BUILD_DIR

# Navigate to the build directory
cd $BUILD_DIR

# Compile the program
echo "Compiling the program..."
cmake $PROJECT_DIR
make

# Check if the compilation was successful
if [ $? -ne 0 ]; then
    echo "Compilation failed. Exiting."
    exit 1
fi

# Run the program in the background
echo "Running the program..."
./sensor_logger_simulator &

# Give the program some time to start
sleep 2

# Run the test scenarios
echo "Running test scenarios..."

# Test GET command
echo "Testing GET command..."
GET_OUTPUT=$($PROJECT_DIR/scripts/test_commands.sh GET)
echo "$GET_OUTPUT" >> $LOG_FILE

# Test STOP command
echo "Testing STOP command..."
STOP_OUTPUT=$($PROJECT_DIR/scripts/test_commands.sh STOP)
echo "$STOP_OUTPUT" >> $LOG_FILE

# Wait for the program to stop
sleep 2

# Summarize the results
echo "Summarizing the results..."
echo "Automation Test Results:" > $LOG_FILE
echo "========================" >> $LOG_FILE
echo "" >> $LOG_FILE

echo "GET Command Output:" >> $LOG_FILE
echo "$GET_OUTPUT" >> $LOG_FILE
echo "" >> $LOG_FILE

echo "STOP Command Output:" >> $LOG_FILE
echo "$STOP_OUTPUT" >> $LOG_FILE
echo "" >> $LOG_FILE

echo "Automation script completed. Check the log file for details: $LOG_FILE"