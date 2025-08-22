#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

struct CPUData {
    unsigned long long user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice;
};

CPUData readCPUStatus() {
    ifstream file("/proc/stat");
    string line;
    CPUData data{};
    
    if (file.is_open()) {
        getline(file, line);
        istringstream iss(line);
        string cpu;
        iss >> cpu >> data.user  >> data.nice >> data.system >> data.idle >> data.iowait 
            >> data.irq >> data.softirq >> data.steal >> data.guest >> data.guest_nice;
    }
    return data;
}

float calculateCPUUsage(const CPUData& prev, const CPUData& curr){
    unsigned long long prevIdle = prev.idle + prev.iowait;
    unsigned long long idle = curr.idle + curr.iowait;

    unsigned long long preNonIdle = prev.user + prev.nice + prev.system + prev.irq + prev.softirq + prev.steal;
    unsigned long long nonIdle = curr.user + curr.nice + curr.system + curr.irq + curr.softirq + curr.steal;
    unsigned long long prevTotal = prevIdle + preNonIdle;
    unsigned long long total = idle + nonIdle;

    unsigned long long totalDiff = total - prevTotal;
    unsigned long long idleDiff = idle - prevIdle;

    return (float)(totalDiff - idleDiff) / totalDiff * 100.0;
}

void printMemoryUsage() {
    ifstream file("/proc/meminfo");
    string key;
    unsigned long value;
    string unit;
    unsigned long memTotal = 0, memAvailable = 0;

    while (file >> key >> value >> unit) {
        if (key == "MemTotal:") memTotal = value;
        if (key == "MemAvailable:") {
            memAvailable = value;
            break;
        }
    }
    float memUsed = (float)(memTotal - memAvailable) / memTotal * 100.0;
    cout<<"Memory Usage: " << memUsed << "%" << endl;
}

int main() {
    CPUData prev = readCPUStatus();
    this_thread::sleep_for(chrono::seconds(1));
    CPUData curr = readCPUStatus();

    float cpuUsage = calculateCPUUsage(prev, curr);
    cout<<"CPU Usage: " << cpuUsage << "%" << endl;
    printMemoryUsage();

    return 0;
}