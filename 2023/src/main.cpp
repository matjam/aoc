#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AOCWorld.hpp"
#include "2023/day2/Day2.hpp"
#include "2023/day3/Day3.hpp"
#include "2023/day4/Day4.hpp"
#include "2023/day5/Day5.hpp"

void aocWorker()
{
    sf::sleep(sf::seconds(1));

    Day5 day5(AOCWorld::renderer);
    day5.run();
}

int main()
{
    // AOCWorld world;
    // sf::Thread thread(&aocWorker);

    Day5 day5(nullptr);
    day5.run();

    // thread.launch();
    // world.start();
    // thread.wait();
}
