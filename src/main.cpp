#include <iostream>
#include <thread>
#include <chrono>
#include "SystemMonitor.h"

int main() {
    while (true) {
        double cpu = getCPUUsage();
        double mem = getMemoryUsage();
        double temp = getCPUTemperature();

        std::cout << "CPU Usage: " << cpu << "% | "
                  << "Memory Usage: " << mem << "% | "
                  << "CPU Temp: " << temp << "°C"
                  << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
