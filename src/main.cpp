#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "TileView.hpp"
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

    sf::Sprite loadingSprite(loadingTexture);
    sf::Sprite backgroundSprite(backgroundTexture);

    loadingSprite.setPosition(0, 0);
    backgroundSprite.setPosition(0, 0);

    window.draw(loadingSprite);
    window.display();
    sf::Music music;
    if (!music.openFromFile("../resources/sound/menu_music.ogg")) {
        throw std::runtime_error("Could not load music");
    }
    music.setLoop(true);
    music.play();
    std::shared_ptr<GameStateManager> game_state_manager = std::make_shared<GameStateManager>(std::make_pair<int, int>(22, 14), 2);
    std::shared_ptr<Game> game = std::make_shared<Game>(game_state_manager);
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
            }
        }
        window.display();
    }
    
    return 0;
}