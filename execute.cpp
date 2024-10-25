
#include <string>
#include <filesystem>
#include <cassert>
#include <unistd.h>

int main(int argc, char *argv[])
{
    assert(("Please provide a target file as a 1st argument", argc > 1));
    assert(("Provided file does not exist", std::filesystem::exists(argv[1])));

    std::string exec_path = argv[1];
    assert(("Provided file is not executable", !access(exec_path.c_str(), X_OK)));

    exec_path += " > out.txt 2> error.txt";
    return system(exec_path.c_str());
}