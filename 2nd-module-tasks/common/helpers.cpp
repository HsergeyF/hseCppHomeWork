#include "helpers.hpp"

struct sockaddr_in getSocketAddress(const int port)
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

void handleException(const std::string message)
{
    perror(message.c_str());
    exit(EXIT_FAILURE);
};

// TODO: const struct *
void establishSocketConnection(int &sockfd, struct sockaddr_in address, const int streamType)
{
    if ((sockfd = socket(address.sin_family, streamType, 0)) < 0)
        handleException("Socket creation failed:");

    if (bind(sockfd, (const struct sockaddr *)&address, sizeof(address)) < 0)
        handleException("Binding failed:");
}

PortsInputArguments getInputArgs(int argc, char *argv[])
{

    option longopts[] = {
        {"client", required_argument, NULL, 'c'},
        {"reciever", required_argument, NULL, 'r'},
        {0}};

    PortsInputArguments arguments{};
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

    assert(((void)"Please provide client and reciever ports as args",
            &arguments.clientPort != NULL || &arguments.recieverPort != NULL));

    return arguments;
}

std::string findKeyboardDeviceNumber()
{
    const std::string cmd =
        "grep -E 'Handlers|EV=' /proc/bus/input/devices |"
        "grep -B1 'EV=120013' |"
        "grep -Eo 'event[0-9]+' |"
        "grep -Eo '[0-9]+' |"
        "tr -d '\n'";
    FILE *pipe = popen(cmd.c_str(), "r");
    char buffer[128];
    std::string result = "";
    while (!feof(pipe))
        if (fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    pclose(pipe);
    return result;
}

std::string getInputDevicePath()
{
    return "/dev/input/event" + findKeyboardDeviceNumber();
}
