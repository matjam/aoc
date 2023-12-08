#include "Day5.hpp"
#include "Convert.hpp"
#include "Interval.hpp"
#include "strutil.h"

#include <SFML/System.hpp>
#include <algorithm>

#define DEBUG 1
#define TEST_FILE 1

using namespace std;
using namespace fmt;

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

    part2();
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
            for (auto nstr : strutil::split(strutil::trim_copy(seed_string), " "))
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
            auto map_string = strutil::split(strutil::trim_copy(line), " ");
            map_name = map_string[0];

            // so we can process a number in order of maps
            almanac_maps.push_back(map_name);
            continue;
        }

        // check that there's a map entry for this almanac entry
        if (!almanac.contains(map_name))
        {
            almanac[map_name] = map<int64_t, almanac_entry>();
        }

        // split the numbers
        auto numbers_string = strutil::split(line, " ");
        auto numbers = string_vector_to_int64_vector(numbers_string);

        // store the range keyed by the start of the range.
        almanac[map_name][numbers[1]] = {{numbers[1], numbers[1] + numbers[2] - 1}, numbers[0]};
        // print("stored {}: {}\n", map_name, almanac[map_name][numbers[1]]);
    }

    // create an Interval for the beginning and end of each mapping that covers the entire range
    // so that each mapping has Intervals that cover from 0 to INT64_MAX. I'm not sure this is
    // necessary but it makes the code simpler.
    for (auto &[k, v] : almanac)
    {
        // print("adding padding intervals for {}\n", k);

        auto first = v.begin()->second;
        auto last = v.rbegin()->second;

        // print("  {}: first:{} last:{}\n", k, first, last);

        if (first.interval.start > 0)
        {
            v[0] = {{0, first.interval.start - 1}, 0};

            // print("  added {}\n", v[0]);
        }

        if (last.interval.end < INT64_MAX)
        {
            v[last.interval.end + 1] = {{last.interval.end + 1, INT64_MAX}, last.interval.end + 1};

            // print("  added {}\n", v[last.interval.end + 1]);
        }
    }

    input.close();
}

int64_t Day5::get_location_for_seed(int64_t id)
{
    for (auto map_name : almanac_maps)
    {
        auto map_name_split = strutil::split(map_name, "-");
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
    auto mapping = almanac[map_name];

    // find the entry that contains the seed
    auto entry = find_entry_in_almanac(seed, mapping);

    // the dest value is calculated by finding the offset from the start of the interval
    // and adding that to the destination value for the interval
    auto offset = seed - entry.interval.start;
    auto dest_value = entry.destination + offset;

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

void Day5::part2()
{
    // OK so we should have what we need. In part2 of the problem, we're given a list of ranges
    // of seed numbers. We need to walk each almanac mapping in order, and push the range of seeds
    // through the mapping. This will create a new range of seeds. We then need to take the new
    // range of seeds and push it through the next mapping. We keep doing this until we've gone
    // through all the mappings. The final range of seeds holds the answer which is the lowest
    // final number in all the ranges.

    sf::Clock clock;

    vector<Interval<int64_t>> input_seeds;
    vector<Interval<int64_t>> output_seeds;

    input_seeds = seed_ranges;
    for (auto mapping_name : almanac_maps)
    {
        print("mapping {}\n", mapping_name);

        // dump the input seeds
        dump_intervals("  input seeds", input_seeds, "    ");

        auto mappings = almanac[mapping_name];
        while (input_seeds.size() > 0)
        {
            auto seed = input_seeds.back();
            input_seeds.pop_back();
            print("  seed: {}\n", seed);

            // because we have a mapping that covers the complete range, we only need to consider
            // the seeds that overlap the mapping. If the seed doesn't overlap, we can ignore it
            // as it will be handled by the next mapping.
            for (auto &[start, mapping] : mappings)
            {
                // get the overlap of the seed in the mapping. If it doesn't overlap, nothing happens.
                auto overlap = mapping.interval.overlap(seed);
                if (overlap.start == -1)
                    continue;

                print("    mapping: {}\n", mapping);

                // dump overlap
                print("      overlap: {}\n", overlap);

                // calculate the destination value for the seed
                auto offset = overlap.start - mapping.interval.start;
                print("      offset: {}\n", offset);

                auto dest_value = mapping.destination + offset;
                Interval<int64_t> dest_seed = {dest_value, dest_value + overlap.length() - 1};

                print("      dest seed: {}\n", dest_seed);

                // add the destination value to the output seeds
                output_seeds.push_back(dest_seed);
            }
        }

        // swap the output seeds to the input seeds so we can process the next mapping
        input_seeds.clear();
        input_seeds = output_seeds;
        output_seeds.clear();
    }

    // find the lowest value in the output seeds
    int64_t lowest = INT64_MAX;
    for (auto seed : input_seeds)
    {
        if (seed.start < lowest)
            lowest = seed.start;
    }

    sf::Time elapsed = clock.getElapsedTime();
    print("day 5 part 2 lowest location: {}\n", lowest);
    print("completed in {}ms\n", elapsed.asMilliseconds());
}
