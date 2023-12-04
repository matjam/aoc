#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "AOCRenderer.hpp"

class AOCWorld
{
private:
	sf::RenderWindow window;

public:
	static AOCRenderer *renderer;

	AOCWorld();

	int start();
	void update(sf::Time &deltaTime);
	void processEvents();
};
