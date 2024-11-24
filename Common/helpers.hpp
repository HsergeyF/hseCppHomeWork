#pragma once
#include <netinet/in.h>
#include <string>
#include <getopt.h>

#define MSG_SIZE 256
#define MSG_CONFIRM 0

struct UDPChatInputArguments
{
    int clientPort;
    int recieverPort;
};

UDPChatInputArguments getInputArgs(int argc, char *argv[]);
struct sockaddr_in getSocketAddress(int port);
void handleException(std::string message);
void establishSocketConnection(int &sockfd, struct sockaddr_in address, int streamType = SOCK_STREAM);
