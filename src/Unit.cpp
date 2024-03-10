#include "Unit.hpp"

Unit::Unit(const int& hit_level, const int& cost, const int& movement, const std::string& benefits, const int& id) : hit_level_(hit_level), cost_(cost), benefits_(benefits), movement_(movement), id_(id) {}

Unit::~Unit() {}

// Say hello to the getters and setter, they are our friends. (Maybe not the setters, they are a bit too friendly.)
const int& Unit::getHitLevel() const {
    return hit_level_;
}

const int& Unit::getCost() const {
    return cost_;
}

const int& Unit::getMovement() const {
    return movement_;
}

const int& Unit::getMovementLeft() const {
    return movement_left_;
}

const int& Unit::getId() const {
    return id_;
}

bool Unit::hasCombinedUnit() const {
    return !combined_unit_.expired();
}

std::string Unit::getBenefits() const {
    return benefits_;
}

std::shared_ptr<Player> Unit::getOwner() const {
    return owner_.lock();
}

std::shared_ptr<Tile> Unit::getTile() const {
    return tile_.lock();
}

void Unit::setCost(int cost) {
    cost_ = cost;
}

void Unit::setCombinedUnit(const std::shared_ptr<Unit>& combined_unit) {
    combined_unit_ = combined_unit;
}

void Unit::setBenefits(const std::string& benefits) {
    benefits_ = benefits;
}

void Unit::setMovementLeft(int movement_left) {
    movement_left_ = movement_left;
}

void Unit::setOwner(const std::shared_ptr<Player>& owner) {
    owner_ = owner;
}

void Unit::setTile(const std::shared_ptr<Tile>& tile) {
    tile_ = tile;
}

bool Unit::isLeavableTile(const std::shared_ptr<Tile>& tile) {
    if (tile->getUnits().size() == 0) {
        return true;
    }

    bool own_units_only = true;
    for (auto unit : tile->getUnits()) {
        if (unit.lock()->getOwner() != owner_.lock()) {
            own_units_only = false;
            break;
        }
    }

    return own_units_only;
}

bool Unit::isReachableTile(const std::shared_ptr<Tile>& tile) {
    std::pair<int, std::vector<int>> distance = calculateDistanceGBFS(tile_.lock(), tile);

    std::vector<std::shared_ptr<Tile>> route;

    for (auto it = distance.second.begin(); it != distance.second.end(); it++) {
        route.push_back(tile_.lock()->getNeighbor(*it));
    }

    bool all_are_leavable = true;
    for (auto it = route.begin(); it != route.end(); it++) {
        if (!isLeavableTile(*it)) {
            all_are_leavable = false;
            break;
        }
    }

    return (distance.first <= movement_left_) && all_are_leavable;
}
