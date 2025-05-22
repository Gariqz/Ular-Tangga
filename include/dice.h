#ifndef DICE_H
#define DICE_H

#include <SFML/Graphics.hpp>

class Dice
{
public:
    Dice(int size);
    void render(sf::RenderWindow& window) const;
    void roll();
    int getValue() const;
    void updateAnimation(float deltaTime);

private:
    int size;
    int value;
    float animationTime;
    bool rolling;
    sf::RectangleShape diceShape;
    sf::Text diceValueText;
    sf::Font font;
};

#endif
