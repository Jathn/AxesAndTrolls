#include "GameStateManager.hpp"

GameStateManager::GameStateManager(const std::pair<int, int>& map_size) : map_size_(map_size) {
    generateMap();
}

GameStateManager::~GameStateManager() {

}

void GameStateManager::generateMap() {
    std::vector<std::shared_ptr<Tile>> tiles;
    int width = map_size_.first;
    int height = map_size_.second;

    /* Generate a vector of Tile objects */
    for (int i = 0; i < width * height; i++) {
        std::vector<std::shared_ptr<Tile>> neighbors;
        if (i % width != 0) {
            neighbors.push_back(tiles[i - 1]);
        }
        if (i >= width) {
            neighbors.push_back(tiles[i - width]);
        }
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(i, neighbors);

        tiles.push_back(tile);
    }

    /* Add the remaining neighbors */
    for (int i = 0; i < width * height; i++) {
        if (i % width != width - 1) {
            tiles[i]->addNeighbor(tiles[i + 1]);
        }
        if (i < width * (height - 1)) {
            tiles[i]->addNeighbor(tiles[i + width]);
        }
    }

    /* Assign the tile vector to map */
    map_ = tiles;
}

std::vector<std::shared_ptr<Tile>> GameStateManager::getMap() {
    return map_;
}

void GameStateManager::setCurrentTile(const int& id) {
    std::shared_ptr<Tile> newCurrentTile = map_.at(id);
    current_tile_ = newCurrentTile;
}

std::shared_ptr<Tile> GameStateManager::getCurrentTile() {
    return current_tile_;
}
