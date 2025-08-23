#include "SystemMonitor.h"
#include <fstream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>

double getCPUUsage() {
    static long long lastUser = 0, lastNice = 0, lastSystem = 0, lastIdle = 0;

    std::ifstream file("/proc/stat");
    std::string cpu;
    long long user, nice, system, idle;
    file >> cpu >> user >> nice >> system >> idle;

    long long diffUser = user - lastUser;
    long long diffNice = nice - lastNice;
    long long diffSystem = system - lastSystem;
    long long diffIdle = idle - lastIdle;

    lastUser = user;
    lastNice = nice;
    lastSystem = system;
    lastIdle = idle;

    long long total = diffUser + diffNice + diffSystem + diffIdle;
    double cpuUsage = 0.0;
    if (total > 0) {
        cpuUsage = (double)(diffUser + diffNice + diffSystem) * 100.0 / total;
    }

    return cpuUsage;
}

double getMemoryUsage() {
    std::ifstream file("/proc/meminfo");
    std::string key;
    long long memTotal = 0, memAvailable = 0;
    long long value;
    std::string unit;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") memTotal = value;
        if (key == "MemAvailable:") memAvailable = value;
    }

    if (memTotal == 0) return 0.0;

    return (double)(memTotal - memAvailable) * 100.0 / memTotal;
}

double getCPUTemperature() {
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    double tempC = 0.0;

    if (file.is_open()) {
        double millideg;
        file >> millideg;
        tempC = millideg / 1000.0;
    }

    return tempC;
}
