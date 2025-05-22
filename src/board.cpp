#include "Board.h"
#include <iostream>

Board::Board(int rows, int cols, int tileSize) : rows(rows), cols(cols), tileSize(tileSize)
{
    tiles.resize(rows * cols);

    bool alternate = false;

    for (int i = 0; i < rows * cols; i++)
    {
        tiles[i].setSize(sf::Vector2f(tileSize - 2, tileSize - 2));
        tiles[i].setOutlineThickness(1);
        tiles[i].setOutlineColor(sf::Color::Black);
        tiles[i].setFillColor(alternate ? sf::Color(200, 200, 200) : sf::Color(150, 150, 150));

        // Hitung posisi tile dengan zigzag pattern
        int row = i / cols;
        int col = i % cols;
        if (row % 2 == 1)
            col = cols - 1 - col;

        tiles[i].setPosition(sf::Vector2f(col * tileSize, (rows - 1 - row) * tileSize));

        alternate = !alternate;
        if ((i + 1) % cols == 0) alternate = !alternate;
    }
}

int Board::getTileCount() const
{
    return rows * cols;
}

void Board::render(sf::RenderWindow& window) const
{
    static sf::Font font;
    static bool fontLoaded = false;
    if (!fontLoaded)
    {
        if (!font.openFromFile("./build/bin/resources/Arial.ttf"))
            std::cerr << "Failed to load font in Board\n";
        fontLoaded = true;
    }

    for (int i = 0; i < rows * cols; i++)
    {
        window.draw(tiles[i]);
        sf::Text text(font);
        text.setString(std::to_string(i + 1));
        text.setCharacterSize(tileSize / 3);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(tiles[i].getPosition().x + 5, tiles[i].getPosition().y + 5));
        window.draw(text);
    }
}


sf::Vector2f Board::getTilePosition(int tileNumber) const
{
    if (tileNumber < 1) tileNumber = 1;
    if (tileNumber > rows * cols) tileNumber = rows * cols;

    int index = tileNumber - 1;
    int row = index / cols;
    int col = index % cols;
    if (row % 2 == 1) // zigzag pattern
        col = cols - 1 - col;

    float x = col * tileSize + tileSize / 2.f;
    float y = (rows - 1 - row) * tileSize + tileSize / 2.f;

    return {x, y};
}
