#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "../include/testmain.hpp"
#include "../include/TileView.hpp"

int main() {
    // bool testmode = true;
    // if (testmode) {
    //     return testmain();
    // }
    std::shared_ptr<Tile> tile = std::make_shared<Tile>(0, 0, 0, std::vector<std::shared_ptr<Tile>>(), false, TileType::FOREST);
    TileView tileView(tile);
    sf::RenderWindow window(sf::VideoMode(800, 600), "TileView Test");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        tileView.draw(window);
        window.display();
    }
    return 0;
}