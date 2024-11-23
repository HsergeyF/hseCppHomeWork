#pragma once
#include <thread>
#include "Client.hpp"

int main(int argc, char *argv[])
{
    assert(((void)"Please provide a port as a 1st argument", argc > 1));
    // TODO: make args
    ClientSettings settings = {};
    settings.server_address = get_socket_address(std::atoi(argv[1]));
    settings.client_address = get_socket_address(std::atoi(argv[2]));

    auto client = Client(settings);
    auto connection_thread = std::thread(&Client::onWrite, client);
    auto listen_thread = std::thread(&Client::onRecieve, client);
    connection_thread.join();
    listen_thread.join();
    return 0;
}