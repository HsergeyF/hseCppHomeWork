#include <string>
#include <fstream>
#include <getopt.h>
#include <random>

enum Regieme
{
    STASH,
    RESTORE
};

struct InputArguments
{
    std::string file;
    Regieme regieme{};

public:
    void set_regieme(std::string r)
    {
        if (r == "s")
        {
            this->regieme = STASH;
            return;
        }
        else if (r == "r")
        {
            this->regieme = RESTORE;
            return;
        }
        throw std::invalid_argument("Invalid regieme argument. Options: r | f.");
    }
};

InputArguments get_options(int argc, char *argv[])
{
    option longopts[] = {
        {"regieme", required_argument, NULL, 'r'},
        {"file", required_argument, NULL, 'f'},
        {0}};

    InputArguments arguments{};
    int opt;
    while ((opt = getopt(argc, argv, "r:f:")) != -1)
    {
        switch (opt)
        {
        case 'r':
            arguments.set_regieme(optarg);
            break;
        case 'f':
            arguments.file = optarg;
            break;
        }
    }
    return arguments;
}

char *read_source(std::string file_name)
{
    std::fstream fs;
    fs.open(file_name, std::ios_base::in | std::ios_base::out | std::ios::binary);
    fs.seekg(0, fs.end);
    int length = fs.tellg();
    fs.seekg(0, fs.beg);

    char *buffer = new char[length];
    fs.read(buffer, length);
    fs.close();
    return buffer;
}

void stash(std::string file_name)
{
    std::fstream fs;
    char *buffer = read_source(file_name);
    fs.open(file_name, std::ios_base::in | std::ios_base::out |
                           std::ios_base::trunc | std::ios::binary);
    fs.seekg(0, fs.end);
    int length = fs.tellg();

    std::random_device random_generator;
    char stash_bite = random_generator();

    while (strcmp(&buffer[0], &stash_bite) == 0)
    {
        stash_bite = random_generator();
    }
    
    fs.seekp(0, fs.beg);
    fs << stash_bite << buffer;
    fs.close();
}

void restore(std::string file_name)
{
    std::fstream fs;
    char *buffer = read_source(file_name);
    char *substr = buffer + 1;
    std::ofstream ofs(file_name, std::ios::binary | std::ofstream::trunc);
    ofs << substr;
    ofs.close();
}

int main(int argc, char *argv[])
{
    /* Stateless преобразватель magic number-a.
    Добавляет в файл первый случайны байт, отличный от первого magic number-а
    в случае, если указан аргумент '-r s' и удаляет первый байт в случае, если
    указан '-r r'. Если применить recover режим к файлу, который не был предварительно
    искажен, то возвращать его обратно в рабочее состояние нужно будет по спецификации
    кодов magic number-ов для определенного типа файла.
    */
    auto arguments = get_options(argc, argv);

    switch (arguments.regieme)
    {
    case STASH:
        stash(arguments.file);
        break;
    case RESTORE:
        restore(arguments.file);
        break;
    default:
        break;
    }

    return 0;
}
