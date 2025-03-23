#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H
#include <queue>
#include <mutex>
#include <atomic>
#include <thread>
#include <string>

void command_interface(std::queue<double>& buffer, std::mutex& mutex, std::atomic<bool>& run_flag);

#endif // COMMAND_INTERFACE_H