#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Board
{
public:
    Board(int rows, int cols, int tileSize);
    void render(sf::RenderWindow& window) const;
    sf::Vector2f getTilePosition(int tileNumber) const; // nomor petak => posisi pixel
    int getRows() const { return rows; }
    int getCols() const { return cols; }

private:
    int rows;
    int cols;
    int tileSize;
    std::vector<sf::RectangleShape> tiles;
};

#endif
