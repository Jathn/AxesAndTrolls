#include "Tile.hpp"

Tile::Tile(const int& id, const std::vector<std::shared_ptr<Tile>>& neighbors) : id_(id) {
    for (auto neighbor : neighbors) {
        std::weak_ptr<Tile> neighbor_weak = neighbor;
        neighbors_.push_back(neighbor_weak);
    } 
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

void Tile::setNeighbors(const std::vector<std::weak_ptr<Tile>>& neighbors) {
    neighbors_ = neighbors;
}

void Tile::addNeighbor(const std::shared_ptr<Tile>& neighbor) {
    std::weak_ptr<Tile> weak_ptr = neighbor;
    neighbors_.push_back(weak_ptr);
}

std::vector<std::weak_ptr<Tile>> Tile::getNeighbors() {
    return neighbors_;
}

TileType Tile::getNeighborMajorityType() {
    std::map<TileType, int> typeCount;

    for (auto neighbor : neighbors_) {
        try {
            neighbor.lock()->getType();
        } catch (const std::bad_weak_ptr& e) {
            std::cout << "Bad weak pointer: " << e.what() << std::endl;
            continue;
        }
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

const int& Tile::getId() const {
    return id_;
}
