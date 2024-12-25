#include "server.hpp"

Server::Server(struct sockaddr_in address) : serverAddress(address)
{
    establishSocketConnection(sockfd, serverAddress);

    if (listen(sockfd, 100) == -1)
        handleException("Listening failed:");

    isRunning = true;
}

void Server::onNewConnection()
{
    int clientSocket{};
    socklen_t clientLen{};
    while (isRunning)
    {
        clientSocket = accept(sockfd, (struct sockaddr *)&serverAddress, &clientLen);
        std::thread handlingThread(&Server::handleConnection, this, clientSocket);
        handlingThread.detach();
    }
}

void Server::handleConnection(const int socket)
{
    std::cout << "New connection established" << '\n';

    const int bufferLength = 256;
    char keyboardOutput[bufferLength];
    memset(&keyboardOutput, 0, bufferLength);
    std::fstream fs;
    fs.open(outputSource, std::ios_base::in | std::ios_base::out);
    // Всегда получаем один символ, не реализовал буфер.
    while (recv(socket, keyboardOutput, sizeof(keyboardOutput) - 1, 0) > 0)
    {
        fs << keyboardOutput;
        // TODO: fs.flush(); ?
    }
    fs.close();
}
Server::~Server()
{
    // TODO: check for automatically closable socket
    isRunning = false;
    close(sockfd);
};
