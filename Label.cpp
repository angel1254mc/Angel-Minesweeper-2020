#include "Label.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "WindowEssentials.h"
using namespace std;
class Board;
Label::Label(int width, int height, WindowEssentials* essentials, Board* board)
{
	this->segment_width = width;
	this->segment_height = height;
	this->essentials = essentials;
	this->board = board;
	sprite_array[0] = sign;
	sprite_array[1] = hundreds;
	sprite_array[2] = tens;
	sprite_array[3] = ones;

	UpdateLabels();
}

void Label::UpdateLabels()
{
	int mines_left = board->getMines();
	string mines_string = to_string(mines_left);
	int length = mines_string.length();

	char* mines_numeric_array;
	char corresponding_label_ints[4];
	mines_numeric_array = &mines_string[0];
	//Zero initializing array...
	for (int i = 0; i < 4; i++)
		corresponding_label_ints[i] = 0;
	//Transferring mines_numeric_array to corresponding_label_ints
	int cli_length = sizeof(corresponding_label_ints) / sizeof(corresponding_label_ints[0]);
	for (int i = length - 1; i >= 0; i--)
	{
		corresponding_label_ints[cli_length-1] = mines_numeric_array[i];
		cli_length--;
	}

	for (int i = 0; i < 4; i++)
	{
		if (i == 0 && atoi(&corresponding_label_ints[i]) == 0)
			continue;
		else
		getTexture(corresponding_label_ints[i], &sprite_array[i]);
	}
}

void Label::getTexture(const char v, sf::Sprite* sprite)
{
	int v_int = atoi(&v);
	sprite->setTexture(essentials->digits);
	sprite->setTextureRect(sf::IntRect(21 * v_int, 0, 21, 32));
	if (v == '-')
		sprite->setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));

}

void Label::Draw()
{
	sprite_array[0].setPosition(0.0f, board->getHeight() * 32.0f);
	sprite_array[1].setPosition(21.0f, board->getHeight() * 32.0f);
	sprite_array[2].setPosition(42.0f, board->getHeight() * 32.0f);
	sprite_array[3].setPosition(63.0f, board->getHeight() * 32.0f);

	for (int i = 0; i < 4; i++)
		essentials->render_window->draw(sprite_array[i]);
}