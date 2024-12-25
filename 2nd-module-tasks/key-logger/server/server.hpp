#pragma once
#include <fstream>
#include <netinet/in.h>
#include <thread>
#include <iostream>
#include "helpers.hpp"

class Server
{
private:
    struct sockaddr_in serverAddress;
    int sockfd;
    std::string outputSource = "./tmp.txt";
    bool isRunning;
    void handleConnection(int socket);

public:
    Server(struct sockaddr_in address);
    void onNewConnection();
    virtual ~Server();
};