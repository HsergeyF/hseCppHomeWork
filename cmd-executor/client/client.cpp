#include "client.hpp"

Client::Client(ClientSettings settings) : bufferLength(settings.bufferLength)
{
    clientAddress = settings.clientAddress;
    serverAddress = settings.serverAddress;

    establishSocketConnection(sockfd, clientAddress);

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        handleException("Connection failed:");

    isRunning = true;
};

void Client::onWrite()
{
    std::string command;
    while (isRunning)
    {
        getline(std::cin, command);

        if (command == "/exit")
            close(sockfd);

        if (write(sockfd, command.c_str(), command.size()) == -1)
            handleException("Writing failed:");
    };
};

void Client::onRecieve()
{
    char response[bufferLength];
    while (read(sockfd, response, sizeof(response) - 1) > 0)
    {
        std::cout << response;
    }
};

Client::~Client()
{
    isRunning = false;
    close(sockfd);
};
