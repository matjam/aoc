#include "AOCWorld.h"
#include <string>

using namespace std;

AOCWorld::AOCWorld()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;

    window.create(
        sf::VideoMode(1280, 768),
        "SFML works!",
        sf::Style::Titlebar | sf::Style::Close,
        settings
    );
}

void worker(AOCRenderer *renderer) {
    while (true) {
        sf::sleep(sf::milliseconds(1000));
        renderer->writeText("writing some shit\n");
    }
}

int AOCWorld::start()
{
    sf::Time timePerFrame = sf::seconds(1.f / 30.f);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    sf::Thread thread_worker(&worker, &renderer);
    thread_worker.launch();
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

        renderer.render(window);
    }
    thread_worker.terminate();

    return EXIT_SUCCESS;
}

void AOCWorld::update(sf::Time& deltaTime)
{
    renderer.update();
}

void AOCWorld::processEvents()
{
    sf::Event event;

    while (window.pollEvent(event))
    {
        switch (event.type) {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::TextEntered:
            if (31 < event.text.unicode < 127) {
                string s(1, (char) event.text.unicode);
                renderer.writeText(s);
            }

            if (event.text.unicode == 13) {
                renderer.writeText("\n");
            }

            break;

        default:
            break;
        }

    }
}
