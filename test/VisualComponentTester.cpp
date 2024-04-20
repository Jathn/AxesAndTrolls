#include "VisualComponentTester.hpp"

VisualComponentTester::VisualComponentTester() : Tester() {}

std::pair<int, int> VisualComponentTester::runTest() {
    GameStateManager gameStateManager(std::make_pair<int, int>(11, 7));
    GameGraphicsManager gameGraphicsManager(gameStateManager);
    gameStateManager.getPlayers()[0]->setName("Jonneboii");
    gameStateManager.getPlayers()[1]->setName("Pelle faderlos");
    std::shared_ptr<Tile> tile = gameStateManager.getMap()[0];
    std::shared_ptr<Territory> territory = std::make_shared<Territory>();
    MovementHandler movementHandler = MovementHandler(territory);
    for (int i = 0; i < 9; i++) {
        std::shared_ptr<Unit> unit = std::make_shared<Unit>(UnitType::INFANTRY);
        tile->addUnit(unit);
        unit->setTile(tile);
        movementHandler.addUnit(unit);
    }
    std::shared_ptr<Tile> tile2 = gameStateManager.getMap()[1];
    tile->addNeighbor(tile2);
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Axes and Trolls");
    gameStateManager.getPlayers()[0]->getTerritory()->addTile(gameStateManager.getMap()[4]);
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
        gameGraphicsManager.draw(window);
        window.display();
    }

    return std::pair<int, int>(0, 0);
}