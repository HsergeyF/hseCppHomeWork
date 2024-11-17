#pragma once
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>

#define MSG_CONFIRM 0

struct ClientSettings
{
    struct sockaddr_in client_address;
    struct sockaddr_in reciever_address;
    const int buffer_length = 1024;
};

class Client
{
private:
    sockaddr_in client_address, reciever_address;
    bool is_running;
    int sockfd;
    const int buffer_length;
    std::string user_name;
    void setUserName();

public:
    Client(ClientSettings settings);
    virtual ~Client();
    void onWrite();
    void onRecieve();
};