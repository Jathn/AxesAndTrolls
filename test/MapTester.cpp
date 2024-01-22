#include "MapTester.hpp"
#include <iostream>
#include <algorithm>

MapTester::MapTester() : Tester() { }

std::pair<int, int> MapTester::runTest() {

    std::vector<Tile> map;
    int width = 5;
    int height = 3;

    std::cout << "## Map generation test ##" << std::endl;
    std::cout << "Enter width: " << std::endl;
    std::cin >> width;
    std::cout << "Enter height: " << std::endl;
    std::cin >> height;
    std::pair<int, int> map_size = std::make_pair(width, height);
    game_state_manager_ = GameStateManager(map_size);

    bool isNeighbor = false; // Initialize isNeighbor to false
    for (auto tile : game_state_manager_.getMap()) {
        /* For each tile: find their neighbors */
        std::cout << "[" << tile.getTypeChar() << "]";
        if (tile.getId() % width == width - 1) {
            std::cout << std::endl;
        }

    }

    for (auto neighbor : game_state_manager_.getMap().at(width + 4).getNeighbors()) {
        /* For each neighbor: find their neighbors */
        const std::vector<std::shared_ptr<Tile>>& list_of_neighbors = neighbor->getNeighbors();

        /* Search the tile at index width + 4 */
        std::find_if(list_of_neighbors.begin(), list_of_neighbors.end(), [&width, &isNeighbor](const std::shared_ptr<Tile>& tile) {
            if (tile->getId() == width + 4) {
                isNeighbor = true;
            }
            return isNeighbor;
        });

    }

    /* Checking if the map is generated correctly */
    if (isNeighbor) {
        addCompleted("Map generation");
    } else {
        addUnsuccessful("Map generation");
    }
    return test_results_;
}