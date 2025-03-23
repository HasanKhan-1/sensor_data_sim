#include "data_logger.hpp"
#include "sensor_simulator.hpp"

#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>


int main() {
    std::queue<double> buffer;
    std::mutex mtx;
    std::atomic<bool> run_flag{true};

    // Start sensor and logger threads
    std::thread sensor_thread(temperature_simulator, std::ref(buffer), std::ref(mtx), std::ref(run_flag));//REQUIRED: runs in a seperate thread
    std::thread logger_thread(data_logger, std::ref(buffer), std::ref(mtx), std::ref(run_flag));

    // Run for a specified duration (e.g., 10 seconds)
    std::this_thread::sleep_for(std::chrono::seconds(10));

    // Signal threads to stop and wait for them to finish
    run_flag.store(false);
    sensor_thread.join();
    logger_thread.join();

    std::cout << "Simulation ended. Data logged to temperature_log.txt\n";
    return 0;
}
