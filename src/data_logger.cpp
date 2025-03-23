#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <filesystem> // Include filesystem for directory creation

/*THINGS TO UNDERSTAND:
    1. WHAT IS A atomic structure and what exactly is it besides a object the prevents race conditions? 
    2. What is a mutex and how does it work?
*/

using namespace std;

void data_logger(std::queue<double> & buffer, std::mutex& mutex, std::atomic<bool>& flagger){
    // Ensure the logs directory exists
    std::filesystem::path log_dir = "logs";
    if (!std::filesystem::exists(log_dir)) {
        if (!std::filesystem::create_directories(log_dir)) {
            std::cerr << "Failed to create logs directory" << std::endl;
            return;
        }
    }

    std::cout<<"DId I get here"<<std::endl
    std::ofstream logger_file(log_dir / "temperature_log.txt", std::ios::app); //REQUIRED: append mode (does not overwrite)

    if (!logger_file.is_open()){
        std::cerr << "Failed to open file" << std::endl;
        return;
    }

    while (flagger.load()){
        std::this_thread::sleep_for(std::chrono::seconds(2)); // REQUIRED: log every 2 seconds
        std::vector<double> readings;
        {
            std::lock_guard<std::mutex> lock(mutex);
            while (!buffer.empty()){
                readings.push_back(buffer.front());//REQUIRED: shared buffer
                buffer.pop();
            }
        }
        // OPTIONAL FEATURE: JSON FORMAT FOR LOGGER
        for (const auto & temp :readings){ // range based loop
            auto t = std::time(nullptr); // calendar time
            auto tm = *std::localtime(&t); // acc time

            logger_file << std::put_time(&tm, "%Y-%m-%d %H-%M-%S") << " - Temperature:" << temp << "C\n"; // fancier formatting in the output file :))
        } 
        logger_file.flush();
    }
    logger_file.close();
    std::cout << "Logger thread is closed \n";
}