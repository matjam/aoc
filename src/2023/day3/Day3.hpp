#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AOCRenderer.hpp"
#include "Grid.hpp"

struct part
{
    int instance_id;
    int value;
};

class Day3
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;
    int buffer_width;
    int buffer_height;
    Grid<part> part_grid;
    std::vector<part> parts;

public:
    Day3(AOCRenderer *r);
    void load_buffer(std::string filename);
    void generate_parts();
    void run();
    void part1();
    void part2();
    void dump_buffer();
};
