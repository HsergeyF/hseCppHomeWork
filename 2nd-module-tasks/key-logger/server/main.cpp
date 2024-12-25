#include <thread>
#include "helpers.hpp"
#include "server.hpp"
int main(int argc, char *argv[])
{
    assert(((void)"Please provide a port as a 1st argument", argc > 1));

    struct sockaddr_in serverAddress = getSocketAddress(std::atoi(argv[1]));

    auto server = Server(serverAddress);

    auto p = fork();

    if (p == 0)
    {
        auto child_process_pid = fork();
        if (child_process_pid == 0)
        {
            signal(SIGHUP, SIG_IGN);
            auto connectionThread = std::thread(&Server::onNewConnection, server);
            connectionThread.join();
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
