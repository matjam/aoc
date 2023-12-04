#include <string>

#include "AOCWorld.hpp"

using namespace std;

AOCRenderer *AOCWorld::renderer = nullptr;

AOCWorld::AOCWorld()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    window.create(
        sf::VideoMode(1280, 768),
        "SFML works!",
        sf::Style::Titlebar | sf::Style::Close,
        settings);

    renderer = new (AOCRenderer);
}

int AOCWorld::start()
{
    sf::Time timePerFrame = sf::seconds(1.f / 30.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (window.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > timePerFrame)
        {
            timeSinceLastUpdate -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }

        renderer->render(window);
    }

    return EXIT_SUCCESS;
}

void AOCWorld::update(sf::Time &deltaTime)
{
    renderer->update();
}

void AOCWorld::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::TextEntered:
            if (31 < event.text.unicode || event.text.unicode < 127)
            {
                string s(1, (char)event.text.unicode);
                renderer->print(s);
            }

            if (event.text.unicode == 13)
            {
                renderer->print("\n");
            }

            break;

        default:
            break;
        }
    }
}
