#include "Client.hpp"

Client::Client(ClientSettings settings) : buffer_length(settings.buffer_length)
{
    setUserName();

    client_address = settings.client_address;

    reciever_address = settings.reciever_address;

    if ((sockfd = socket(settings.client_address.sin_family, SOCK_DGRAM, 0)) < 0)
    {
        perror("Socket creation failed:");
        exit(EXIT_FAILURE);
    }

    if (bind(sockfd, (const struct sockaddr *)&client_address, sizeof(client_address)) < 0)
    {
        perror("Binding failed:");
        exit(EXIT_FAILURE);
    }

    is_running = true;
};

void Client::setUserName()
{
    std::cout << "Type username: ";
    getline(std::cin, user_name);
    if (user_name.size() == 0)
        user_name = "anon user";
}

void Client::onWrite()
{
    std::string message;
    socklen_t len = sizeof reciever_address;
    int num_of_bytes;
    while (is_running)
    {
        getline(std::cin, message);
        message.insert(0, user_name + ": ");
        num_of_bytes = sendto(sockfd, (const char *)message.data(), strlen(message.data()),
                              MSG_CONFIRM, (const struct sockaddr *)&reciever_address,
                              len);
        if (num_of_bytes == -1)
        {
            perror("Sendto error:");
            exit(EXIT_FAILURE);
        }
    };
};

void Client::onRecieve()
{
    int num_of_bytes;
    char buffer[buffer_length];
    socklen_t len = sizeof reciever_address;
    while (is_running)
    {
        num_of_bytes = recvfrom(sockfd, (char *)buffer, buffer_length,
                                MSG_WAITALL, (struct sockaddr *)&reciever_address,
                                &len);
        if (num_of_bytes == -1)
        {
            perror("Recievefrom error:");
            exit(EXIT_FAILURE);
        }
        buffer[num_of_bytes] = '\0';
        std::cout << buffer << std::endl;
    }
};

Client::~Client()
{
    is_running = false;
    close(sockfd);
};
