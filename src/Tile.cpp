#include "Tile.hpp"

Tile::Tile(const int& id, const TileType& type) : id_(id), type_(type) { }

Tile::~Tile() { }

void Tile::setNeighbors(std::vector<Tile> neighbors) {
    neighbors_ = neighbors;
}

TileType Tile::getType() {
    return type_;
}

TileType Tile::getNeighborMajorityType() {
    std::map<TileType, int> typeCount;

    for (auto neighbor : neighbors_) {
        typeCount[neighbor.getType()]++;
    }

    TileType majorityType;
    int maxCount = 0;

    for (const auto& pair : typeCount) {
        if (pair.second > maxCount) {
            majorityType = pair.first;
            maxCount = pair.second;
        }
    }

    return majorityType;
}
