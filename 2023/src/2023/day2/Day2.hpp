#pragma once

#include <iostream>
#include <fstream>

#include "AOCRenderer.hpp"

class Day2
{
private:
	AOCRenderer* renderer;
	std::ifstream input;

public:
	Day2(AOCRenderer *r);
	void run();
	void part1();
	void part2();
};

