#include "Player.hpp"

void Player::addTile(const Tile& tile) {
    tiles_.push_back(std::make_shared<Tile>(tile));
}

void Player::removeTile(const int& id) {
    tiles_.erase(std::remove_if(tiles_.begin(), tiles_.end(), [&id](const std::shared_ptr<Tile>& tile) {
        return tile->getId() == id;
    }), tiles_.end());
}

std::vector<std::shared_ptr<Tile>> Player::getTiles() const {
    return tiles_;
}
