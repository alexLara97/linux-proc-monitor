#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "SystemMonitor.h"
#include "utils/UdpSocketManager.h"
#include "utils/DataUtils.h"


int main() {
    // Socket implementation
    UdpSocketManager socket("127.0.0.1", 8888);
    // const char* message = "Hello from Alex'raspberry pi";

    while (true) {
        double cpu = getCPUUsage();
        double mem = getMemoryUsage();
        double temp = getCPUTemperature();

        std::cout << "\033[2J\033[1;1H" << std::endl;
        std::cout << "CPU Usage: " << cpu << "% | "
                  << "Memory Usage: " << mem << "% | "
                  << "CPU Temp: " << temp << "°C"
                  << std::endl;
        
        // Send info by udp socket
        std::string json = buildJson(cpu, mem, temp);
        socket.send(json);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    socket.closeSocket();
    return 0;
}
