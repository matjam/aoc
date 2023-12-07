#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <cstdint>

#include "AOCRenderer.hpp"
#include "Interval.hpp"

class Day5
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;

    std::map<std::string, std::map<std::int64_t, Interval<std::int64_t>>> almanac;
    std::map<std::string, std::map<std::int64_t, std::int64_t>> almanac_dest;
    std::vector<std::int64_t> seeds;
    std::vector<Interval<int64_t>> seed_ranges;
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
