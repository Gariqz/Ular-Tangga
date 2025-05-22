#include "Dice.h"
#include <cstdlib>
#include <ctime>

Dice::Dice(int size) : size(size), value(1), animationTime(0.f), rolling(false), diceShape(sf::Vector2f(size, size)), diceValueText(font, "")
{
    diceShape.setFillColor(sf::Color::White);
    diceShape.setOutlineColor(sf::Color::Black);
    diceShape.setOutlineThickness(2);

    if (!font.openFromFile("./build/bin/resources/Arial.ttf"))
        throw std::runtime_error("Failed to load font in Dice");

    diceValueText.setFont(font);
    diceValueText.setCharacterSize(size / 2);
    diceValueText.setFillColor(sf::Color::Black);
    diceValueText.setStyle(sf::Text::Bold);
    diceValueText.setString(std::to_string(value));
    diceValueText.setPosition({diceShape.getPosition().x + size / 3, diceShape.getPosition().y + size / 6});
}

void Dice::setPosition(const sf::Vector2f& pos)
{
    diceShape.setPosition(pos);
    diceValueText.setPosition(sf::Vector2f(pos.x + size / 3.f, pos.y + size / 6.f));
}

void Dice::render(sf::RenderWindow& window) const
{
    window.draw(diceShape);
    window.draw(diceValueText);
}

void Dice::roll()
{
    rolling = true;
    animationTime = 0.f;
}

int Dice::getValue() const
{
    return value;
}

void Dice::updateAnimation(float deltaTime)
{
    if (!rolling) return;

    animationTime += deltaTime;
    if (animationTime > 1.f)
    {
        rolling = false;
        value = rand() % 6 + 1;
        diceValueText.setString(std::to_string(value));
    }
    else
    {
        int randomValue = rand() % 6 + 1;
        diceValueText.setString(std::to_string(randomValue));
    }
}
