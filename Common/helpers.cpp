#include "helpers.hpp"

struct sockaddr_in get_socket_address(int port)
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // Hint: if using external ip address, implement passing ip_adress via args
    // address.sin_addr.s_addr = inet_addr(args.ip_adress);
    address.sin_port = htons(port);
    return address;
};

void handleException(std::string message)
{
    perror(message.c_str());
    exit(EXIT_FAILURE);
};

void establishSocketConnection(int &sockfd, struct sockaddr_in address)
{
    if ((sockfd = socket(address.sin_family, SOCK_STREAM, 0)) < 0)
        handleException("Socket creation failed:");

    if (bind(sockfd, (const struct sockaddr *)&address, sizeof(address)) < 0)
        handleException("Binding failed:");
}