#include "sensor_simulator.hpp"
#include <thread>
#include <chrono>
#include <random>

void temperature_simulator(std::deque<double>& buffer, std::mutex& mtx, std::atomic<bool>& run_flag) {
    // Random number generation setup
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-50.0, 150.0);

    while (run_flag.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Sleep for 500 milliseconds
        double new_temperature = dis(gen); 
        
        std::lock_guard<std::mutex> lock(mtx);
        buffer.push_back(new_temperature);
        if (buffer.size() > 100) { 
            buffer.pop_front();
        }
    }
}