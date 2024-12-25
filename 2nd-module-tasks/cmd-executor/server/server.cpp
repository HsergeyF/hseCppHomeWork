#include "server.hpp"

// TODO: specify what boost methods will be used
// TODO: make method args const where needed

Server::Server(ServerSettings settings) : bufferLength(settings.bufferLength)
{
    serverAddress = settings.serverAddress;

    establishSocketConnection(sockfd, serverAddress);

    if (listen(sockfd, 100) == -1)
        handleException("Listening failed:");

    isRunning = true;
};

void Server::handleConnection(const int socket)
{
    std::cout << "New connection established" << '\n';

    char command[bufferLength];
    memset(&command, 0, bufferLength);

    while (recv(socket, command, sizeof(command) - 1, 0) > 0)
    {
        execute(command, socket);
    }
}

void Server::writeToSocket(const int socket, const std::string message)
{
    if (write(socket, message.c_str(), sizeof(message)) == -1)
        handleException("Writing to socket failed:");
}

ExecutionResponse Server::execute(const char *command, const int socket)
{
    std::string execOutput{};
    boost::process::ipstream output;
    boost::process::ipstream errorOutput;

    try
    {
        boost::process::child process(command, boost::process::std_out > output,
                                      boost::process::std_err > errorOutput);

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
    int clientSocket{};
    socklen_t clientLen{};
    while (isRunning)
    {
        clientSocket = accept(sockfd, (struct sockaddr *)&serverAddress, &clientLen);
        std::thread handlingThread(&Server::handleConnection, this, clientSocket);
        handlingThread.detach();
    }
}

Server::~Server()
{
    // TODO: check for automatically closable socket
    isRunning = false;
    close(sockfd);
};
