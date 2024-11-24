#include "client.hpp"

Client::Client(ClientSettings settings) : bufferLength(settings.bufferLength)
{
    setUserName();

    clientAddress = settings.clientAddress;

    recieverAddress = settings.recieverAddress;

    establishSocketConnection(sockfd, clientAddress, SOCK_DGRAM);

    isRunning = true;
};

void Client::setUserName()
{
    std::cout << "Type username: ";
    getline(std::cin, userName);
    if (userName.size() == 0)
        userName = "anon user";
}

void Client::onWrite()
{
    std::string message;
    socklen_t len = sizeof recieverAddress;

    while (isRunning)
    {
        getline(std::cin, message);
        message.insert(0, userName + ": ");
        if (sendto(sockfd, (const char *)message.data(), strlen(message.data()),
                   MSG_CONFIRM, (const struct sockaddr *)&recieverAddress,
                   len) == -1)
            handleException("Send to error:");
    };
};

void Client::onRecieve()
{
    char buffer[bufferLength];
    socklen_t len = sizeof recieverAddress;
    while (isRunning)
    {
        if (recvfrom(sockfd, (char *)buffer, bufferLength,
                     MSG_WAITALL, (struct sockaddr *)&recieverAddress,
                     &len) == -1)
            handleException("Recievefrom error:");
        std::cout << buffer << std::endl;
    }
};

Client::~Client()
{
    isRunning = false;
    close(sockfd);
};
