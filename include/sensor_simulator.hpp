#ifndef SENS_DEVICE_SIM_H
#define SENS_DEVICE_SIM_H

#include <deque>
#include <mutex>
#include <atomic>

// Function declaration
void temperature_simulator(std::deque<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag);

#endif // SENS_DEVICE_SIM_H