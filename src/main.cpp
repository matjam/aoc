#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AOCWorld.hpp"
#include "2023/day2/Day2.hpp"
#include "2023/day3/Day3.hpp"
#include "2023/day4/Day4.hpp"

void worldWorker()
{
    AOCWorld world;
    world.start();
}

int main()
{
    sf::Thread thread(&worldWorker);
    thread.launch();

    sf::sleep(sf::seconds(1));

    // Day2 day2(AOCWorld::renderer);
    // day2.run();

    // Day3 day3(AOCWorld::renderer);
    // day3.run();

    Day4 day4(AOCWorld::renderer);
    day4.run();

    thread.wait();
}
