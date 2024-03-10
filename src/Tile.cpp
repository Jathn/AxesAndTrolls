#include "Tile.hpp"

Tile::Tile(const int& id, const int& x, const int& y, const std::vector<std::shared_ptr<Tile>>& neighbors, bool random, TileType type) : id_(id), x_(x), y_(y), type_(type) {
    for (auto neighbor : neighbors) {
        std::weak_ptr<Tile> neighbor_weak = neighbor;
        neighbors_.push_back(neighbor_weak);
    } 
    if (random) {
        randomizeType();
    }
}

Tile::~Tile() { }

std::vector<std::weak_ptr<Tile>> Tile::getNeighbors() {
    return neighbors_;
}

std::shared_ptr<Tile> Tile::getNeighbor(int id) {
    for (auto neighbor : neighbors_) {
        std::shared_ptr<Tile> lockedNeighbor = neighbor.lock();
        if (lockedNeighbor != nullptr && lockedNeighbor->getId() == id) {
            return lockedNeighbor;
        }
    }
    return nullptr;
}

TileType Tile::getNeighborMajorityType() {
    std::map<TileType, int> typeCount;

    typeCount[TileType::GRASS] = 0;
    typeCount[TileType::FOREST] = 0;
    typeCount[TileType::WATER] = 0;
    typeCount[TileType::MOUNTAIN] = 0;

    for (auto neighbor : neighbors_) {
        std::shared_ptr<Tile> lockedNeighbor = neighbor.lock();
        if (lockedNeighbor != nullptr) {
            TileType neighborType = lockedNeighbor->getType();
            typeCount[neighborType] = typeCount[neighborType] + 1;
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

const int& Tile::getX() const {
    return x_;
}

const int& Tile::getY() const {
    return y_;
}

const std::vector<std::weak_ptr<Unit>>& Tile::getUnits() const {
    return units_;
}

const std::weak_ptr<Player>& Tile::getOwner() const {
    return owner_;
}

void Tile::setOwner(const std::shared_ptr<Player>& owner) {
    owner_ = owner;
}

void Tile::setNeighbors(const std::vector<std::weak_ptr<Tile>>& neighbors) {
    neighbors_ = neighbors;
}

void Tile::addNeighbor(const std::shared_ptr<Tile>& neighbor) {
    std::weak_ptr<Tile> weak_ptr = neighbor;
    neighbors_.push_back(weak_ptr);
}

void Tile::addUnit(const std::shared_ptr<Unit>& unit) {
    std::weak_ptr<Unit> weak_ptr = unit;
    units_.push_back(weak_ptr);
}

void Tile::removeUnit(const std::shared_ptr<Unit>& unit) {
    std::remove_if(units_.begin(), units_.end(), [unit](std::weak_ptr<Unit> weak_unit) {
        return weak_unit.lock() == unit;
    });
}


bool Tile::isFull() {
    return units_.size() > 4;
}

bool Tile::isHomogenous() {
    return true;
}

// Private methods
void Tile::randomizeType() {
    TileType majorityType = getNeighborMajorityType();
        std::map<TileType, double> typeOdds = {
            {TileType::GRASS, 25},
            {TileType::FOREST, 15},
            {TileType::WATER, 20},
            {TileType::MOUNTAIN, 5},
        };
    typeOdds[majorityType] += 35;
    type_ = chooseAlternative<TileType>(typeOdds);
}