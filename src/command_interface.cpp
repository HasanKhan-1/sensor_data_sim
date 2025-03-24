#include "command_interface.hpp"
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>

const char* SOCKET_PATH = "/tmp/sensor_socket";

void command_interface(std::deque<double>& buffer,
                       std::mutex& mtx,
                       std::atomic<bool>& run_flag)
{
    int server_fd, client_fd;
    sockaddr_un addr;

    server_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        return;
    }

    unlink(SOCKET_PATH);
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCKET_PATH, sizeof(addr.sun_path)-1);

    if (bind(server_fd, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return;
    }

    listen(server_fd, 5);
    std::cout << "[Command Interface] Listening on " << SOCKET_PATH << "\n";

    while (run_flag.load()) {
        client_fd = accept(server_fd, nullptr, nullptr);
        if (client_fd < 0) {
            if (!run_flag.load()) break;
            perror("Accept failed");
            continue;
        }

        char buffer_recv[128] = {0};
        read(client_fd, buffer_recv, sizeof(buffer_recv));
        std::string command(buffer_recv);

        if (command == "GET") {
            std::lock_guard<std::mutex> lock(mtx);
            std::vector<double> readings;

            if (buffer.size() > 5) {
                readings.assign(buffer.end() - 5, buffer.end());
            } else {
                readings.assign(buffer.begin(), buffer.end());
            }

            std::ostringstream response;
            response << "Last " << readings.size() << " readings: ";
            for (const auto& reading : readings) {
                response << reading << " ";
            }

            std::string resp_str = response.str();
            write(client_fd, resp_str.c_str(), resp_str.size());
        } 
        else if (command == "STOP") {
            run_flag.store(false);
            const char* msg = "Simulation stopping.\n";
            write(client_fd, msg, strlen(msg));
        } 
        else {
            const char* msg = "Unknown command.\n";
            write(client_fd, msg, strlen(msg));
        }

        close(client_fd);
    }

    close(server_fd);
    unlink(SOCKET_PATH);
    std::cout << "[Command Interface] Shutting down.\n";
}