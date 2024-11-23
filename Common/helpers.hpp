#pragma once
#include <netinet/in.h>
#include <string>

#define MSG_SIZE 256
#define MSG_CONFIRM 0

struct sockaddr_in get_socket_address(int port);
void handleException(std::string message);
void establishSocketConnection(int &sockfd, struct sockaddr_in address);
