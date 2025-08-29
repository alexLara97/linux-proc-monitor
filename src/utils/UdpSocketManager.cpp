#include "utils/UdpSocketManager.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

UdpSocketManager::UdpSocketManager(const char* ip_address, uint16_t port)
    : isInitialized(false)
{    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    destAddr.sin_addr.s_addr = inet_addr(ip_address);
}

UdpSocketManager::~UdpSocketManager() {
    closeSocket();
}

bool UdpSocketManager::send(const std::string& message) {
    if (!isInitialized) return false;
    ssize_t sent = sendto(sock, message.c_str(), message.size(), 0,
                          (struct sockaddr*)&destAddr, sizeof(destAddr));
    return sent >= 0;
}

void UdpSocketManager::closeSocket() {
    if (!isInitialized) {
        close(sock);
        isInitialized = false;
    }
}