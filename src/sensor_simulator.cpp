#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <chrono>
#include <random>
#include <atomic>
#include <iomanip>  
#include <ctime>

using namespace std;

void temperature_simulator(std::queue<double>& buffer, std::mutex& mutex, std::atomic<bool>& flagger){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-50.00, 150.00);//REQUIRED: generate random numbers between -50 and 150

    while (flagger.load()) {
        double temp_reading = dist(gen);
        {
            std::lock_guard<std::mutex> lock(mutex);
            buffer.push(temp_reading);
            std::cout << "Sensor Generated Temperature: " << temp_reading << "°C\n";
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // REQUIRED generate every 500ms
    }
}