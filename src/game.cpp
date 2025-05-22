#include "Game.h"
#include <iostream>
#include <ctime>

Game::Game()
    : window(sf::VideoMode(600, 600), "Ular Tangga"),
      board(10, 10, 50),
      dice(50),
      currentPlayerIndex(0),
      gameOver(false)
{
    srand(static_cast<unsigned>(time(nullptr)));

    if (!font.loadFromFile("resources/Arial.ttf"))
    {
        std::cerr << "Failed to load font\n";
        // Handle gracefully
    }

    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition(10, 560);

    // Setup 2 players
    players.emplace_back(1, sf::Color::Red, 1, 50);
    players.emplace_back(2, sf::Color::Blue, 1, 50);
}

void Game::run()
{
    sf::Clock clock;
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed)
        {
            if (!gameOver && event.key.code == sf::Keyboard::Space)
            {
                dice.roll();
            }
            else if (gameOver && event.key.code == sf::Keyboard::R)
            {
                reset();
            }
        }
    }
}

void Game::update(float deltaTime)
{
    dice.updateAnimation(deltaTime);

    if (!dice.rolling && dice.getValue() != 0 && !gameOver)
    {
        moveCurrentPlayer(dice.getValue());
        checkSnakesAndLadders();
        nextTurn();
    }
}

void Game::render()
{
    window.clear(sf::Color::White);

    board.render(window);

    // Render
