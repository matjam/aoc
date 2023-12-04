#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "AOCWorld.hpp"
#include "2023/day2/Day2.hpp"
#include "2023/day3/Day3.hpp"

void worldWorker()
{
    AOCWorld world;
    world.start();
}

int main()
{
    sf::Thread thread(&worldWorker);
    thread.launch();

    sf::sleep(sf::seconds(5));

    Day2 day2(AOCWorld::renderer);
    day2.run();

    Day3 day3(AOCWorld::renderer);
    day3.run();

    thread.wait();
}
