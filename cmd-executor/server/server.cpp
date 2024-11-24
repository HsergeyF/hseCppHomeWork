#include "server.hpp"

namespace bp = boost::process;

Server::Server(ServerSettings settings) : bufferLength(settings.bufferLength)
{
    serverAddress = settings.serverAddress;

    establishSocketConnection(sockfd, serverAddress);

    if (listen(sockfd, 100) == -1)
        handleException("Listening failed:");

    isRunning = true;
};

void Server::handleConnection(int socket)
{
    std::cout << "New connection established" << std::endl;

    char command[bufferLength];
    memset(&command, 0, bufferLength);

    while (recv(socket, command, sizeof(command) - 1, 0) > 0)
    {
        execute(command, socket);
    }
}

void Server::writeToSocket(int socket, std::string message)
{
    if (write(socket, message.c_str(), sizeof(message)) == -1)
        handleException("Writing to socket failed:");
}

ExecutionResponse Server::execute(char *command, int socket)
{
    std::string execOutput;
    bp::ipstream output;
    bp::ipstream errorOutput;

    try
    {
        bp::child process(command, bp::std_out > output, bp::std_err > errorOutput);

        std::string execMessage = "Execution code: " + std::to_string(process.exit_code()) + "\n";

        writeToSocket(socket, execMessage);

        while (std::getline(process.exit_code() < 0 ? errorOutput : output, execOutput))
        {
            writeToSocket(socket, execOutput);
        }

        writeToSocket(socket, "\n");
    }
    catch (std::system_error e)
    {
        writeToSocket(socket, e.what());
    }
}

void Server::onResponse(sockaddr_in recieverAddress, std::string message)
{
    socklen_t len = sizeof recieverAddress;

    if (sendto(sockfd, (const char *)message.data(), strlen(message.data()),
               MSG_CONFIRM, (const struct sockaddr *)&recieverAddress,
               len) == -1)
        handleException("Send response failed:");
};

void Server::onNewConnection()
{
    int clientSocket;
    socklen_t clientLen;
    while (isRunning)
    {
        clientSocket = accept(sockfd, (struct sockaddr *)&serverAddress, &clientLen);
        std::thread handlingThread(&Server::handleConnection, this, clientSocket);
        handlingThread.detach();
    }
}

Server::~Server()
{
    isRunning = false;
    close(sockfd);
};
