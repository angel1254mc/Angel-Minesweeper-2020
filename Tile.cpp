#include "Tile.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
using namespace std;
vector<Tile*> Tile::tiles_checked;
Tile::Tile(int xPos, int yPos, Board* game_board)
{
	this->posX = xPos;
	this->posY = yPos;
	this->game_board = game_board;
	this->posVector = sf::Vector2f((float)posX, (float)posY);
	this->boolBomb = false;
	this->boolFlag = false;
	this->boolIsRevealed = false;
	this->drawOverSprite = false;
	this->intMinesNear = 0;
	this->tilesNear = 0;
	this->tile_ptr_array = new Tile * [8];
}

void Tile::setReveal(bool rev)
{
	boolIsRevealed = rev;
}

void Tile::setFlag(bool flag)
{
	if (boolIsRevealed == true)
		return;
	boolFlag = flag;
	if (boolFlag == true)
	{
		game_board->setMines(game_board->getMines() - 1);
	}
	else
	{
		game_board->setMines(game_board->getMines() + 1);
	}
}

void Tile::setBomb(bool bomb)
{
	boolBomb = bomb;
}

bool Tile::HasBomb()
{
	return boolBomb;
}

bool Tile::HasFlag()
{
	return boolFlag;
}

void Tile::Reveal()
{
	if (boolIsRevealed == true)
		return;
	if (intMinesNear == 0 && !HasBomb())
	{
		this->boolIsRevealed = true;
		game_board->decrementTilesLeft();
		for (int i = 0; i < tilesNear; i++)
		{
			if (tile_ptr_array[i]->intMinesNear == 0 && find(tiles_checked.begin(), tiles_checked.end(), tile_ptr_array[i]) == tiles_checked.end() && !(tile_ptr_array[i]->HasFlag()))
			{
				tiles_checked.push_back(tile_ptr_array[i]);
				tile_ptr_array[i]->Reveal();
			}
			else if (tile_ptr_array[i]->intMinesNear != 0 && find(tiles_checked.begin(), tiles_checked.end(), tile_ptr_array[i]) == tiles_checked.end() && !(tile_ptr_array[i]->HasFlag()))
			{
				//If this tile hasn't been revealed before... decrement tiles left to reveal
				if (!tile_ptr_array[i]->boolIsRevealed)
				{
					game_board->decrementTilesLeft();
				}
				tile_ptr_array[i]->setReveal(true);
			}
		}
		return;
	}
	//This else corresponds to the tile either having an amount of mines near or being a mine itself
	else
	{
		setReveal(true);
		//If this is not a bomb, 
		if (!HasBomb())
			game_board->decrementTilesLeft();
		return;
	}
}

void Tile::ClearReveal()
{
	tiles_checked.clear();
}

void Tile::UpdateTexture()
{
	sprite_over.setColor(sf::Color::White);
	sprite.setTexture(game_board->tile_hidden);
	checkMinesNear();
	if (intMinesNear == 1)
		mines_near_sprite = game_board->number1;
	else if (intMinesNear == 2)
		mines_near_sprite = game_board->number2;
	else if (intMinesNear == 3)
		mines_near_sprite = game_board->number3;
	else if (intMinesNear == 4)
		mines_near_sprite = game_board->number4;
	else if (intMinesNear == 5)
		mines_near_sprite = game_board->number5;
	else if (intMinesNear == 6)
		mines_near_sprite = game_board->number6;
	else if (intMinesNear == 7)
		mines_near_sprite = game_board->number7;
	else if (intMinesNear == 8)
		mines_near_sprite = game_board->number8;
	if (HasBomb())
	{
		mines_near_sprite = game_board->mine;
	}
	if (boolIsRevealed)
	{
		sprite.setTexture(game_board->tile_revealed);
		sprite_over.setTexture(mines_near_sprite);
		debug_sprite.setTexture(mines_near_sprite);
		drawOverSprite = true;
		if (boolFlag && boolBomb)
		{
			sprite_over.setTexture(game_board->flag);
		}
		else if (boolBomb)
		{
			sprite_over.setTexture(game_board->mine);
		}
		else if (intMinesNear == 0)
			sprite_over.setColor(sf::Color::Transparent);
	}
	else
	{	
		if (boolFlag)
		{
			sprite_over.setTexture(game_board->flag);
			drawOverSprite = true;
		}
		else
		{
			drawOverSprite = false;
			if (intMinesNear == 0)
				sprite_over.setColor(sf::Color::Transparent);
			else
				sprite_over.setTexture(mines_near_sprite);
		}
		 //This is where I left off
	}
}

void Tile::Draw(sf::RenderWindow* window)
{
	UpdateTexture();
	debug_sprite.setTexture(game_board->mine);
	sprite.setPosition(posVector);
	sprite_over.setPosition(posVector);
	window->draw(sprite);
	if (drawOverSprite)
		window->draw(sprite_over);
	if (debug_mode == true)
	{
		debug_sprite.setPosition(posVector);
		window->draw(debug_sprite);
	}

}

bool Tile::checkIfClicked(int xCoord, int yCoord)
{
	if (xCoord >= posX && xCoord <= posX + 32 && yCoord >= posY && yCoord <= posY + 32)
		return true;
	return false;
}

void Tile::checkMinesNear()
{
	intMinesNear = 0;
	for (int i = 0; i < tilesNear; i++)
	{
		if (tile_ptr_array[i]->HasBomb())
			intMinesNear = intMinesNear + 1;
	}
}

void Tile::setTilesNear(int num)
{
	tilesNear = num;
}

void Tile::Print()
{
	cout << "This tile has " << intMinesNear << " mines surrounding it." << endl;
	cout << "This tile is positioned at x = " << posX << " and y = " << posY << endl;
	cout << "This tile has a bomb? -- " << boolBomb << endl;
	cout << "This tile has a flag? -- " << boolFlag << endl;
}