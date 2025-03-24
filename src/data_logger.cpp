#include "data_logger.hpp"
#include <fstream>
#include <thread>
#include <chrono>

void data_logger(std::deque<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag) {
    std::ofstream log_file("sensor_log.txt");
    while (run_flag.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        std::lock_guard<std::mutex> lock(mtx);
        if (!buffer.empty()) {
            log_file << buffer.back() << std::endl;
        }
    }
    log_file.close();
}