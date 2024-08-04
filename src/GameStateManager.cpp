#include "GameStateManager.hpp"

GameStateManager::GameStateManager(std::pair<int, int> map_size, int num_players) : map_size_(map_size) {
    generateMap();
    current_player_ = 0;
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
    if (num_players > 4) throw std::invalid_argument("Too many players");
    for (int i = 0; i < num_players; i++) {
        std::shared_ptr<Player> player = std::make_shared<Player>(player_colors[i]);
        player->setPlayerNr(i + 1);
        players_.push_back(player);
    }
}

void GameStateManager::nextPlayer() {
    current_player_ = (current_player_ + 1) % players_.size();
}

const std::vector<std::shared_ptr<Tile>>& GameStateManager::getMap() {
    return map_;
}

std::pair<int, int> GameStateManager::getMapSize() {
    return map_size_;
}

const std::vector<std::shared_ptr<Player>>& GameStateManager::getPlayers() {
    return players_;
}

const std::shared_ptr<Player> GameStateManager::getCurrentPlayer() {
    return players_[current_player_];
}

const int& GameStateManager::getRoundNr() {
    return round_nr_;
}

void GameStateManager::setCurrentTile(const int& id) {

    /* Remove previous tile "current" status */
    if (current_tile_ != nullptr) {
        current_tile_->toggleCurrent();
    }
    std::shared_ptr<Tile> newCurrentTile = map_[id];
    current_tile_ = newCurrentTile;

    /* Update tile "current" status to true */
    current_tile_->toggleCurrent();
}

std::shared_ptr<Tile> GameStateManager::getCurrentTile() {
    return current_tile_;
}

std::vector<std::shared_ptr<Tile>> GameStateManager::getContestedTiles() {
    std::vector<std::shared_ptr<Tile>> contested_tiles;
    for (auto tile : map_) {
        if (isTileContested(tile)) {
            std::cout << "Tile " << tile->getId() << " is contested" << std::endl;
            contested_tiles.push_back(tile);
        }
    }

    return contested_tiles;
}

void GameStateManager::setCurrentPlayer(const std::shared_ptr<Player>& player) {
    for (int i = 0; i < players_.size(); i++) {
        if (players_[i] == player) {
            current_player_ = i;
            return;
        }
    }
}

void GameStateManager::setPlayers(const std::vector<std::shared_ptr<Player>>& players) {
    players_ = players;
}

bool GameStateManager::isTileContested(const std::shared_ptr<Tile>& tile) const { 
    const std::vector<std::weak_ptr<Unit>> units = tile->getUnits();

    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::string> player_names;

    for (auto unit : units) {
        if (unit.expired()) continue;
        
        std::string name = "null";
        std::shared_ptr<Player> player = unit.lock()->getOwner();
        if (player == nullptr) {
            continue;
        } else {
            name = player->getName();
        }
        
        if (std::find(player_names.begin(), player_names.end(), name) == player_names.end()) {
            players.push_back(player);
        }
    }

    return players.size() > 1;
}