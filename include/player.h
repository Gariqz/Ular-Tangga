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
    sf::CircleShape token;
    void setTokenPosition(const sf::Vector2f& pos) 
    {
    token.setPosition(sf::Vector2f(pos.x - token.getRadius(), pos.y - token.getRadius()));
    }
    int getId() const;

private:
    int id;
    sf::Color color;
    int tilePosition;  // nomor petak pemain saat ini
    int tileSize;
};

#endif
