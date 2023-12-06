#include "Day5.hpp"
#include "Split.hpp"
#include "Trim.hpp"
#include "Convert.hpp"
#include <set>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <SFML/System.hpp>
#include <algorithm>

#define DEBUG 1
#define TEST_FILE 0

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

    // part2();
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
                    seed_ranges.push_back({start, start + v - 1, -1});
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
            almanac[map_name] = map<int64_t, range>();
        }

        // split the numbers
        auto numbers_string = split_string(line, " ");
        auto numbers = string_vector_to_int64_vector(numbers_string);

        // store the range keyed by the start of the range.
        almanac[map_name][numbers[1]] = {numbers[1], numbers[1] + numbers[2] - 1, numbers[0]};
    }

    input.close();
}

int64_t Day5::get_location_for_seed(int64_t id)
{
    for (auto map_name : almanac_maps)
    {
        auto map_name_split = split_string(map_name, "-");
        // cout << map_name_split[0] << "[" << id << "] ";
        id = from_almanac(map_name, id);
    }

    // cout << "location [" << id << "]" << endl;

    return id;
}

int64_t Day5::from_almanac(string map_name, int64_t id)
{
    bool found = false;
    range prev = {-1, -1, -1};

    // iterate through the map, if the id is between the previous key
    // and the current key, then calculate the offset of the previous
    // and add it to the value in the map UNLESS previous was 0, then
    // we just return the value directly.
    //
    // this handles the beginning of the range before the values source
    // values start.
    //
    // if we hit the last entry and the value is after you know

    if (DEBUG)
        cout << "checking map " << map_name << " for id " << id << endl;

    for (auto [k, range] : almanac[map_name])
    {
        if (DEBUG)
            cout << " considering start " << range.start << " end " << range.end << " destination " << range.dest << " " << endl;

        if (id < range.start)
        {
            // it may be the previous entry
            if (prev.start == -1)
            {
                if (DEBUG)
                    cout << " out of lower bounds, returning id " << id << " as the value" << endl;
                // out of bounds just returns the provided value
                return id;
            }

            // return the destination, offset by the result of the id minus
            // prev_start.

            if (DEBUG)
                cout << " was previous entry, returning " << prev.dest + (id - prev.start) << endl;

            return prev.dest + (id - prev.start); // avoiding overflows?
        }

        prev.start = range.start;
        prev.end = range.end;
        prev.dest = range.dest;
    }

    // was the previous entry
    if (id >= prev.start && id <= prev.end)
    {
        if (DEBUG)
            cout << " was previous entry, returning " << prev.dest + (id - prev.start) << endl;
        return prev.dest + (id - prev.start);
    }

    if (DEBUG)
        cout << " out of upper bounds, returning id " << id << " as the value" << endl;

    // out of bounds just returns the provided value
    return id;
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
