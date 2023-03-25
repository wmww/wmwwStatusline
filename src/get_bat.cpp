
#include "statusline.h"

#include <fstream>
#include <string>
#include <sys/stat.h>

bool pathExists(string const& path)
{
    struct stat info;
    return stat(path.c_str(), &info) == 0;
}

double getNumberFromFile(string const& path)
{
    std::ifstream ifs(path);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    return std::stod(content);
}

unsigned int getEnumFromFile(std::vector<std::pair<unsigned int, string>> const& enums, string const& path)
{
    std::ifstream ifs(path);
    std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    for (auto const& e : enums)
    {
        if (content == e.second)
        {
            return e.first;
        }
    }
    return 0;
}

