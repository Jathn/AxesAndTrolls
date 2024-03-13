#include "Territory.hpp"

Territory::Territory() { }

const std::vector<std::shared_ptr<Tile>> Territory::getTiles() const {
    std::vector<std::shared_ptr<Tile>> tiles;
    for (auto tile : tiles_) {
        tiles.push_back(tile.lock());
    }
    return tiles;
}

void Territory::addTile(const std::shared_ptr<Tile>& tile) {
    tiles_.push_back(tile);
}

void Territory::removeTile(const std::shared_ptr<Tile>& tile) {
    tiles_.erase(std::remove_if(tiles_.begin(), tiles_.end(), 
        [&tile](const std::weak_ptr<Tile>& t) {
            return t.lock() == tile;
        }), tiles_.end());
}
