#ifndef DATA_LOGGER_H
#define DATA_LOGGER_H

#include <queue>
#include <mutex>
#include <atomic>

// Function declaration
void data_logger(std::queue<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag);

#endif // DATA_LOGGER_H