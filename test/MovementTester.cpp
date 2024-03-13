#include "MovementTester.hpp"

MovementTester::MovementTester() : Tester() { }


std::pair<int, int> MovementTester::runTest() {

    std::cout << "### Movement test ###" << std::endl;

    std::pair<int, int> map_size = std::make_pair(10, 10);
    game_state_manager_ = GameStateManager(map_size);
    std::shared_ptr<Territory> territory = std::make_shared<Territory>();
    MovementHandler movementHandler(territory);
    int current_id = 0;

    std::cout << "Creating a unit..." << std::endl;
    std::shared_ptr<Unit> unit = std::make_shared<Unit>(current_id, UnitType::DRAGON);

    if (unit->getType() == UnitType::DRAGON) {
        addSuccessful("Unit creation");
    } else {
        addUnsuccessful("Unit creation");
    }

    std::cout << "Setting the unit's tile..." << std::endl;

    unit->setTile(game_state_manager_.getMap().at(0));

    if (unit->getTile() == game_state_manager_.getMap().at(0)) {
        addSuccessful("Unit tile setting");
    } else {
        addUnsuccessful("Unit tile setting");
    }

    std::cout << "Adding the unit to the movement handler..." << std::endl;
    movementHandler.addUnit(unit);

    
    if (movementHandler.getUnits().size() == 1) {
        addSuccessful("Unit addition to MovementHandler");
    } else {
        addUnsuccessful("Unit addition to MovementHandler");
    }

    std::cout << "Removing unit from movement handler..." << std::endl;

    movementHandler.removeUnit(unit);

    if (movementHandler.getUnits().empty()) {
        addSuccessful("Unit removal from MovementHandler");
    } else {
        addUnsuccessful("Unit removal from MovementHandler");
    }

    movementHandler.addUnit(unit);

    std::cout << "Getting available tiles for the unit..." << std::endl;

    std::vector<std::shared_ptr<Tile>> availableTiles = movementHandler.getAvailableTiles(unit);

    std::cout << "Printing the map with unit marked U, available tiles marked A and others marked .\n";

    for (int i = 0; i < map_size.first; i++) {
        for (int j = 0; j < map_size.second; j++) {
            auto tile = game_state_manager_.getMap().at(i * map_size.second + j);
            if (tile == unit->getTile()) {
                std::cout << "U ";
            } else if (std::find(availableTiles.begin(), availableTiles.end(), tile) != availableTiles.end()) {
                std::cout << "A ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }

    std::cout << "Moving the unit to tile with id 12" << std::endl;

    std::shared_ptr<Tile> tile = game_state_manager_.getMap().at(12);
    movementHandler.moveUnit(unit, tile);

    availableTiles = movementHandler.getAvailableTiles(unit);
    
    for (int i = 0; i < map_size.first; i++) {
        for (int j = 0; j < map_size.second; j++) {
            auto tile = game_state_manager_.getMap().at(i * map_size.second + j);
            if (tile == unit->getTile()) {
                std::cout << "U ";
            } else if (std::find(availableTiles.begin(), availableTiles.end(), tile) != availableTiles.end()) {
                std::cout << "A ";
            } else {
                std::cout << ". ";
            }
        }
        std::cout << "\n";
    }

    if (unit->getTile() == tile) {
        addSuccessful("Unit movement");
    } else {
        addUnsuccessful("Unit movement");
    }

    return test_results_;
}