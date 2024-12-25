#include <thread>
#include "client.hpp"
#include "helpers.hpp"

int main(int argc, char *argv[])
{

    PortsInputArguments args = getInputArgs(argc, argv);

    SharedClientSettings settings = {
        .clientAddress = getSocketAddress(args.clientPort),
        .recieverAddress = getSocketAddress(args.recieverPort)};

    // TODO: pass pointer?
    auto client = Client(settings);

    auto readRhread = std::thread(&Client::onRecieve, client);
    auto writeThread = std::thread(&Client::onWrite, client);

    readRhread.join();
    writeThread.join();

    return 0;
}
