#include "TurnTester.hpp"

TurnTester::TurnTester() : Tester() {}

std::pair<int, int> TurnTester::runTest() {
    std::pair<int, int> map_size = std::make_pair(5, 5);
    GameStateManager game_state_manager = GameStateManager(map_size);

    std::shared_ptr<Player> player = std::make_shared<Player>();
    player->addResource(ResourceType::GOLD, 30);
    player->buyBuilding(BuildingType::CITY);
    std::cout << "Map for this game: " << std::endl;
    printMap(map_size, game_state_manager);
    std::cout << ".\n.\n.\n";
    std::cout << "Initial city placement" << std::endl;
    printMap(map_size, game_state_manager);
    std::cout << "Choose a tile for placement with coordinates (x, y)" << std::endl;
    int x;
    int y;
    int id;
    std::cout << "x:" << std::endl;
    std::cin >> x;
    std::cout << "y:" << std::endl;
    std::cin >> y;
    id = y*map_size.first + x;
    game_state_manager.getMap()[id]->setBuilding(player->getUnplacedBuildings()[0]);
    printMap(map_size, game_state_manager);

    return test_results_;
}

void TurnTester::printMap(std::pair<int, int> ms, GameStateManager gsm) {
    for (int i = 0; i < ms.second; i++) {
        for (int j = 0; j < ms.first; j++) {
            auto tile = gsm.getMap().at(i * ms.first + j);
            auto units = tile->getUnits();
            auto building = tile->getBuilding();
            std::cout << "(" << tile->getTypeChar();
            std::cout << ",";
            if (building != nullptr) {
                std::cout << building->getTypeChar();
            } else {
                std::cout << ".";
            }
            std::cout << ",{";
            for (auto unit : units) {
                std::cout << unit.lock()->getTypeChar();
            }
            std::cout << "}";
            std::cout << ")  ";
        }

        for (int i = 0; i < 2; i++) {
            std::cout << std::endl;
        }
    }  
}