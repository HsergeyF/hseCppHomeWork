#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <fcntl.h>
#include "helpers.hpp"

class Client
{
private:
    sockaddr_in clientAddress, serverAddress;
    bool isRunning;
    int sockfd;
    int serverSocket;
    std::string devicePath;

public:
    Client(SharedClientSettings settings);
    virtual ~Client();
    void run();
};