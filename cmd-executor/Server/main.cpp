#include <thread>
#include "helpers.hpp"
#include "Server.hpp"

int main(int argc, char *argv[])
{
    assert(((void)"Please provide a port as a 1st argument", argc > 1));

    ServerSettings settings = {};
    settings.server_address = get_socket_address(std::atoi(argv[1]));

    auto server = Server(settings);
    auto connection_thread = std::thread(&Server::onNewConnection, server);
    connection_thread.join();
    return 0;
}