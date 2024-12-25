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
    struct sockaddr_in serverAddress;
    const int bufferLength = MSG_SIZE;
};

class Client
{
private:
    sockaddr_in clientAddress, serverAddress;
    bool isRunning;
    int sockfd;
    int serverSocket;
    const int bufferLength;

public:
    Client(ClientSettings settings);
    virtual ~Client();
    void onWrite();
    void onRecieve();
};