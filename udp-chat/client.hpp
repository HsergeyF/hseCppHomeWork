#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include "helpers.hpp"

struct ClientSettings
{
    struct sockaddr_in clientAddress;
    struct sockaddr_in recieverAddress;
    const int bufferLength = 1024;
};

class Client
{
private:
    sockaddr_in clientAddress, recieverAddress;
    bool isRunning;
    int sockfd;
    const int bufferLength;
    std::string userName;
    void setUserName();

public:
    Client(ClientSettings settings);
    virtual ~Client();
    void onWrite();
    void onRecieve();
};