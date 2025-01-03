#include <thread>
#include "client.hpp"

int main(int argc, char *argv[])
{
    assert(((void)"Please provide a port as a 1st argument", argc > 1));
    // TODO: make args
    ClientSettings settings = {
        .serverAddress = getSocketAddress(std::atoi(argv[1])),
        .clientAddress = getSocketAddress(std::atoi(argv[2]))};

    // TODO: pass settings by pointer
    auto client = Client(settings);
    auto connectionThread = std::thread(&Client::onWrite, client);
    auto listenThread = std::thread(&Client::onRecieve, client);
    connectionThread.join();
    listenThread.join();
    return 0;
}