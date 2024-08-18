#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "TileView.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "GameInitializer.hpp"
#include "PlacementPhase.hpp"
#include <SFML/Audio.hpp>

int main() {
    GameInitializer game_initializer = GameInitializer();
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Axes and Trolls", sf::Style::Fullscreen);
    Menu menu = Menu();
    sf::Texture loadingTexture;
    sf::Texture backgroundTexture;
    if (!loadingTexture.loadFromFile("../resources/pics/loading_screen.png")) {
        // handle error loading texture
    }

    if (!backgroundTexture.loadFromFile("../resources/pics/background.png")) {
        // handle error loading texture
    }

    /* Background image Init */
    sf::Sprite loadingSprite(loadingTexture);
    sf::Sprite backgroundSprite(backgroundTexture);

    loadingSprite.setPosition(0, 0);
    backgroundSprite.setPosition(0, 0);

    /* Draw loading sprite once */
    window.draw(loadingSprite);
    window.display();

    /* Button Init */
    Button exit_button = Button("Exit", std::make_pair<int, int>(100, 30), std::make_pair<int, int>(1820, 0));
    Button music_button = Button("Music", std::make_pair<int, int>(100, 30), std::make_pair<int, int>(1720, 0));
    
    /* Music Init */
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("../resources/sound/click.wav")) {
        throw std::runtime_error("Could not load sound");
    }
    sf::Sound sound;
    sf::Music music;

    if (!music.openFromFile("../resources/sound/menu_music.ogg")) {
        throw std::runtime_error("Could not load music");
    }

    music.setLoop(true);
    music.play();

    /* Game Init */
    std::shared_ptr<GameStateManager> game_state_manager = std::make_shared<GameStateManager>(std::make_pair<int, int>(22, 14), 2);
    std::shared_ptr<Game> game = std::make_shared<Game>(game_state_manager);

    /* Game Over text Load */
    sf::Font font;
    if (!font.loadFromFile("../resources/fonts/TTF/Crimson-Bold.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    sf::Text game_over_text;
    game_over_text.setFont(font);
    game_over_text.setCharacterSize(50);
    game_over_text.setPosition(800, 800);
    /* Loop */
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!menu.getGameActivated()) {
                menu.handleEvent(event, window);
            } else {
                if (!game_initializer.isDone()) {
                    game_initializer.handleEvent(event, game->getStateManager(), game->getGraphicsManager());
                } else {
                    game->handleEvent(event, window);
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sound.setBuffer(buffer);
                sound.play();
                if (exit_button.isInside(event.mouseButton.x, event.mouseButton.y)) {
                    window.close();
                }
                if (music_button.isInside(event.mouseButton.x, event.mouseButton.y)) {
                    if (music.getStatus() == sf::Music::Playing) {
                        music.pause();
                    } else {
                        music.play();
                    }
                }
            }
        }
        window.clear();
        window.draw(backgroundSprite);
        if (!menu.getGameActivated()) {
            window.draw(loadingSprite);
            menu.draw(window);
        } else {
            if (!game_initializer.isDone()) {
                game_initializer.draw(window);
            } else {
                game->draw(window);
                if (game->getStateManager()->isGameOver()) {
                    std::shared_ptr<Player> winner = game->getStateManager()->getWinner();
                    game_over_text.setString("Game Over! " + winner->getName() + " wins!");
                    game_over_text.setFillColor(winner->getColor());
                }
            }
        }
        exit_button.draw(window);
        music_button.draw(window);
        window.display();
    }
    
    return 0;
}