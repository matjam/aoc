#include <string>
#include <charconv>
#include <utility>
#include <map>
#include <regex>
#include <algorithm>

#include "Day4.hpp"
#include "Split.hpp"
#include "Convert.hpp"

using namespace std;

const int maxBlue = 14;
const int maxGreen = 13;
const int maxRed = 12;

Day4::Day4(AOCRenderer *r)
{
    renderer = r;
}

void Day4::run()
{
    string day4input = "resources/day4_input.txt";
    // string day4input = "resources/day4_test1.txt";

    renderer->print("starting day4 ...\n");
    renderer->print(" . opening " + day4input + " ...\n");

    load_data(day4input);

    part1();
    part2();

    renderer->print(" . closing\n");
    input.close();
}

void Day4::load_data(std::string filename)
{
    input.open(filename);
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
        auto card = parse_card(line);
        cards.push_back(card);

        vector<ScratchCard> v;
        v.push_back(card);
        all_cards.push_back(v);
    }
}

ScratchCard Day4::parse_card(std::string line)
{
    ScratchCard card;

    regex re("Card\\s+(\\d+):\\s*([\\s\\d]+)\\s+\\|\\s*([\\s\\d]+)", regex_constants::ECMAScript);
    smatch matches;

    regex_search(line, matches, re);

    auto card_id_str = matches[1].str();
    auto numbers_str = matches[2].str();
    auto winners_str = matches[3].str();

    regex replace_re("[\\s]+");
    card.numbers = strvectoint(split_string(regex_replace(numbers_str, replace_re, " "), " "));
    card.winners = strvectoint(split_string(regex_replace(winners_str, replace_re, " "), " "));
    card.id = atoi(card_id_str.c_str()) - 1; // cards start at 1 but we're going to use 0 based indexes

    return card;
}

int Day4::calculate_score(ScratchCard card)
{
    int winners = count_winners(card);
    int score = 0;

    for (int i = 0; i < winners; i++)
    {
        if (score == 0)
        {
            score = 1;
        }
        else
        {
            score = score * 2;
        }
    }

    return score;
}

int Day4::count_winners(ScratchCard card)
{
    int winners = 0;
    for (auto num : card.numbers) // for each card, see if its a winner
    {
        if (std::find(card.winners.begin(), card.winners.end(), num) != card.winners.end())
        {
            winners++;
        }
    }
    return winners;
}

void Day4::part1()
{
    renderer->print(" . processing part 1 ... \n");

    int total_points = 0;

    for (auto card : cards)
    {
        int score = calculate_score(card);
        total_points += score;
    }

    cout << "total_points: " << total_points << endl;

    renderer->print(" . day4 part1 result: " + to_string(total_points) + "\n");
}

// wow much copy pasta
void Day4::part2()
{
    renderer->print(" . processing part 2 ... \n");

    int total_cards = (int)all_cards.size(); // keep track of all the cards we end up with

    // all_cards is a vector of vectors; each position will hold all of the "copies"
    // of a given card. We process the outer vector one by one and don't modify it at all.
    // We pop cards off the inner vector one by one, processing them and adding any
    // duplicate cards into the right places as we go.
    //
    // we're copying the data around which could get insane but lets see how that goes

    for (int i = 0; i < (int)all_cards.size(); i++)
    {
        // pop a card off the top of the stack
        auto card_vector = all_cards[i];

        // remove a card from the current index and see if its a winner.
        while (card_vector.size() > 0)
        {
            auto card = card_vector.back();
            card_vector.pop_back();

            int winner_count = count_winners(card);

            // add duplicates of all the cards below this one
            for (int x = 0; x < winner_count; x++)
            {
                int idx = i + x + 1;

                // check we're not overflowing
                if (idx > all_cards.size() - 1)
                    break;

                // duplicate this card
                all_cards[idx].push_back(all_cards[idx].back());
                total_cards++;
            }
        }
    }

    cout << "total_cards: " << total_cards << endl;
    renderer->print(" . day4 part2 result: " + to_string(total_cards) + "\n");
}
