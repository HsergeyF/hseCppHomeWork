#include <thread>
#include "client.hpp"
#include "helpers.hpp"

int main(int argc, char *argv[])
{

    UDPChatInputArguments args = getInputArgs(argc, argv);

    assert(((void)"Please provide client and reciever ports as args",
            &args.clientPort != NULL || &args.recieverPort != NULL));

    ClientSettings settings = {};
    settings.clientAddress = getSocketAddress(args.clientPort);
    settings.recieverAddress = getSocketAddress(args.recieverPort);

    auto client = Client(settings);

    auto readRhread = std::thread(&Client::onRecieve, client);
    auto writeThread = std::thread(&Client::onWrite, client);

    readRhread.join();
    writeThread.join();

    return 0;
}
