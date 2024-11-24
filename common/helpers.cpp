#include "helpers.hpp"

struct sockaddr_in getSocketAddress(int port)
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

void establishSocketConnection(int &sockfd, struct sockaddr_in address, int streamType)
{
    if ((sockfd = socket(address.sin_family, streamType, 0)) < 0)
        handleException("Socket creation failed:");

    if (bind(sockfd, (const struct sockaddr *)&address, sizeof(address)) < 0)
        handleException("Binding failed:");
}

UDPChatInputArguments getInputArgs(int argc, char *argv[])
{
    option longopts[] = {
        {"client", required_argument, NULL, 'c'},
        {"reciever", required_argument, NULL, 'r'},
        {0}};

    UDPChatInputArguments arguments{};
    int opt;
    while ((opt = getopt(argc, argv, "c:r:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            arguments.clientPort = std::atoi(optarg);
            break;
        case 'r':
            arguments.recieverPort = std::atoi(optarg);
            break;
        }
    }
    return arguments;
}
