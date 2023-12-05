#include <string>
#include <charconv>
#include <utility>
#include <map>

#include "Day3.hpp"
#include "Split.hpp"

using namespace std;

const int maxBlue = 14;
const int maxGreen = 13;
const int maxRed = 12;

Day3::Day3(AOCRenderer *r)
{
    renderer = r;
    buffer_width = 0;
    buffer_height = 0;
}

void Day3::run()
{
    string day3input = "resources/day3_input.txt";
    // string day3input = "resources/day3_test1_7253.txt";
    // string day3input = "resources/day3_test1_4361.txt";
    // string day3input = "resources/day3_test2_467835.txt";

    renderer->print("starting day3 ...\n");
    renderer->print(" . opening " + day3input + " ... ");

    load_buffer(day3input);
    generate_parts();

    part1();
    part2();

    renderer->print(" . closing " + day3input + ".\n");
    input.close();
}

void Day3::load_buffer(std::string filename)
{
    input.open(filename);
    if (input.bad() || input.eof())
    {
        renderer->print("\n !!! error opening file :-(\n");
        return;
    }
    renderer->print("opened!\n");
    renderer->print(" . loading into memory\n");

    int x = 0;
    int y = 0;
    int height = 0;

    char c;
    while (input.get(c))
    {
        if (c == 13 || c == 32) // skip CR
            continue;

        if (c == 10) // LF is a new line
        {
            if (buffer_width == 0) // the first line we process sets the width of the buffer.
            {
                buffer_width = x;
            }
            x = 0;
            y++;
            continue;
        }

        buffer.push_back(c);
        x++;
    }

    buffer_height = y + 1;
}

void Day3::dump_buffer()
{
    ofstream dump;
    dump.open("resources/buffer_dump.txt");

    for (int y = 0; y < buffer_height; y++)
    {
        for (int x = 0; x < buffer_width; x++)
        {
            dump << buffer[x + y * buffer_width];
        }
        dump << endl;
    }

    dump.close();
}

void Day3::generate_parts()
{
    part_grid.set_size(buffer_width, buffer_height);

    string partNumber;
    int instance_x = 0; // x,y when we found an instance of a number
    int instance_y = 0;
    int instance_id = 1; // unique ID for each part so if there's 100*100 thats going to compute to 200, not 100.
                         // start at 1 so we know 0 isn't a thing.

    // find all the part numbers. while reading everything into the . I think this logic is ok.
    for (int y = 0; y < buffer_height; y++)
    {
        for (int x = 0; x < buffer_width; x++)
        {
            char c = buffer[x + y * buffer_width];
            if (c > 47 && c < 58) // only digits
            {
                // keep appending digits until we get something else
                if (partNumber.size() > 0)
                {
                    partNumber.append(string() + c);
                }
                else
                {
                    instance_x = x;
                    instance_y = y;
                    partNumber = string() + c;
                }
            }
            else
            {
                if (partNumber.size() > 0)
                {
                    // this idiocy is basically so I can have two numbers that are the same value but
                    // I can determine if they are the same instance of that number. I could use pointers
                    // but .. whatever.
                    part p = {instance_id, atoi(partNumber.c_str())};
                    parts.push_back(p);
                    instance_id++;

                    for (auto px = instance_x; px < instance_x + partNumber.size(); px++)
                    {
                        part_grid.set(px, instance_y, p);
                    }
                    // reset partNumber
                    partNumber.clear();
                    instance_x = 0;
                    instance_y = 0;
                }
            }
        }
        if (partNumber.size() > 0)
        {
            part p = {instance_id, atoi(partNumber.c_str())};
            parts.push_back(p);
            instance_id++;

            for (auto px = instance_x; px < instance_x + partNumber.size(); px++)
            {
                part_grid.set(px, instance_y, p);
            }
            // reset partNumber
            partNumber.clear();
            instance_x = 0;
            instance_y = 0;
        }
    }
}

void Day3::part1()
{
    renderer->print(" . processing part 1 ... \n");

    int partSum = 0;

    // instance IDs that we have seen in the neighbors.
    map<int, part> instances;

    // now scan all the data for symbols that are not a number or .
    // and then check neighbours for part numbers. We want only to
    // consider each neighbour's unique
    for (int y = 0; y < buffer_height; y++)
    {
        for (int x = 0; x < buffer_width; x++)
        {
            char c = buffer[x + y * buffer_width];
            if (c == '.')
            {
                continue;
            }

            if ((c > ' ' && c < '0') || c == '=' || c == '@') // we excuded '.' above
            {
                // cout << "considering " << x << "," << y << " symbol " << c << endl;
                auto neighbours = part_grid.neighbours(x, y);
                // found a symbol, check neighbours
                for (auto p : neighbours)
                { // fuck just remembed about foreach lol
                    if (p.instance_id > 0)
                    {
                        if (!instances.contains(p.instance_id))
                        {
                            instances[p.instance_id] = p;
                            // cout << "   added value " << p.value << endl;
                        }
                    }
                }
            }
            else
            {
                if (c < '0' || c > '9')
                    cout << "unprocessed character [" << c << "]" << endl;
            }
        }
    }

    // add them into the sum if we found any
    for (auto part_kv : instances)
    {
        partSum += part_kv.second.value;
    }
    cout << "result: " << partSum << endl;

    renderer->print(" . day3 part1 result: " + to_string(partSum) + "\n");
}

// wow much copy pasta
void Day3::part2()
{
    renderer->print(" . processing part 2 ... \n");

    int partSum = 0;

    // the computed gear ratio for each symbol
    vector<int> ratios;

    // now scan all the data for symbols that are not a number or .
    // and then check neighbours for part numbers. We want only to
    // consider each neighbour's unique
    for (int y = 0; y < buffer_height; y++)
    {
        for (int x = 0; x < buffer_width; x++)
        {
            char c = buffer[x + y * buffer_width];
            if (c == '.')
            {
                continue;
            }

            if ((c > ' ' && c < '0') || c == '=' || c == '@') // we excuded '.' above
            {
                auto neighbours = part_grid.neighbours(x, y);
                // found a symbol, check neighbours

                map<int, part> unique_parts;

                for (auto p : neighbours)
                { // fuck just remembed about foreach lol
                    if (p.instance_id > 0)
                    {
                        if (!unique_parts.contains(p.instance_id))
                        {
                            unique_parts[p.instance_id] = p;
                        }
                    }
                }

                if (unique_parts.size() == 2)
                {
                    // compute the product of these parts
                    int product = 1;
                    for (auto p : unique_parts)
                    {
                        product = product * p.second.value;
                    }

                    ratios.push_back(product);
                }
                else
                {
                    cout << "did not compute for a part with more than two part numbers" << endl;
                }
            }
            else
            {
                if (c < '0' || c > '9')
                    cout << "unprocessed character [" << c << "]" << endl;
            }
        }
    }

    // add them into the sum if we found any
    for (auto ratio : ratios)
    {
        partSum += ratio;
    }
    cout << "result: " << partSum << endl;

    renderer->print(" . day3 part2 result: " + to_string(partSum) + "\n");
}
