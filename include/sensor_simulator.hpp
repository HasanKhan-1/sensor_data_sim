#ifndef SENS_DEVICE_SIM_H
#define SENS_DEVICE_SIM_H

#include <queue>
#include <mutex>
#include <atomic>

// Function declaration
void temperature_simulator(std::queue<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag);

#endif // SENS_DEVICE_SIM_H