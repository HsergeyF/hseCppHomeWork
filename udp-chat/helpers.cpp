#include <string>
#include <getopt.h>
#include <netinet/in.h>

struct InputArguments
{
    int client_port;
    int reciever_port;
};

InputArguments get_options(int argc, char *argv[])
{
    option longopts[] = {
        {"client", required_argument, NULL, 'c'},
        {"reciever", required_argument, NULL, 'r'},
        {0}};

    InputArguments arguments{};
    int opt;
    while ((opt = getopt(argc, argv, "c:r:")) != -1)
    {
        switch (opt)
        {
        case 'c':
            arguments.client_port = std::atoi(optarg);
            break;
        case 'r':
            arguments.reciever_port = std::atoi(optarg);
            break;
        }
    }
    return arguments;
}

struct sockaddr_in get_socket_adress(int port)
{
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    // Hint: if using external ip address, implement passing ip_adress via args
    // address.sin_addr.s_addr = inet_addr(args.ip_adress);
    address.sin_port = htons(port);
    return address;
}