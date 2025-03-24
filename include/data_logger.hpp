#ifndef DATA_LOGGER_HPP
#define DATA_LOGGER_HPP

#include <deque>
#include <mutex>
#include <atomic>

// Function declaration
void data_logger(std::deque<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag);

#endif // DATA_LOGGER_HPP