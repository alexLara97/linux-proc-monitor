#include <iostream>
#include <fstream>

using namespace std;

struct CPUData {
    unsigned long long user, nice, system, idle, iowait, irq, softirp, steal, guest, guest_nice;
};

CPUData readCPUStats() {
    ifstream file("/proc/stat");
    string line;
    CPUData data{};
    
    if (file.is_open()) {
        getline(file, line)
        
    }
    
}
