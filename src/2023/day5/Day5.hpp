#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <cstdint>

#include "AOCRenderer.hpp"

// I reuse this for both the seed ranges and the mappings
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

    std::map<std::string, std::map<int64_t, range>> almanac;
    std::vector<std::int64_t> seeds;
    std::vector<range> seed_ranges;
    std::vector<std::string> almanac_maps;
    std::vector<range> split_range(range mapping, range seed);

public:
    Day5(AOCRenderer *r);
    void load_data(std::string filename);
    void run();
    void part1();
    void part2();

    std::int64_t get_location_for_seed(std::int64_t id);
    std::int64_t from_almanac(std::string map_name, std::int64_t id);
};
