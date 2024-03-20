#include "RunAroundTester.hpp"

RunAroundTester::RunAroundTester() : Tester() { }


std::pair<int, int> RunAroundTester::runTest() {
    
        std::cout << "### RunAround test ###" << std::endl;
    
        std::pair<int, int> map_size = std::make_pair(10, 6);
        gameStateManager = GameStateManager(map_size);
        std::shared_ptr<Territory> territory = std::make_shared<Territory>();
        movementHandler = MovementHandler(territory);
        int current_id = 0;
    
        std::cout << "Creating a unit..." << std::endl;
        std::shared_ptr<Unit> unit = std::make_shared<Unit>(current_id, UnitType::DRAGON);
        unit->setTile(gameStateManager.getMap().at(0));

        movementHandler.addUnit(unit);
        char command = 'n';

        while (command != 'q') {
            auto availableTiles = movementHandler.getAvailableTiles(unit);
            auto currentTile = unit->getTile();
            for (int i = 0; i < map_size.second; ++i) {
                for (int j = 0; j < map_size.first; ++j) {
                    auto tile = gameStateManager.getMap().at(i * map_size.first + j);
                    if (tile == currentTile) {
                        std::cout << "(" << tile->getTypeChar() << ", C) ";
                    } else if (std::find(availableTiles.begin(), availableTiles.end(), tile) != availableTiles.end()) {
                        std::cout << "(" << tile->getTypeChar() << ", A) ";
                    } else {
                        std::cout << "(" << tile->getTypeChar() << ", .) ";
                    }
                }
                std::cout << std::endl;
            }

            std::cout << "Enter a command: ";
            std::cin >> command;

            switch (command) {
                case 'w':
                    movementHandler.moveUnit(unit, gameStateManager.getMap().at(unit->getTile()->getId() - gameStateManager.getMapSize().first));
                    break;
                case 'a':
                    movementHandler.moveUnit(unit, gameStateManager.getMap().at(unit->getTile()->getId() - 1));
                    break;
                case 's':
                    movementHandler.moveUnit(unit, gameStateManager.getMap().at(unit->getTile()->getId() + gameStateManager.getMapSize().first));
                    break;
                case 'd':
                    movementHandler.moveUnit(unit, gameStateManager.getMap().at(unit->getTile()->getId() + 1));
                    break;
                case 'q':
                    break;
                default:
                    std::cout << "Invalid command" << std::endl;
                    break;
            }
        }

        return std::make_pair(0, 0);
}