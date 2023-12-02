#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "AOCRenderer.h"

class AOCWorld
{
private:
	sf::RenderWindow window;
	AOCRenderer renderer;

public:
	AOCWorld();

	int start();
	void update(sf::Time& deltaTime);
	void processEvents();
};

