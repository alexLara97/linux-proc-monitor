#include <sstream>

std::string buildJson(double cpu, double men, double temp) {
    std::ostringstream oss;

    oss << "{" 
        << "\"cpu\":" << cpu << ","
        << "\"mem\":" << men << ","
        << "\"temp\":" << temp
        << "}";
    return oss.str();
}