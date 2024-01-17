#include "Tile.hpp"

Tile::Tile(const int& id, const std::vector<Tile>& neighbors) : id_(id), neighbors_(neighbors) { 
    TileType majorityType = getNeighborMajorityType();
    std::map<TileType, double> typeOdds = {
        {TileType::GRASS, 35},
        {TileType::FOREST, 20},
        {TileType::WATER, 20},
        {TileType::MOUNTAIN, 5},
    };
    typeOdds[majorityType] += 10;

    type_ = chooseAlternative<TileType>(typeOdds);
}

Tile::~Tile() { }

void Tile::setNeighbors(const std::vector<Tile>& neighbors) {
    neighbors_ = neighbors;
}

std::vector<Tile> Tile::getNeighbours() {
    return neighbors_;
}

TileType Tile::getNeighborMajorityType() {
    std::map<TileType, int> typeCount;

    for (auto neighbor : neighbors_) {
        typeCount[neighbor.getType()]++;
    }

    TileType majorityType = TileType::MOUNTAIN;
    int maxCount = 0;

    for (const auto& pair : typeCount) {
        if (pair.second > maxCount) {
            majorityType = pair.first;
            maxCount = pair.second;
        }
    }

    return majorityType;
}

TileType Tile::getType() {
    return type_;
}

char Tile::getTypeChar() {
    switch (type_) {
        case TileType::GRASS:
            return 'G';
        case TileType::FOREST:
            return 'F';
        case TileType::WATER:
            return 'W';
        case TileType::MOUNTAIN:
            return 'M';
        default:
            return ' ';
    }
}
