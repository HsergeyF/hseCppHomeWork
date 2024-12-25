#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include "helpers.hpp"

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
    Client(SharedClientSettings settings);
    virtual ~Client();
    void onWrite();
    void onRecieve();
};