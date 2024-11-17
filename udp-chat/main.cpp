#pragma once
#include <thread>
#include "Client.cpp"
#include "helpers.cpp"

int main(int argc, char *argv[])
{

    InputArguments args = get_options(argc, argv);
    assert(("Please provide client and reciever ports as args",
            args.client_port != NULL || args.reciever_port != NULL));

    ClientSettings settings = {};
    settings.client_address = get_socket_adress(args.client_port);
    settings.reciever_address = get_socket_adress(args.reciever_port);

    auto client = Client(settings);

    auto read_thread = std::thread(&Client::onRecieve, client);
    auto write_thread = std::thread(&Client::onWrite, client);

    read_thread.join();
    write_thread.join();

    return 0;
}
