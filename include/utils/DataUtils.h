#ifndef UTILS_H
#define UTILS_H

#include <string>

std::string buildJson(double cpu, double men, double temp);
int socketUDPCreate(char* ip_address, uint16_t port);

#endif