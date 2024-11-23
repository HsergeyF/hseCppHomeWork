#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include "../../Common/helpers.hpp"

#define MSG_CONFIRM 0

struct ClientSettings
{
    struct sockaddr_in client_address;
    struct sockaddr_in server_address;
    const int buffer_length = MSG_SIZE;
};

class Client
{
private:
    sockaddr_in client_address, server_address;
    bool is_running;
    int sockfd;
    int server_socket;
    const int buffer_length;

public:
    Client(ClientSettings settings);
    virtual ~Client();
    void onWrite();
    void onRecieve();
};