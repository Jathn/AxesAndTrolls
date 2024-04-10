#include "VisualComponentTester.hpp"

VisualComponentTester::VisualComponentTester() : Tester() {}

std::pair<int, int> VisualComponentTester::runTest() {
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

    std::shared_ptr<Player> player = std::make_shared<Player>();

    PlayerView playerView(player, std::pair<int, int>(0, 0), std::pair<int, int>(400, 200));
    sf::RenderWindow window2(sf::VideoMode(1920, 1080), "PlayerView Test");
    while (window2.isOpen()) {
        sf::Event event;
        while (window2.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window2.close();
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                player->addResource(ResourceType::GOLD, 100);
            }
        }
        window2.clear();
        playerView.draw(window2);
        window2.display();
    }

    return std::pair<int, int>(0, 0);
}