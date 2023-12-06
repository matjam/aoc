#include "Day5.hpp"
#include "Split.hpp"
#include "Trim.hpp"

using namespace std;

Day5::Day5(AOCRenderer *r)
{
    renderer = r;
}

void Day5::run()
{
    string day5input = "resources/day5_sample.txt";

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
            cout << "empty line" << endl;
            map_name = "";
            continue;
        }

        if (line.starts_with("seeds: "))
        {
            cout << "creating seeds" << endl;
            auto seed_string = line.substr(7);
            for (auto nstr : split_string(trim_copy(seed_string), " "))
            {
                seeds.push_back(stoll(nstr, nullptr));
            }
            continue;
        }

        if (line.find("map:") != string::npos)
        {
            auto map_string = split_string(trim_copy(line), " ");
            map_name = map_string[0];
            cout << "found map name " << map_name << endl;
            continue;
        }

        cout << "numbers: " << line << endl;
    }

    input.close();
}

void Day5::part1()
{
}

void Day5::part2()
{
}

int64_t Day5::from_almanac(string map_name, int64_t id)
{

    return 0;
}
