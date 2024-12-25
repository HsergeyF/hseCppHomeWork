#include "client.hpp"
#include <string>
#include <filesystem>
#include <unistd.h>
#include <iostream>
// Not needed on OSX
#include <signal.h>

int main(int argc, char *argv[])
{
    PortsInputArguments args = getInputArgs(argc, argv);

    SharedClientSettings settings = {
        .clientAddress = getSocketAddress(args.clientPort),
        .recieverAddress = getSocketAddress(args.recieverPort)};
    auto p = fork();
    if (p == 0)
    {
        auto child_process_pid = fork();
        if (child_process_pid == 0)
        {
            signal(SIGHUP, SIG_IGN);
            auto client = Client(settings);
            client.run();
        }
        else if (child_process_pid > 0)
        {
            exit(0);
        }
        else
        {
            throw "Could not fork process";
        }
    }
    else if (p < 0)
    {
        throw "Could not fork process";
    }
}
