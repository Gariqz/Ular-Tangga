#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(int id, sf::Color color, int startTile, int tileSize);
    void render(sf::RenderWindow& window) const;
    void setPosition(int tileNumber);
    int getPosition() const;

private:
    int id;
    sf::Color color;
    int tilePosition;  // nomor petak pemain saat ini
    int tileSize;
    sf::CircleShape token;
};

#endif
