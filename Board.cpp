#include "Board.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Tile.h"
#include "Random.h"
#include <ctime>
#include "WindowEssentials.h"
#include "Button.h"
using namespace std;

Board::Board(int width, int height, int mine_count, sf::RenderWindow* window, WindowEssentials* essentials, ifstream* file_read)
{
	this->width = width;
	this->height = height;
	this->window = window;
	this->board_mine_amount = mine_count;
	this->mines_remaining = board_mine_amount;
	this->tiles_left = width * height - board_mine_amount;
	this->gameIsLost = false;
	this->gameIsWon = false;
	this->essentials = essentials;
	this->file_read = file_read;
	this->mine_label = new Label(21, 32, essentials, this);
	//Button handling and creation
	float game_state_x = (float)width * 32 / 2 - 32;
	buttons[0] = new GameStateButton(64, 64, game_state_x, height * 32.0f, essentials, this, file_read);
	buttons[1] = new DebugButton(64, 64, game_state_x += 128.0f, height * 32.0f, essentials, this);
	buttons[2] = new TestButton(64, 64, game_state_x += 64.0f, height * 32.0f, essentials, this, 1);
	buttons[3] = new TestButton(64, 64, game_state_x += 64.0f, height * 32.0f, essentials, this, 2);
	buttons[4] = new TestButton(64, 64, game_state_x += 64.0f, height * 32.0f, essentials, this, 3);
	int map_iter = 0;
	board = new Tile** [height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new Tile * [width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Tile* tile_created = new Tile(j * 32, i * 32, this);
			board[i][j] = tile_created;
			tileMap[map_iter] = tile_created;
			map_iter++;
		}
	}
	for (int i = 0; i < board_mine_amount; i++)
	{
		int randomInt = 0 + rand() % (width * height - 1)+ 1;
		cout << randomInt << endl;
		if (tileMap[randomInt]->HasBomb() == true)
		{
			i--;
			continue;
		}
		tileMap[randomInt]->setBomb(true);
	}

	tile_hidden = this->essentials->tile_hidden;
	tile_revealed = this->essentials->tile_revealed;
	mine = this->essentials->mine;
	number1 = this->essentials->number1;
	number2 = this->essentials->number2;
	number3 = this->essentials->number3;
	number4 = this->essentials->number4;
	number5 = this->essentials->number5;
	number6 = this->essentials->number6;
	number7 = this->essentials->number7;
	number8 = this->essentials->number8;
	flag = this->essentials->flag;

	populateTilePtrArrays();
	
};
Board::~Board()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			delete board[i][j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete[] board;

	for (int i = 0; i < 5; i++)
	{
		delete buttons[i];
	}
	delete mine_label;
};

int Board::getWidth()
{
	return width;
}

int Board::getHeight()
{
	return height;
}

void Board::drawBoard()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j]->Draw(window);
		}
	}
	for (int i = 0; i < 5; i++)
	{
		buttons[i]->Draw();
	}
	mine_label->Draw();
}

Tile* Board::FindTileClicked(int x, int y)
{
	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->checkIfClicked(x, y))
				return board[i][j];
		}
	}
	return nullptr;

}

Button* Board::FindButtonPressed(int x, int y)
{
	for (int i = 0; i < 5; i++)
	{
		if (buttons[i]->checkIfClicked(x, y))
			return buttons[i];
	}
	return nullptr;
}

