#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "TileView.hpp"
#include "Game.hpp"
#include "GameInitializer.hpp"
#include "PlacementPhase.hpp"

int main() {

    GameInitializer game_initializer;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Axes and Trolls");
    sf::Font font;
    if (!font.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Axes and Trolls");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(800, 500);
    window.draw(text);
    window.display();
    std::shared_ptr<GameStateManager> game_state_manager = std::make_shared<GameStateManager>(std::make_pair<int, int>(22, 14), 2);
    Game game = Game(game_state_manager);
    std::shared_ptr<Phase> placement_phase = std::make_shared<PlacementPhase>(game.getStateManager(), game.getGraphicsManager());
    
    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!game_initializer.isDone()) {
                game_initializer.handleEvent(event, game.getStateManager(), game.getGraphicsManager());
            } else {
                game.handleEvent(event, placement_phase);
            }
        }

        window.clear();
        if (!game_initializer.isDone()) {
            game_initializer.draw(window);
        } else {
            game.draw(window);
        }
        window.display();
    }
    
    return 0;
}