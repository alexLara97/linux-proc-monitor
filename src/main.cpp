#include <iostream>
#include <thread>
#include <chrono>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "SystemMonitor.h"
#include "utils.h"


int main() {
    // Socket implementation
    int sock;
    struct sockaddr_in server_addr;
    const char* message = "Hello from Alex'raspberry pi";

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    

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
        int sent = sendto(sock, json.c_str(), json.size(), 0,
                      (struct sockaddr*)&server_addr, sizeof(server_addr));
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    close(sock);
    return 0;
}
