#include <string>
#include <iostream>
#include <filesystem>
#include <cassert>

namespace fs = std::filesystem;

std::string get_file_status(const fs::path &p, fs::file_status s)
{
    switch (s.type())
    {
    case fs::file_type::regular:
        return std::string("Regular files:");
    case fs::file_type::directory:
        return std::string("Directories:");
    case fs::file_type::block:
        return std::string("Blocks:");
    case fs::file_type::character:
        return std::string("Characters:");
    case fs::file_type::fifo:
        return std::string("IPC Pipes:");
    case fs::file_type::socket:
        return std::string("Sockets");
    case fs::file_type::symlink:
        return std::string("Symlinks");
    default:
        return std::string("");
    }
}

int main(int argc, char *argv[])
{
    assert(("Please provide a target directory as a 1st argument", argc > 1));
    assert(("Provided path does not exist", fs::is_directory(argv[1])));

    std::string path = argv[1];
    std::unordered_map<std::string, int> filetype_counter;

    for (auto it{fs::directory_iterator(path)}; it != fs::directory_iterator(); ++it)
        filetype_counter[get_file_status(*it, it->symlink_status())]++;

    for (auto const &kv : filetype_counter)
        std::cout << kv.first << " " << kv.second << std::endl;
}