#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "Tile.h"
#include "WindowEssentials.h"

WindowEssentials::WindowEssentials(string width, string height)
{
	render_window = new sf::RenderWindow(sf::VideoMode(stoi(width) * 32, stoi(height) * 32 + 64), "Minesweeper", sf::Style::Close);

	tile_hidden.loadFromFile("images/tile_hidden.png");
	tile_revealed.loadFromFile("images/tile_revealed.png");
	mine.loadFromFile("images/mine.png");
	number1.loadFromFile("images/number_1.png");
	number2.loadFromFile("images/number_2.png");
	number3.loadFromFile("images/number_3.png");
	number4.loadFromFile("images/number_4.png");
	number5.loadFromFile("images/number_5.png");
	number6.loadFromFile("images/number_6.png");
	number7.loadFromFile("images/number_7.png");
	number8.loadFromFile("images/number_8.png");
	flag.loadFromFile("images/flag.png");
	game_happening.loadFromFile("images/face_happy.png");
	game_won.loadFromFile("images/face_win.png");
	game_lost.loadFromFile("images/face_lose.png");
	debug_button.loadFromFile("images/debug.png");
	test_1.loadFromFile("images/test_1.png");
	test_2.loadFromFile("images/test_2.png");
	test_3.loadFromFile("images/test_3.png");
	digits.loadFromFile("images/digits.png");


}

WindowEssentials::~WindowEssentials()
{
	delete render_window;
	
}