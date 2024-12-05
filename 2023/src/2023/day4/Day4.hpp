#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "AOCRenderer.hpp"
#include "Grid.hpp"

struct ScratchCard
{
    int id;
    std::vector<int> numbers;
    std::vector<int> winners;
};

class Day4
{
private:
    AOCRenderer *renderer;
    std::ifstream input;
    std::vector<char> buffer;
    std::vector<ScratchCard> cards;
    std::vector<std::vector<ScratchCard>> all_cards;

public:
    Day4(AOCRenderer *r);
    void load_data(std::string filename);
    ScratchCard parse_card(std::string line);
    int calculate_score(ScratchCard);
    int count_winners(ScratchCard);
    void run();
    void part1();
    void part2();
};
