#pragma once
#include <string>
#include <vector>

static inline std::vector<int> strvectoint(std::vector<std::string> sv)
{
    std::vector<int> result;

    for (std::string s : sv)
    {
        result.push_back(atoi(s.c_str()));
    }

    return result;
}
