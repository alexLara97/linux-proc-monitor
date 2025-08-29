#ifndef UDP_SOCKET_MANAGER_H
#define UDP_SOCKET_MANAGER_H

#include <string>
#include <netinet/in.h>

class UdpSocketManager {
public:
    UdpSocketManager(const std::string& ip_address, int port);
    ~UdpSocketManager();

    bool send(const std::string& message);
    void closeSocket();

private:
    int sock;
    struct sockaddr_in destAddr;
    bool isInitialized;
};

#endif