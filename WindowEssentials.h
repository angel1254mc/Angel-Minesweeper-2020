#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "Tile.h"
using namespace std;

struct WindowEssentials
{
	sf::Texture tile_hidden;
	sf::Texture tile_revealed;
	sf::Texture mine;
	sf::Texture number1;
	sf::Texture number2;
	sf::Texture number3;
	sf::Texture number4;
	sf::Texture number5;
	sf::Texture number6;
	sf::Texture number7;
	sf::Texture number8;
	sf::Texture flag;
	sf::Texture game_happening;
	sf::Texture game_won;
	sf::Texture game_lost;
	sf::Texture debug_button;
	sf::Texture test_1;
	sf::Texture test_2;
	sf::Texture test_3;
	sf::Texture digits;

	sf::RenderWindow* render_window;

	WindowEssentials(string width, string height);
	~WindowEssentials();
};