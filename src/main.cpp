#include "command_interface.hpp"
#include "data_logger.hpp"
#include "sensor_simulator.hpp"
#include <iostream>
#include <thread>
#include <deque>
#include <mutex>
#include <atomic>

int main() {
    std::deque<double> buffer;
    std::mutex mtx;
    std::atomic<bool> run_flag{true};

    std::thread cmd_thread(command_interface, std::ref(buffer), std::ref(mtx), std::ref(run_flag));
    std::thread sensor_thread(temperature_simulator, std::ref(buffer), std::ref(mtx), std::ref(run_flag));
    std::thread logger_thread(data_logger, std::ref(buffer), std::ref(mtx), std::ref(run_flag));

    // Run for a certain amount of time
    // std::this_thread::sleep_for(std::chrono::seconds(10));

    // run_flag.store(false);
    cmd_thread.join();
    sensor_thread.join();
    logger_thread.join();

    std::cout << "Simulation ended.\n";
    return 0;
}