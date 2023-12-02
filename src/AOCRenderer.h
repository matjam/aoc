#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class AOCRenderer
{
private:
	sf::Font font;
	sf::Text text;

	// incoming lines are written to this buffer and cleared as
	// it is written to the termBuffer vector.
	std::string inputBuffer;

	// mutex to lock read/writing while the text is being written
	// by other threads.
	sf::Mutex inputBufferMutex;

	// representation of the display, will hold 24 lines that will
	// be at most 40 characters wide for a 40x24 display
	std::vector<std::string> termBuffer;

	int curs_x;
	int curs_y;

public:
	AOCRenderer();
	void render(sf::RenderWindow& window);

	void writeText(std::string s);

	void update(); 
};

