#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "WindowEssentials.h"

class Label
{
	sf::Texture digits;
	sf::Sprite hundreds;
	sf::Sprite tens;
	sf::Sprite ones;
	sf::Sprite sign;
	Board* board;
	WindowEssentials* essentials;
	int segment_width;
	int segment_height;
	int integer_value;
	sf::Sprite sprite_array[4];


	public:
		//Constructor
		Label(int width, int height, WindowEssentials* essentials, Board* board);
		
		void UpdateLabels();
		void getTexture(const char v, sf::Sprite* sprite);
		void Draw();
};

