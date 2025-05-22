#include "Board.h"
#include <iostream>

Board::Board(int rows, int cols, int tileSize) : rows(rows), cols(cols), tileSize(tileSize)
{
    tiles.reserve(rows * cols);
    bool alternate = false;

    for (int i = 0; i < rows * cols; i++)
    {
        sf::RectangleShape tile(sf::Vector2f(tileSize - 2, tileSize - 2));
        tile.setOutlineThickness(1);
        tile.setOutlineColor(sf::Color::Black);
        tile.setFillColor(alternate ? sf::Color(200, 200, 200) : sf::Color(150, 150, 150));
        tiles.push_back(tile);
        alternate = !alternate;
        if ((i + 1) % cols == 0) alternate = !alternate;
    }
}

void Board::render(sf::RenderWindow& window) const
{
    for (int i = 0; i < rows * cols; i++)
    {
        int row = i / cols;
        int col = i % cols;

        // buat zigzag numbering (snake pattern)
        if (row % 2 == 1)
            col = cols - 1 - col;

        tiles[i].setPosition(col * tileSize, (rows - 1 - row) * tileSize);
        window.draw(tiles[i]);

        // nomornya kita gambar pake SFML text, biar kelihatan
        // bisa dipikirkan optimasi supaya text cuma dibuat sekali, ini simple
        sf::Text text;
        static sf::Font font;
        static bool fontLoaded = false;
        if (!fontLoaded)
        {
            if (!font.loadFromFile("resources/Arial.ttf"))
                std::cerr << "Failed to load font in Board\n";
            fontLoaded = true;
        }
        text.setFont(font);
        text.setString(std::to_string(i + 1));
        text.setCharacterSize(tileSize / 3);
        text.setFillColor(sf::Color::Black);
        text.setPosition(tiles[i].getPosition().x + 5, tiles[i].getPosition().y + 5);
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
