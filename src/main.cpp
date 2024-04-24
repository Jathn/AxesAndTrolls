#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "testmain.hpp"
#include "TileView.hpp"
#include "Game.hpp"
#include "GameInitializer.hpp"

int main() {
    bool testmode = false;
    if (testmode) {
        return testmain();
    }

    GameInitializer game_initializer;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Axes and Trolls");
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (!game_initializer.isDone()) {
                game_initializer.handleEvent(event);
            }
        }
        window.clear();
        if (!game_initializer.isDone()) {
            game_initializer.draw(window);
        } else {
            window.close();
        }
        game_initializer.draw(window);
        window.display();
    }
    
    return 0;
}