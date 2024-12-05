#pragma once
#include <string>
#include <vector>
#include <cstdint>

static inline std::vector<int> strvectoint(std::vector<std::string> sv)
{
    std::vector<int> result;

    for (std::string s : sv)
    {
        result.push_back(std::stoi(s));
    }

    return result;
}

// Convert a vector of strings that contain numbers into a vector of int64_t.
static inline std::vector<std::int64_t> string_vector_to_int64_vector(std::vector<std::string> sv)
{
    std::vector<std::int64_t> result;

    for (std::string s : sv)
    {
        result.push_back(std::stoll(s));
    }

    return result;
}
