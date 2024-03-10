#include "Unit.hpp"

std::map<UnitType, std::vector<int>> unitTypeMap = {
    /* Format: 
        {UnitType, {hit_level, cost_food, cost_wood, movement}}
    */
    {UnitType::SURFACE_WARSHIP, {4, 0, 10, 2}},
    {UnitType::SEA_TRANSPORT, {0, 0, 5, 2}},
    {UnitType::INFANTRY, {1, 3, 0, 1}},
    {UnitType::ARTILLERY, {2, 2, 3, 1}},
    {UnitType::RIDER, {2, 3, 3, 2}},
    {UnitType::DRAGON, {4, 8, 4, 2}}
};

Unit::Unit(const int& id, UnitType type) 
: id_(id), type_(type) {
    hit_level_ = unitTypeMap[type][0];
    cost_ = std::make_pair(unitTypeMap[type][1], unitTypeMap[type][2]);
    movement_ = unitTypeMap[type][3];
    movement_left_ = movement_;
}

Unit::~Unit() {}

// Say hello to the getters and setter, they are our friends. (Maybe not the setters, they are a bit too friendly.)
const int& Unit::getHitLevel() const {
    return hit_level_;
}

const std::pair<int, int>& Unit::getCost() const {
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

std::shared_ptr<Player> Unit::getOwner() const {
    return owner_.lock();
}

std::shared_ptr<Tile> Unit::getTile() const {
    return tile_.lock();
}

void Unit::setCost(std::pair<int, int> cost) {
    cost_ = cost;
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
