#include "Client.hpp"

Client::Client(ClientSettings settings) : buffer_length(settings.buffer_length)
{
    client_address = settings.client_address;
    server_address = settings.server_address;

    establishSocketConnection(sockfd, client_address);

    if (connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
        handleException("Connection failed:");

    is_running = true;
};

void Client::onWrite()
{
    std::string command;
    while (is_running)
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
    char response[buffer_length];
    while (read(sockfd, response, sizeof(response) - 1) > 0)
    {
        std::cout << response;
    }
};

Client::~Client()
{
    is_running = false;
    close(sockfd);
};