void Board::populateTilePtrArrays()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 && j == 0)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j + 1];
				board[i][j]->tile_ptr_array[1] = board[i + 1][j + 1];
				board[i][j]->tile_ptr_array[2] = board[i + 1][j];
				board[i][j]->setTilesNear(3);
				continue;
			}
			else if (i == 0 && j == width - 1)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j - 1];
				board[i][j]->tile_ptr_array[1] = board[i + 1][j - 1];
				board[i][j]->tile_ptr_array[2] = board[i + 1][j];
				board[i][j]->setTilesNear(3);
				continue;
			}
			else if (i == height - 1 && j == 0)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j + 1];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j + 1];
				board[i][j]->tile_ptr_array[2] = board[i - 1][j];
				board[i][j]->setTilesNear(3);
				continue;
			}
			else if (i == height - 1 && j == width - 1)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j - 1];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j - 1];
				board[i][j]->tile_ptr_array[2] = board[i - 1][j];
				board[i][j]->setTilesNear(3);
				continue;
			}
			if (i == 0)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j - 1];
				board[i][j]->tile_ptr_array[1] = board[i + 1][j - 1];
				board[i][j]->tile_ptr_array[2] = board[i + 1][j];
				board[i][j]->tile_ptr_array[3] = board[i + 1][j + 1];
				board[i][j]->tile_ptr_array[4] = board[i][j + 1];
				board[i][j]->setTilesNear(5);
				continue;
			}
			else if (i == height - 1)
			{
				board[i][j]->tile_ptr_array[0] = board[i][j - 1];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j - 1];
				board[i][j]->tile_ptr_array[2] = board[i - 1][j];
				board[i][j]->tile_ptr_array[3] = board[i - 1][j + 1];
				board[i][j]->tile_ptr_array[4] = board[i][j + 1];
				board[i][j]->setTilesNear(5);
				continue;
			}
			if (j == 0)
			{
				board[i][j]->tile_ptr_array[0] = board[i - 1][j];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j + 1];
				board[i][j]->tile_ptr_array[2] = board[i][j + 1];
				board[i][j]->tile_ptr_array[3] = board[i + 1][j + 1];
				board[i][j]->tile_ptr_array[4] = board[i + 1][j];
				board[i][j]->setTilesNear(5);
				continue;
			}
			else if (j == width - 1)
			{
				board[i][j]->tile_ptr_array[0] = board[i - 1][j];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j - 1];
				board[i][j]->tile_ptr_array[2] = board[i][j - 1];
				board[i][j]->tile_ptr_array[3] = board[i + 1][j - 1];
				board[i][j]->tile_ptr_array[4] = board[i + 1][j];
				board[i][j]->setTilesNear(5);
				continue;
			}
			else
			{
				board[i][j]->tile_ptr_array[0] = board[i - 1][j-1];
				board[i][j]->tile_ptr_array[1] = board[i - 1][j];
				board[i][j]->tile_ptr_array[2] = board[i - 1][j + 1];
				board[i][j]->tile_ptr_array[3] = board[i][j + 1];
				board[i][j]->tile_ptr_array[4] = board[i + 1][j + 1];
				board[i][j]->tile_ptr_array[5] = board[i + 1][j];
				board[i][j]->tile_ptr_array[6] = board[i + 1][j - 1];
				board[i][j]->tile_ptr_array[7] = board[i][j - 1];
				board[i][j]->setTilesNear(8);
			}

		}
	}
}

void Board::RevealAll()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			board[i][j]->setReveal(true);
		}
	}
}

void Board::RevealAllBombsDebug()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->HasBomb())
				board[i][j]->debug_mode = !board[i][j]->debug_mode;
		}
	}
}

void Board::RevealAllBombs()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->HasBomb())
			{
				board[i][j]->debug_mode = true;
				board[i][j]->Reveal();
			}
		}
	}
}

void Board::HideAllBombs()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->HasBomb())
			{
				board[i][j]->debug_mode = false;
			}
		}
	}
}

void Board::FlagAllBombs()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (board[i][j]->HasBomb())
			{
				if (!board[i][j]->HasFlag())
					board[i][j]->setFlag(true);
				UpdateLabels();
			}
		}
	}
}

