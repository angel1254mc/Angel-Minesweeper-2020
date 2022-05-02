#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <map>
#include "Board.h"
#include "Tile.h"
#include "WindowEssentials.h"
using namespace std;

int main()
{
    srand((unsigned int)time(0));
    ifstream* file_read =  new ifstream();
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
    file_read->close();
    WindowEssentials essentials(width_boxes, height_boxes);
    Board* GameBoard = new Board(width, height, mines, essentials.render_window, &essentials, file_read);
    sf::RenderWindow* Window = essentials.render_window;
  
    while (Window->isOpen())
    {
        sf::Event event;
        while (Window->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                Tile* tile_pressed = GameBoard->FindTileClicked(x, y);
                Button* button_pressed = GameBoard->FindButtonPressed(x, y);
                switch (event.key.code)
                {

                    case sf::Mouse::Left:
                        //Only execute while tile_pressed exists and game is not lost or won
                        GameBoard->PrintTilesLeft();
                        if (tile_pressed != nullptr && !(GameBoard->GetIsGameLost() || GameBoard->GetIsGameWon()))
                        {
                            tile_pressed->Print();

                            if (tile_pressed->HasFlag())
                                continue;
                            tile_pressed->Reveal();
                            tile_pressed->ClearReveal();

                            //If pressed bomb, game is lost
                            if (tile_pressed->HasBomb() == true)
                                GameBoard->GameLost();
                            //If no tiles remain, game is won
                            if (GameBoard->GetIsGameWon())
                                GameBoard->GameWon();
                        }
                        if (button_pressed != nullptr)
                        {
                            cout << "Button was pressed" << endl;
                            button_pressed->SpecialFunction();
                            GameBoard->UpdateLabels();
                        }
                        break;
                    case sf::Mouse::Right:
                        //Switches between flagged and not flagged.
                        //Only execute if tile_pressed exists and game is not lost
                        if (tile_pressed == nullptr || GameBoard->GetIsGameLost() || GameBoard->GetIsGameWon())
                            break;
                        tile_pressed->setFlag(!tile_pressed->HasFlag());
                        GameBoard->UpdateLabels();
                }
            }
            if (event.type == sf::Event::Closed)
            {
                essentials.render_window->close();
                return 0;
            }
        }

       Window->clear();
       GameBoard->drawBoard();
       Window->display();
    }

    return 0;
}
