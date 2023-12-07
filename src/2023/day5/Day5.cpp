#include "Day5.hpp"
#include "Split.hpp"
#include "Trim.hpp"
#include "Convert.hpp"
#include "Interval.hpp"

#include <SFML/System.hpp>
#include <algorithm>
#include <fmt/core.h>

#define DEBUG 1
#define TEST_FILE 1

using namespace std;

Day5::Day5(AOCRenderer *r)
{
    renderer = r;
}

void Day5::run()
{
    string day5input;

    if (TEST_FILE)
        day5input = "resources/day5_sample.txt";
    else
        day5input = "resources/day5_input.txt";

    load_data(day5input);

    part1();
}

void Day5::load_data(string filename)
{
    input.open(filename);
    if (input.bad() || input.eof())
    {
        cerr << "couldn't open " << filename << endl;
        return;
    }

    string map_name;
    string line;
    while (getline(input, line))
    {
        if (line.empty())
        {
            map_name = "";
            continue;
        }

        if (line.starts_with("seeds: "))
        {
            // for part 2
            int64_t start = -1;

            auto seed_string = line.substr(7);
            for (auto nstr : split_string(trim_copy(seed_string), " "))
            {
                auto v = stoll(nstr, nullptr);
                seeds.push_back(v);

                // for part 2
                if (start == -1)
                {
                    start = v;
                }
                else
                {
                    seed_ranges.push_back({start, start + v - 1});
                    start = -1;
                }
            }
            continue;
        }

        if (line.find("map:") != string::npos)
        {
            auto map_string = split_string(trim_copy(line), " ");
            map_name = map_string[0];

            // so we can process a number in order of maps
            almanac_maps.push_back(map_name);
            continue;
        }

        // check that there's a map entry for this almanac entry
        if (!almanac.contains(map_name))
        {
            almanac[map_name] = map<int64_t, Interval<int64_t>>();
            almanac_dest[map_name] = map<int64_t, int64_t>();
        }

        // split the numbers
        auto numbers_string = split_string(line, " ");
        auto numbers = string_vector_to_int64_vector(numbers_string);

        // store the range keyed by the start of the range.
        almanac[map_name][numbers[1]] = {numbers[1], numbers[1] + numbers[2] - 1};

        // destination is keyed by the start of the range.
        almanac_dest[map_name][numbers[1]] = numbers[0];
    }

    // create an Interval for the beginning and end of each mapping that covers the entire range
    // so that each mapping has Intervals that cover from 0 to INT64_MAX. I'm not sure this is
    // necessary but it makes the code simpler.
    for (auto [k, v] : almanac)
    {
        auto first = v.begin()->second;
        auto last = v.rbegin()->second;

        fmt::print("{}: {} {}\n", k, first.start, last.end);

        if (first.start > 0)
        {
            v[0] = {0, first.start - 1};
            almanac_dest[k][0] = 0;
        }

        if (last.end < INT64_MAX)
        {
            v[last.end + 1] = {last.end + 1, INT64_MAX};
            almanac_dest[k][last.end + 1] = last.end + 1;
        }
    }

    // check that none of the Intervals overlap
    for (auto [k, v] : almanac)
    {
        for (auto [k2, v2] : v)
        {
            for (auto [k3, v3] : v)
            {
                if (k2 == k3)
                    continue;

                if (v2.overlaps(v3))
                {
                    cout << "overlap between " << k2 << " and " << k3 << endl;
                    cout << "  " << v2.start << " " << v2.end << endl;
                    cout << "  " << v3.start << " " << v3.end << endl;
                    throw runtime_error("overlap");
                }
            }
        }
    }

    input.close();
}

int64_t Day5::get_location_for_seed(int64_t id)
{
    for (auto map_name : almanac_maps)
    {
        auto map_name_split = split_string(map_name, "-");
        cout << map_name_split[0] << "[" << id << "] ";
        id = from_almanac(map_name, id);
    }

    cout << "location [" << id << "]" << endl;

    return id;
}

// from_almanac finds the interval a seed is in and then maps that seed value to the destination
// value for that interval. It then returns the destination value.
int64_t Day5::from_almanac(string map_name, int64_t seed)
{
    auto map = almanac[map_name];
    auto dest = almanac_dest[map_name];

    // find the interval that contains the seed
    auto interval = Interval<int64_t>::find_interval(seed, map);

    // the dest value is calculated by finding the offset from the start of the interval
    // and adding that to the destination value for the interval
    auto offset = seed - interval.start;
    auto dest_value = dest[interval.start] + offset;

    // return the destination value
    return dest_value;
}

void Day5::part1()
{
    sf::Clock clock;

    int64_t lowest = INT64_MAX;
    for (auto id : seeds)
    {
        auto result = get_location_for_seed(id);
        if (result < lowest)
            lowest = result;
    }

    sf::Time elapsed = clock.getElapsedTime();

    cout << "day 5 part 1 lowest location: " << lowest << endl;
    cout << "completed in " << elapsed.asMilliseconds() << "ms" << endl;
}
