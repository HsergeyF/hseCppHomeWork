#include <string>
#include <filesystem>
#include <cassert>
#include <unistd.h>
#include <iostream>

int main(int argc, char *argv[])
{
    // Fork from child process, exit child, set Sigignore to avoid canceling after terminal exit.
    assert(("Please provide a target file as a 1st argument", argc > 1));
    assert(("Provided file does not exist", std::filesystem::exists(argv[1])));

    std::string exec_path = argv[1];
    assert(("Provided file is not executable", !access(exec_path.c_str(), X_OK)));

    exec_path += " &> /dev/null";
    auto p = fork();
    if (p == 0)
    {
        auto child_process_pid = fork();
        if (child_process_pid == 0)
        {
            signal(SIGHUP, SIG_IGN);
            std::cout << "Check working process with 'lsof -p " << getpid() << "'" << std::endl;
            system(exec_path.c_str());
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