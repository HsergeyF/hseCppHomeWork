#include <string>
#include <iostream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    assert(("Please provide a target file as a 1st argument", argc > 1));
    assert(("Provided file doesn't exist", fs::exists(argv[1])));

    std::string file_path = argv[1];
    std::string hide_path = "./blackbox/";
    fs::create_directories(hide_path);

    // default permissions at my local OSX machine: drwxr-xr-x
    fs::rename(file_path, hide_path + file_path);

    // target permission: --wx--x--x
    fs::permissions(hide_path, fs::perms::group_read, fs::perm_options::remove);
    fs::permissions(hide_path, fs::perms::owner_read, fs::perm_options::remove);
    fs::permissions(hide_path, fs::perms::others_read, fs::perm_options::remove);
}