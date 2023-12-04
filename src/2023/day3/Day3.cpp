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
}

void Day3::run()
{
    string day3input = "resources/day3_input.txt";

    renderer->print("starting day3 ...\n");
    renderer->print(" . opening " + day3input + " ... ");
    input.open(day3input);
    if (input.bad() || input.eof())
    {
        renderer->print("\n !!! error opening file :-(\n");
        return;
    }
    renderer->print("opened!\n");
    renderer->print(" . loading into memory\n");

    string line;
    while (getline(input, line))
    {
        buffer.push_back(line);
    }

    part1();
    part2();

    renderer->print(" . closing " + day3input + ".");
    input.close();
}

void Day3::part1()
{
    renderer->print(" . processing part 1 ... \n");
    int row = 140;
    int col = 140;
    vector<int> grid;
    grid.resize(row * col);

    // find all the part numbers
    for (int y = 0; y < buffer.size(); y++)
    {
        string partNumber;
        string line = buffer[y];
        for (int x = 0; x < line.length(); x++)
        {
            char c = line[x];
            if (c > 47 && c < 58)
            {
                if (partNumber.size() > 0)
                {
                    partNumber.append(string() + c);
                }
                else
                {
                    partNumber = string() + c;
                }
            }
            else
            {
                if (partNumber.size() > 0)
                {
                    // store the number in all the locations it is related to
                    for (int i = 0; i < partNumber.size(); i++)
                    {
                        grid[x - i + y * row] = atoi(partNumber.c_str());
                    }
                    // reset partNumber
                    partNumber.clear();
                }
            }
        }
    }

    // easy way to express all the neighbors in 2d space.
    vector<pair<int, int>> neighbours = {
        {-1, -1},
        {0, -1},
        {1, -1},
        {-1, 0},
        {1, 0},
        {-1, 1},
        {0, 1},
        {1, 1},
    };

    int partSum = 0;

    // now scan all the data for symbols that are not a number or .
    // and then check neighbours for part numbers.
    for (int y = 0; y < buffer.size(); y++)
    {
        string line = buffer[y];
        for (int x = 0; x < line.length(); x++)
        {
            vector<int> counted;
            char c = line[x];
            if ((c > 32 && c < 46) || c == 47 || (c > 57 && c < 65))
            {
                // found a symbol, check neighbours
                for (auto neighbourVector : neighbours)
                { // fuck just remembed about foreach lol
                    int nx = x + neighbourVector.first;
                    int ny = y + neighbourVector.second;

                    int part = grid[nx + ny * row];
                    if (part != 0)
                    {
                        if (counted.size() == 0 || counted.back() != part)
                        {
                            counted.push_back(part);
                        }
                    }
                }
            }

            // add them into the sum if we found any
            for (auto part : counted)
            {
                partSum += part;
            }
        }
    }

    renderer->print(" . day3 part1 result: " + to_string(partSum) + "\n");
}

// wow much copy pasta
void Day3::part2()
{
}
