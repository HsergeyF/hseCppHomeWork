#include <thread>
#include "helpers.hpp"
#include "server.hpp"

int main(int argc, char *argv[])
{
    assert(((void)"Please provide a port as a 1st argument", argc > 1));

    ServerSettings settings = {};
    settings.serverAddress = getSocketAddress(std::atoi(argv[1]));

    auto server = Server(settings);
    auto connectionThread = std::thread(&Server::onNewConnection, server);
    connectionThread.join();
    return 0;
}