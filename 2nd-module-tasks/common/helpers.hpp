#pragma once
#include <netinet/in.h>
#include <string>
#include <getopt.h>

#define MSG_SIZE 256
#define MSG_CONFIRM 0

// #include <string.h>

struct SharedClientSettings
{
    struct sockaddr_in clientAddress;
    struct sockaddr_in recieverAddress;
    const int bufferLength = 1024;
};

struct PortsInputArguments
{
    int clientPort;
    int recieverPort;
};

PortsInputArguments getInputArgs(int argc, char *argv[]);
struct sockaddr_in getSocketAddress(int port);
void handleException(std::string message);
void establishSocketConnection(int &sockfd, struct sockaddr_in address, int streamType = SOCK_STREAM);
std::string findKeyboardDeviceNumber();
std::string getInputDevicePath();
