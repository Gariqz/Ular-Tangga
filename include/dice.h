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
    bool isRolling() const { return rolling; }

    void reset() {
    rolling = false;
    value = 1;
    diceValueText.setString(std::to_string(value));
    }

    void setValue(int val)
    {
    value = val;
    diceValueText.setString(std::to_string(value));
    rolling = false;
    }

    void setPosition(const sf::Vector2f& pos);


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
