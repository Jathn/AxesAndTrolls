#include "GameStateManager.hpp"

GameStateManager::GameStateManager(const std::pair<int, int>& map_size, const int& num_players) : map_size_(map_size) {
    generateMap();
    if (num_players > 4) throw std::invalid_argument("Too many players");
    createPlayers(num_players);
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
        std::shared_ptr<Tile> tile = std::make_shared<Tile>(i, i%width, i/width, neighbors);

        if (i > 0) {
            tiles[i - 1]->addNeighbor(tile);
        }
        if (i >= width) {
            tiles[i - width]->addNeighbor(tile);
        }

        tiles.push_back(tile);
    }


    /* Assign the tile vector to map */
    map_ = tiles;
}

std::vector<sf::Color> player_colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow};
void GameStateManager::createPlayers(const int& num_players) {
    for (int i = 0; i < num_players; i++) {
        std::shared_ptr<Player> player = std::make_shared<Player>(player_colors[i]);
        players_.push_back(player);
    }
}

std::vector<std::shared_ptr<Tile>> GameStateManager::getMap() {
    return map_;
}

std::pair<int, int> GameStateManager::getMapSize() {
    return map_size_;
}

std::vector<std::shared_ptr<Player>> GameStateManager::getPlayers() {
    return players_;
}

void GameStateManager::setCurrentTile(const int& id) {
    std::shared_ptr<Tile> newCurrentTile = map_[id];
    current_tile_ = newCurrentTile;
}

std::shared_ptr<Tile> GameStateManager::getCurrentTile() {
    return current_tile_;
}
