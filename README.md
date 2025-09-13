# Linux Process Monitor  

A simple system monitoring tool for Linux.  
It displays **CPU usage, memory usage, and CPU temperature** in real time, using information read directly from the `/proc` and `/sys` filesystems.  

---

## Features  
- Show **CPU usage** in percentage  
- Show **Memory usage** in percentage  
- Show **CPU temperature** (via `/sys/class/thermal`)  
- Lightweight, written in **modern C++17**   
- Send system metrics as JSON via UDP to a configurable IP and port   

---

## Configuration  

The application reads its network settings from a configuration file located at `config/config.ini`.  
You can specify the destination IP and port for the JSON payload:

```ini
[network]
ip = 192.168.1.50
port = 8888
```
---

## Build Instructions  

### Requirements  
- Linux system  
- `g++` (C++17 or newer)  
- `cmake` (>= 3.10)  
- `make`  

### Build  
```bash
# Clone the repository
git clone https://github.com/alexLara97/linux-proc-monitor.git
cd linux-proc-monitor

# Create build directory
mkdir build && cd build

# Generate Makefiles and compile
cmake ..
make
```
### Run
```bash
./monitor
```