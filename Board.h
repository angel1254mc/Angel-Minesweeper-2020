#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Tile.h"
#include "WindowEssentials.h"
#include "Button.h"
#include "Label.h"
using namespace std; 
class Label;
class Tile;
class Button;
class Board
{
	int width;
	int height;
	int board_mine_amount;
	int mines_remaining;
	int tiles_left;
	bool gameIsLost;
	bool gameIsWon;
	
	WindowEssentials* essentials;
	map<int, Tile*> tileMap;
	Tile*** board; 
	sf::RenderWindow* window; //Window that the board will be built on
	Button* buttons[5];
	Label* mine_label;
	ifstream* file_read;
public:

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
	
	
		//Board constructor, which takes width and height to create a Tile 2D array with amount of tiles equal to width*height
		Board(int width, int height,int mine_count, sf::RenderWindow* window, WindowEssentials* essential, ifstream* file_read);
		//Populates the pointer arrays of each tile. These arrays will be used to decide the number of mines near the tile
		void populateTilePtrArrays();
		//Draws the board
		void drawBoard();
		//This function destroys Tile textures, leaving an empty window as a result of either: 1. The player hitting the close button, or 2. The player starting another game
		void DestroyBoard();
		//This function loads the necessary textures to be used in 
		void LoadTextures();
		//Board object destructor, if necessary
		~Board();
		//Gets the amount of mines LEFT (not mines at the beginning of the game)
		int getMines();
		//Sets the amount of mines LEFT
		void setMines(int amount);
		//Decrements the amount of tiles left unrevealed
		void decrementTilesLeft();
		//Get the width and height (in boxes/cubes) of the board respectively
		int getWidth();
		int getHeight();
		//Goes through the loss animation, including revealing all remaining bomb tiles and changing to sad face :(
		void GameLost();
		//Goes through the win animation, including flagging all bombs and changing to the cool face B-)
		void GameWon();
		//Gets the game state- if game is lost, GetIsGameLost returns true, if game is won, GetIsGameWon returns true
		bool GetIsGameLost();
		bool GetIsGameWon();
		//CheckTilePressed loops over all the tiles with mouse coordinates, returns the tile that was pressed according to mouse position
		Tile* FindTileClicked(int x, int y);
		//CheckButtonPressed loops over buttons to detect which one was clicked, if any was clicked;
		Button* FindButtonPressed(int x, int y);
		//Reveals all tiles
		void RevealAll();
		//Reveals all bombs, in a "losing the game" fashion. Non-reversible until a new game is begun
		void RevealAllBombs();
		//Reveals all bombs, in a "debugging" fashion where it can be reversed when called again
		void RevealAllBombsDebug();
		//Hides all bombs, mainly used in the GameWon process for deactivating debug mode;
		void HideAllBombs();
		//Flags all the bombs, used in the winning animation of the game
		void FlagAllBombs();
		//Resets the board
		void ResetBoard(int width, int height, int mine_count);
		//Resets the board and builds using a .brd file
		void BuildFromFile(string filename);
		//Function that allows labels to update
		void UpdateLabels();
		//Prints tiles left to be revealed for debugging purposes
		void PrintTilesLeft();

};

