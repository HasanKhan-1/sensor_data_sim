#ifndef COMMAND_INTERFACE_HPP
#define COMMAND_INTERFACE_HPP

#include <deque>
#include <mutex>
#include <atomic>

void command_interface(std::deque<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag);

#endif // COMMAND_INTERFACE_HPP