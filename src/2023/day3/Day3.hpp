#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AOCRenderer.hpp"

class Day3
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<std::string> buffer;

public:
    Day3(AOCRenderer *r);
    void run();
    void part1();
    void part2();
};
