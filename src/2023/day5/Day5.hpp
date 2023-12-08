#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <deque>
#include <cstdint>
#include <fmt/core.h>

#include "AOCRenderer.hpp"
#include "Interval.hpp"

struct almanac_entry
{
    Interval<std::int64_t> interval;
    std::int64_t destination;
};

template <>
struct fmt::formatter<almanac_entry>
{
    constexpr auto parse(format_parse_context &ctx) -> format_parse_context::iterator
    {
        // Parse the presentation format and store it in the formatter:
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
    // Formats the point p using the parsed format specification (presentation)
    // stored in this formatter.
    auto format(const almanac_entry &e, format_context &ctx) const -> format_context::iterator
    {
        // ctx.out() is an output iterator to write to.
        return fmt::format_to(ctx.out(), "{} -> {}", e.interval, e.destination);
    }
};

// Given a value and a map of entries, return the entry that contains the value
// If no interval contains the value, return an empty entry
static almanac_entry find_entry_in_almanac(std::int64_t value, std::map<std::int64_t, almanac_entry> entries)
{
    for (auto [k, v] : entries)
    {
        if (v.interval.contains(value))
            return v;
    }

    return almanac_entry();
}

class Day5
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;

    std::map<std::string, std::map<std::int64_t, almanac_entry>> almanac;
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

static inline void dump_intervals(std::string name, std::vector<Interval<std::int64_t>> intervals, std::string indent = "  ")
{
    fmt::print("{}:\n", name);
    for (auto interval : intervals)
    {
        fmt::print("{}{}\n", indent, interval);
    }
}