void Board::ResetBoard(int width, int height, int mine_count)
{
	//First, delete and reset dynamic memory data
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			delete board[i][j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	delete mine_label;
	tileMap.clear();
	
	//Deleting point ends, now changing/randomizing primary board data
	this->width = width;
	this->height = height;
	this->board_mine_amount = mine_count;
	this->mines_remaining = mine_count;
	this->tiles_left = width * height - board_mine_amount;
	this->gameIsLost = false;
	this->gameIsWon = false;

	//Change the game_state_button's texture
	buttons[0]->ChangeTexture(essentials->game_happening);

	mine_label = new Label(21, 32, essentials, this);
	
	
	int map_iter = 0;
	board = new Tile * *[height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new Tile * [width];
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Tile* tile_created = new Tile(j * 32, i * 32, this);
			board[i][j] = tile_created;
			tileMap[map_iter] = tile_created;
			map_iter++;
		}
	}
	for (int i = 0; i < board_mine_amount; i++)
	{
		int randomInt = 0 + rand() % (width * height - 1) + 1;
		cout << randomInt << endl;
		if (tileMap[randomInt]->HasBomb() == true)
		{
			i--;
			continue;
		}
		tileMap[randomInt]->setBomb(true);
	}
	populateTilePtrArrays();
}

void Board::BuildFromFile(string file_name)
{
	//Delete previous game related data, while maintaing core data that does not need to be replaced
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			delete board[i][j];
		}
	}

	for (int i = 0; i < height; i++)
	{
		delete[] board[i];
	}
	delete[] board;
	delete mine_label;
	tileMap.clear();

	if (file_read->is_open())
		file_read->close();
	file_read->open(file_name);
	int data_iter = 0;
	char* file_data = new char[width * height];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			file_read->get(file_data[data_iter]);
			data_iter++;
		}
		file_read->get();
	}
	file_read->close();
	//Creating the 2d Array structure in which Tiles will be stored
	board = new Tile * *[height];
	for (int i = 0; i < height; i++)
	{
		board[i] = new Tile * [width];
	}
	//Creating the tiles themselves, storing them in our 2d array
	board_mine_amount = 0;
	mines_remaining = 0;

	this->gameIsLost = false;
	this->gameIsWon = false;
	//Change the game_state_button's texture
	buttons[0]->ChangeTexture(essentials->game_happening);
	int map_iter = 0;
	int file_data_iter = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			Tile* tile_created = new Tile(j * 32, i * 32, this);

			if (file_data[file_data_iter] == '1')
			{
				tile_created->setBomb(true);
				board_mine_amount++;
				mines_remaining++;
			}
			board[i][j] = tile_created;
			tileMap[map_iter] = tile_created;
			
			
			map_iter++;
			file_data_iter++;
		}
	}
	this->tiles_left = width * height - board_mine_amount;

	//Deleting dynamically allocated array for file data
	delete[] file_data;
	mine_label = new Label(21, 32, essentials, this);

	//Populate the tile pointer arrays
	populateTilePtrArrays();

}

int Board::getMines()
{
	return mines_remaining;
}

void Board::setMines(int amount)
{
	mines_remaining = amount;
}

void Board::UpdateLabels()
{
	mine_label->UpdateLabels();
}

bool Board::GetIsGameLost()
{
	return gameIsLost;
}

void Board::decrementTilesLeft()
{
	tiles_left--;
}

bool Board::GetIsGameWon()
{
	if (gameIsWon || tiles_left == 0)
		return true;
	return false;
}

void Board::GameWon()
{
	gameIsWon = true;
	HideAllBombs();
	FlagAllBombs();
	//Changing the texture for the game_state button
	buttons[0]->ChangeTexture(essentials->game_won);

}


void Board::GameLost()
{
	gameIsLost = true;
	RevealAllBombs();
	//Changing the texture for the game_state button
	buttons[0]->ChangeTexture(essentials->game_lost);
}

void Board::PrintTilesLeft()
{
	cout << "The amount of tiles left to reveal: " << tiles_left << endl;
}