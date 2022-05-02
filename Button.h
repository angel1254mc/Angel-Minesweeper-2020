#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "WindowEssentials.h"
class Board;
class Button
{
public:
	sf::Sprite sprite;
	int width;
	int height;
	float xPos;
	float yPos;

		WindowEssentials* essentials;
		Button(int width, int height, float xPos, float yPos, WindowEssentials* essentials);

		virtual void SpecialFunction();

		virtual void Draw();

		virtual void ChangeTexture(sf::Texture texture);

		bool checkIfClicked(int xCoord, int yCoord);
};

class DebugButton : public Button 
{
	Board* board;
public:
	sf::Texture buttonTexture;
	DebugButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board);

	void SpecialFunction();
	void Draw();
};

class TestButton : public Button
{
	Board* board;
	string board_path;
public:
	sf::Texture buttonTexture;
	TestButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board, int testnum);
	void Draw();

	void SpecialFunction();
};

class GameStateButton : public Button
{
	Board* board;
	ifstream* file_read;

public: 
	sf::Texture buttonTexture;
	GameStateButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board, ifstream* file_read);
	void Draw();

	void SpecialFunction();

	void ChangeTexture(sf::Texture texture);
};

