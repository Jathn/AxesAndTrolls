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
    std::shared_ptr<Territory> territory = std::make_shared<Territory>();
    MovementHandler movementHandler = MovementHandler(territory);
    for (int i = 0; i < 9; i++) {
        std::shared_ptr<Unit> unit = std::make_shared<Unit>(UnitType::INFANTRY);
        tile->addUnit(unit);
        unit->setTile(tile);
        movementHandler.addUnit(unit);
    }
    std::shared_ptr<Tile> tile2 = std::make_shared<Tile>(1, 1, 0, std::vector<std::shared_ptr<Tile>>({tile}), false, TileType::GRASS);
    TileView tileView(tile);
    TileView tileView2(tile2);
    tile->addNeighbor(tile2);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "TileView Test");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                movementHandler.moveUnit(tile->getUnits()[0].lock(), tile2);
            }
        }
        window.clear();
        tileView.draw(window);
        tileView2.draw(window);
        window.display();
    }
    return 0;
}