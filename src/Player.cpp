#include "Player.hpp"

void Player::addTile(const std::shared_ptr<Tile>& tile) {
    std::weak_ptr<Tile> tile_ptr = tile;
    tiles_.push_back(tile_ptr);
}

void Player::removeTile(const int& id) {
    tiles_.erase(std::remove_if(tiles_.begin(), tiles_.end(), 
                                [&id](const std::weak_ptr<Tile>& tile) {
                                    return tile.lock()->getId() == id;
                                }), tiles_.end());
}

const std::vector<std::shared_ptr<Tile>> Player::getTiles() const {
    std::vector<std::shared_ptr<Tile>> shared_tiles;
    for (const auto& weak_tile : tiles_) {
        if (auto shared_tile = weak_tile.lock()) {
            shared_tiles.push_back(shared_tile);
        }
    }
    return shared_tiles;
}
