#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <cstdint>

#include "AOCRenderer.hpp"

struct range
{
    std::int64_t start;
    std::int64_t end;
    std::int64_t dest;
};

class Day5
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;

    // outer map is a map of keys like "seed-to-soil" to another map of <std::int64_t, std::int64_t>.
    // the inner map is sorted (thanks to C++ maps being sorted) by key
    // and the key is the start of the range. The value is the destination number,
    // which will be offset from by the same amount the number being looked up is
    // offset in the inner map.

    std::map<std::string, std::map<int64_t, range>> almanac;
    std::vector<std::int64_t> seeds;
    std::vector<std::pair<std::int64_t, std::int64_t>> seed_ranges;
    std::vector<std::string> almanac_maps;

public:
    Day5(AOCRenderer *r);
    void load_data(std::string filename);
    void run();
    void part1();
    void part2();

    std::int64_t get_location_for_seed(std::int64_t id);
    std::int64_t from_almanac(std::string map_name, std::int64_t id);
};
