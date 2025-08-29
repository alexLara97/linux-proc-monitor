#include "utils/UdpSocketManager.h"
#include <iostream>
#include <arpa/inet.h>
#include <unistd.h>

UdpSocketManager::UdpSocketManager(const std::string& ip_address, int port)
    : isInitialized(false)
{    
   sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Error creando socket UDP\n";
        return;
    }

    destAddr.sin_family = AF_INET;
    destAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip_address.c_str(), &destAddr.sin_addr);
    isInitialized = true;
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