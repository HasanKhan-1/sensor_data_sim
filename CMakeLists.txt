cmake_minimum_required(VERSION 3.10)
project(SensorSimulationSystem)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

find_file(DATA_LOGGER_H "data_logger.hpp" PATHS ${CMAKE_CURRENT_SOURCE_DIR}/include)
if (DATA_LOGGER_H)
    message("Found header file: ${DATA_LOGGER_H}")
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/sensor_simulator.cpp
    src/data_logger.cpp
    src/command_interface.cpp
)

# Create executable
add_executable(sensor_logger_simulator ${SOURCES})

# Link pthread for multithreading
find_package(Threads REQUIRED)
target_link_libraries(sensor_logger_simulator Threads::Threads)

INSTALL(TARGETS
    sensor_logger_simulator
    DESTINATION lib/${PROJECT_NAME}
)