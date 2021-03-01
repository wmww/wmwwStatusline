
#include "statusline.h"

#include <fstream>
#include <string>

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

