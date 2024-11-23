#include "Server.hpp"

namespace bp = boost::process;

Server::Server(ServerSettings settings) : buffer_length(settings.buffer_length)
{
    server_address = settings.server_address;

    establishSocketConnection(sockfd, server_address);

    if (listen(sockfd, 100) == -1)
        handleException("Listening failed:");

    is_running = true;
};

void Server::handleConnection(int socket)
{
    std::cout << "New connection established" << std::endl;

    char command[buffer_length];
    memset(&command, 0, buffer_length);

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
    std::string exec_output;
    bp::ipstream output;
    bp::ipstream error_output;

    try
    {
        bp::child process(command, bp::std_out > output, bp::std_err > error_output);

        std::string exec_message = "Execution code: " + std::to_string(process.exit_code()) + "\n";

        writeToSocket(socket, exec_message);

        while (std::getline(process.exit_code() < 0 ? error_output : output, exec_output))
        {
            writeToSocket(socket, exec_output);
        }

        writeToSocket(socket, "\n");
    }
    catch (std::system_error e)
    {
        writeToSocket(socket, e.what());
    }
}

void Server::onResponse(sockaddr_in reciever_address, std::string message)
{
    socklen_t len = sizeof reciever_address;

    if (sendto(sockfd, (const char *)message.data(), strlen(message.data()),
               MSG_CONFIRM, (const struct sockaddr *)&reciever_address,
               len) == -1)
        handleException("Send response failed:");
};

void Server::onNewConnection()
{
    int client_socket;
    socklen_t client_len;
    while (is_running)
    {
        client_socket = accept(sockfd, (struct sockaddr *)&server_address, &client_len);
        int new_socket = client_socket;
        std::thread handling_thread(&Server::handleConnection, this, new_socket);
        handling_thread.detach();
    }
}

Server::~Server()
{
    is_running = false;
    close(sockfd);
};
