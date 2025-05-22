#include "Player.h"

Player::Player(int id, sf::Color color, int startTile, int tileSize)
    : id(id), color(color), tilePosition(startTile), tileSize(tileSize), token(tileSize / 3.f)
{
    token.setFillColor(color);
    token.setOutlineColor(sf::Color::Black);
    token.setOutlineThickness(2);
}

void Player::render(sf::RenderWindow& window) const
{
    // posisi token akan di set dari Game (karena perlu posisi pixel)
    window.draw(token);
}

void Player::setPosition(int tileNumber)
{
    tilePosition = tileNumber;
}

int Player::getPosition() const
{
    return tilePosition;
}
