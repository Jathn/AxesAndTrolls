#include "MapTester.hpp"
#include <iostream>
#include <algorithm>

MapTester::MapTester() : Tester() { }

std::pair<int, int> MapTester::runTest() {

    int width = 4;
    int height = 3;

    std::cout << "## Map GENERATION TEST ##" << std::endl;
    std::cout << "Enter width: " << std::endl;
    std::cin >> width;
    std::cout << "Enter height: " << std::endl;
    std::cin >> height;
    if (width < 4) {
        width = 4;
    }
    if (height < 3) {
        height = 3;
    }
    std::pair<int, int> map_size = std::make_pair(width, height);
    game_state_manager_ = GameStateManager(map_size);
    game_state_manager_.setCurrentTile(5);
    bool isNeighbor = false; // Initialize isNeighbor to false
    for (auto tile : game_state_manager_.getMap()) {
        /* For each tile: find their neighbors */
        if (tile->getId() == game_state_manager_.getCurrentTile()->getId()) {
            std::cout << "[>" << tile->getTypeChar() << "<]";
        } else {
            std::cout << "[" << tile->getTypeChar() << "]";
        }
        if (tile->getId() % width == width - 1) {
            std::cout << std::endl;
        }

    }

    /* Checking whether tiles are in the right place */
    if (width + 4 < width * height) {
            /* If the tile is not at the bottom of the map */    
            auto list_of_neighbors = game_state_manager_.getMap().at(width + 4)->getNeighbors();

            isNeighbor = std::any_of(list_of_neighbors.begin(), list_of_neighbors.end(),
                                    [&width](const std::weak_ptr<Tile>& tile) {
                                        return tile.lock()->getId() == 4;
                                    });
    }

    /* Checking if the map is generated correctly */
    if (isNeighbor) {
        addSuccessful("Map generation");
    } else {
        addUnsuccessful("Map generation");
    }

    /* Checking coordinates of width + 4 tile */
    if (game_state_manager_.getMap().at(width + 4)->getX() == 4 && game_state_manager_.getMap().at(width + 4)->getY() == 1) {
        addSuccessful("Tile coordinates");
    } else {
        addUnsuccessful("Tile coordinates");
    }

    /* Checking distance calculating algorithm */
    std::cout << "### Movement test ###" << std::endl;
    std::cout << "Calculating distance between tiles" << std::endl;
    std::vector<std::shared_ptr<Tile>> map = game_state_manager_.getMap();
    std::pair<int, std::vector<int>> path = calculateDistanceGBFS(map[width * height - 3], map[0]);
    std::cout << "Distance: " << path.first << std::endl;
    std::cout << "Path: " << std::endl;
    int box_space = 0;
    for (auto tile : map) {
        switch (tile->getId()) {
            case 0:
                box_space = 4;
                break;
            case 10:
                box_space = 3;
                break;
            case 100:
                box_space = 2;
                break;
            default:
                break;
        }
        
        if (std::find(path.second.begin(), path.second.end(), tile->getId()) != path.second.end()) {
            std::cout << "[> " << tile->getId() << " <]";
        } else {
            std::cout << "[";
            for (int i = 0; i < box_space; i++) {
                std::cout << " ";
            }
            std::cout << tile->getId() << "]";
        }
        
        if (tile->getId() % width == width - 1) {
            std::cout << std::endl;
        }
    }

    if (path.second.back() != 0) {
        addUnsuccessful("Distance calculation");
    } else {
        addSuccessful("Distance calculation");
    }

    return test_results_;
}