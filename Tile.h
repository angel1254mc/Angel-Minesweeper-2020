#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
using namespace std;
class Board;
class Tile
{
	sf::Sprite sprite;
	sf::Sprite sprite_over;
	sf::Sprite debug_sprite;
	sf::Texture mines_near_sprite;
	Board* game_board;
	int posX;
	int posY;
	sf::Vector2f posVector;
	static vector<Tile*> tiles_checked;

	bool boolBomb;
	bool boolFlag;
	bool boolIsRevealed;
	bool drawOverSprite;
	int intMinesNear;
	int tilesNear;
	public:
		//Debug mode enables the drawing of a debug_sprite, which displays what is hidden under a tile above all other things currently displayed in that tile. Has no effect on interaction with said tile, though.
		//Essentially works as a sort of xray vision
		bool debug_mode = false;
		
		Tile** tile_ptr_array;
		//Tile constructor that takes xPos, yPos, and a pointer to the Board
		Tile(int xPos, int yPos, Board* game_board);
		//Sets the state of the tile- Revealed or not?
		void setReveal(bool rev);
		//Sets whether the bomb has a tile or not
		void setBomb(bool bomb);
		//Sets whether or not the tile has a flag on it or not
		void setFlag(bool flag);
		//Sets the amount of tiles near (for looping purposes)
		void setTilesNear(int num);
		//Sets the amount of mines near the tile
		void checkMinesNear();
		//Returns whether or not the tile has a bomb
		bool HasBomb();
		//Returns whether or not tile has a flag
		bool HasFlag();
		//Updates the texture of the sprites, both the over_sprite and the regular tile_sprite;
		void UpdateTexture();
		//Reveals the tile. Makes use of a static vector shared among all tile objects, which must be clear using RevealedClear()
		void Reveal();
		//Clears the static tile vector where revealed 
		void ClearReveal();
		//Flags the tile
		void Flag();
		//sets any preconfigurations before drawing the tile
		void Draw(sf::RenderWindow* window);
		//Checks if the x and y coords of mouse upon click allign with the position of the tile object. If so, returns true
		bool checkIfClicked(int xCoord, int yCoord);
		//Prints info about the tile
		void Print();
	

	
};

