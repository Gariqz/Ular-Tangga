#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include <vector>

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    Board board;
    std::vector<Player> players;
    Dice dice;
    int currentPlayerIndex;
    bool gameOver;

    sf::Font font;
    sf::Text infoText;

    void processEvents();
    void update(float deltaTime);
    void render();
    void reset();
    void nextTurn();
    void moveCurrentPlayer(int steps);
    void checkSnakesAndLadders();
};

#endif
