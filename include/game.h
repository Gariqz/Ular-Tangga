#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include <vector>
#include <map>

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

    std::map<int, int> snakesAndLadders;
    sf::Font font;
    sf::Text infoText;

    bool turnInProgress;
    void processEvents();
    void update(float deltaTime);
    void render();
    void reset();
    void nextTurn();
    void moveCurrentPlayer(int steps);
    void checkSnakesAndLadders();
};

#endif
