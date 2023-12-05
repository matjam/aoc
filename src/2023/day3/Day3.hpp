#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AOCRenderer.hpp"
#include "Grid.hpp"

class Day3
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;
    int buffer_width;
    int buffer_height;

public:
    Day3(AOCRenderer *r);
    void load_buffer(std::string filename);
    void run();
    void part1();
    void part2();
};
