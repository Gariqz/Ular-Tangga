#include "Game.h"
#include <iostream>
#include <ctime>

Game::Game()
    : window(sf::VideoMode({600, 600}), "Ular Tangga"),
      board(10, 10, 50),
      dice(50),
      currentPlayerIndex(0),
      gameOver(false),
      infoText(font, "")
{
    srand(static_cast<unsigned>(time(nullptr)));

    if (!font.openFromFile("./build/bin/resources/Arial.ttf"))
    {
        std::cerr << "Failed to load font\n";
        // Handle gracefully
    }

    infoText.setFont(font);
    infoText.setCharacterSize(20);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition({10, 560});

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
    while (const std::optional<sf::Event> event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (event->is<sf::Event::KeyPressed>())
        {
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();
            if (!gameOver && keyEvent->code == sf::Keyboard::Key::Space)
            {
                dice.roll();
                turnInProgress = true;
            }
            else if (gameOver && keyEvent->code == sf::Keyboard::Key::R)
            {
                reset();
            }
        }
    }
}

void Game::update(float deltaTime)
{
    dice.updateAnimation(deltaTime);

    if (!dice.isRolling() && dice.getValue() != 0 && !gameOver && turnInProgress)
    {
        int rollValue = dice.getValue();

        moveCurrentPlayer(rollValue);
        checkSnakesAndLadders();

        // Cek menang
        if (players[currentPlayerIndex].getPosition() >= 100)
        {
            infoText.setString("Player " + std::to_string(players[currentPlayerIndex].getId()) + " menang! Tekan R untuk reset.");
            gameOver = true;
        }
        else
        {
            nextTurn();
        }

        turnInProgress = false;
    }
}

void Game::render()
{
    window.clear(sf::Color::White);

    board.render(window);

    for (auto& player : players)
    {
        sf::Vector2f pos = board.getTilePosition(player.getPosition());
        player.setTokenPosition(pos);  // supaya token pas di tengah tile
        player.render(window);
    }


    // Render dadu
    dice.setPosition({10.f, 540.f});  // atau sesuaikan posisi dice di window kamu
    dice.render(window);

    // Render teks info (misal status game)
    window.draw(infoText);

    window.display();
}

void Game::reset()
{
    for (auto& player : players)
        player.setPosition(1);

    currentPlayerIndex = 0;
    gameOver = false;
    dice.reset();
    turnInProgress = false;
    infoText.setString("Player 1's turn. Tekan Space buat roll!");
}

void Game::moveCurrentPlayer(int steps)
{
    Player& player = players[currentPlayerIndex];
    int newPos = player.getPosition() + steps;

    if (newPos > board.getTileCount()) // board.getTileCount() biar scalable kalau ubah ukuran
    {
        newPos = player.getPosition(); // kalau lebih, stay
    }

    player.setPosition(newPos);

    // Cek menang
    if (newPos == board.getTileCount())
    {
        gameOver = true;
        infoText.setString("Player " + std::to_string(player.getId()) + " menang! Tekan R untuk restart");
    }
    else
    {
        // Update infoText biasa kalau belum menang
        infoText.setString("Player " + std::to_string(player.getId()) + " moved to " + std::to_string(newPos));
    }
}

void Game::checkSnakesAndLadders()
{
    Player& player = players[currentPlayerIndex];
    int pos = player.getPosition();

    if (snakesAndLadders.count(pos))
    {
        int destination = snakesAndLadders[pos];
        player.setPosition(destination);

        // Update info text sesuai ular/tangga
        if (destination > pos)
            infoText.setString("Player " + std::to_string(player.getId()) + " naik tangga ke " + std::to_string(destination));
        else
            infoText.setString("Player " + std::to_string(player.getId()) + " turun ular ke " + std::to_string(destination));
    }
}



void Game::nextTurn()
{
    Player& player = players[currentPlayerIndex];
    if (player.getPosition() == 100)
    {
        infoText.setString("Player " + std::to_string(player.getId()) + " MENANG! Tekan R untuk reset.");
        gameOver = true;
        return;
    }

    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

    infoText.setString("Giliran Player " + std::to_string(players[currentPlayerIndex].getId()) + ". Tekan Spasi untuk lempar dadu.");
}


