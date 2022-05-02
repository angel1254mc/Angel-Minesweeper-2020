#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "WindowEssentials.h"
#include "Button.h"

Button::Button(int width, int height, float xPos, float yPos, WindowEssentials* essentials)
{
	this->width = width;
	this->height = height;
	this->xPos = xPos;
	this->yPos = yPos;
	this->essentials = essentials;

	
}

void Button::SpecialFunction()
{
	cout << "Err: Base Button: Contains no Special Function" << endl;
}

void Button::ChangeTexture(sf::Texture texture)
{
	//Do nothing here, virtual function to be implemented in game_state_button
}

void Button::Draw()
{
	sprite.setPosition(xPos, yPos);
	essentials->render_window->draw(sprite);
}

bool Button::checkIfClicked(int xCoord, int yCoord)
{
	if (xCoord >= xPos && xCoord <= xPos + width && yCoord >= yPos && yCoord <= yPos + height)
		return true;
	return false;
}

DebugButton::DebugButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board) : Button(width, height, xPos, yPos, essentials)
{
	this->board = board;
	buttonTexture = essentials->debug_button;
}

void DebugButton::Draw()
{
	sprite.setTexture(buttonTexture);
	sprite.setPosition(xPos, yPos);
	essentials->render_window->draw(sprite);
}

void DebugButton::SpecialFunction()
{
	if (board->GetIsGameLost() != true && board->GetIsGameWon() != true)
	board->RevealAllBombsDebug();
}

TestButton::TestButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board, int testnum) : Button(width, height, xPos, yPos, essentials)
{
	this->board = board;
	switch (testnum)
	{
	case 1:
		board_path = "boards/testboard1.brd";
		buttonTexture = essentials->test_1;
		break;
	case 2:
		board_path = "boards/testboard2.brd";
		buttonTexture = essentials->test_2;
		break;
	case 3:
		board_path = "boards/testboard3.brd";
		buttonTexture = essentials->test_3;
	}
}

void TestButton::SpecialFunction()
{
	board->BuildFromFile(board_path);
}

void TestButton::Draw()
{
	sprite.setTexture(buttonTexture);
	sprite.setPosition(xPos, yPos);
	essentials->render_window->draw(sprite);
}

GameStateButton::GameStateButton(int width, int height, float xPos, float yPos, WindowEssentials* essentials, Board* board, ifstream* file_read) : Button(width, height, xPos, yPos, essentials)
{
	this->board = board;
	this->file_read = file_read;
	buttonTexture = essentials->game_happening;
}

void GameStateButton::SpecialFunction()
{

	string width_boxes;
	string height_boxes;
	string mine_amount;
	int width;
	int height;
	int mines;

	file_read->open("boards/config.cfg");
	getline(*file_read, width_boxes, '\n');
	getline(*file_read, height_boxes, '\n');
	getline(*file_read, mine_amount, '\n');

	width = stoi(width_boxes);
	height = stoi(height_boxes);
	mines = stoi(mine_amount);

	board->ResetBoard(width, height, mines);
	file_read->close();
}

void GameStateButton::Draw()
{
	sprite.setTexture(buttonTexture);
	sprite.setPosition(xPos, yPos);
	essentials->render_window->draw(sprite);
}

void GameStateButton::ChangeTexture(sf::Texture texture)
{
	buttonTexture = texture;
	sprite.setTexture(buttonTexture);
}

