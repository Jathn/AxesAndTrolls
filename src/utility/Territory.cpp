#include "Territory.hpp"

Territory::Territory() { tiles_ = std::vector<std::weak_ptr<Tile>>(); }

const std::vector<std::shared_ptr<Tile>> Territory::getTiles() const {
    std::vector<std::shared_ptr<Tile>> tiles;
    for (auto tile : tiles_) {
        tiles.push_back(tile.lock());
    }
    return tiles;
}

const std::vector<std::weak_ptr<Building>> Territory::getBuildings() const {
    std::vector<std::weak_ptr<Building>> buildings;
    for (auto tile : tiles_) {
        std::shared_ptr<Tile> t = tile.lock();
        if (t != nullptr) {
            std::shared_ptr<Building> building = t->getBuilding();
            if (building != nullptr) {
                buildings.push_back(building);
            }
        }
    }

    return buildings;
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
