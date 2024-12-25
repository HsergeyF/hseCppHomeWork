#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <thread>
#include "boost/process.hpp"
#include "helpers.hpp"

#define MSG_CONFIRM 0

struct ServerSettings
{
    struct sockaddr_in serverAddress;
    const int bufferLength = 1024;
};
struct ExecutionResponse
{
    int executionCode;
    boost::process::ipstream &output;
};

class Server
{
private:
    sockaddr_in serverAddress;
    bool isRunning;
    int sockfd;
    const int bufferLength;
    ExecutionResponse execute(char *command, int socket);
    void handleConnection(int socket);
    void writeToSocket(int socket, std::string message);

public:
    Server(ServerSettings settings);
    virtual ~Server();
    void onResponse(sockaddr_in recieverAddress, std::string message);
    void onNewConnection();
};