#include "AOCRenderer.hpp"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

AOCRenderer::AOCRenderer()
{
	curs_x = 0;
	curs_y = 0;

	if (!font.loadFromFile("resources/BigBlueTerm437NerdFontMono-Regular.ttf"))
	{
		cerr << "error reading font" << endl;
	}

	text.setFont(this->font);
	termBuffer.resize(24);

	text.setCharacterSize(30);
	text.setFillColor(sf::Color::Green);
}

void AOCRenderer::render(sf::RenderWindow &window)
{
	window.clear();

	// write the terminal buffer to the screen
	for (int row = 0; row < termBuffer.size(); row++)
	{
		text.setPosition(5.0f, -4.0f + 2.0f * (float)row);
		text.setString(termBuffer[row]);
		window.draw(text);
	}

	window.display();
}

void AOCRenderer::print(string s)
{
	inputBufferMutex.lock();
	inputBuffer.append(s);
	inputBufferMutex.unlock();
}

// this is called every tick to write characters to the screen, the intent
// being that each tick one character is written to the termBuffer
// and its removed from the inputBuffer.
//
// because this happens in the MAIN thread, we don't lock the termBuffer,
// we lock the inputBuffer, as thats the only thing being modified by
// other threads.
void AOCRenderer::update()
{
	inputBufferMutex.lock();
	if (inputBuffer.empty())
	{
		inputBufferMutex.unlock();
		return;
	}

	string first(inputBuffer, 0, 1); // grap a _copy_ of the first character
	inputBuffer.erase(0, 1);		 // erase the first character as we're writing it
	inputBufferMutex.unlock();

	if (first.compare("\n") == 0)
	{
		curs_x = 0;
		curs_y++;
	}
	else
	{
		termBuffer[curs_y].append(first);
		curs_x++;
	}

	if (curs_x > 62)
	{
		curs_x = 0;
		curs_y++;
	}

	if (curs_y > 23)
	{
		// scroll this shit by deleting the first row
		termBuffer.erase(termBuffer.begin());
		termBuffer.push_back(string(""));
		curs_y = 23;
	}
}