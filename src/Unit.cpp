#include "Unit.hpp"

Unit::Unit(const int& hit_level, const int& cost, const int& movement, const std::string& benefits) : hit_level_(hit_level), cost_(cost), benefits_(benefits), movement_(movement) {}

Unit::~Unit() {}

// Say hello to the getters and setter, they are our friends. (Maybe not the setters, they are a bit too friendly.)
int Unit::getHitLevel() const {
    return hit_level_;
}

int Unit::getCost() const {
    return cost_;
}

bool Unit::hasCombinedUnit() const {
    return !combined_unit_.expired();
}

std::string Unit::getBenefits() const {
    return benefits_;
}

int Unit::getMovement() const {
    return movement_;
}

int Unit::getMovementLeft() const {
    return movement_left_;
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

bool Unit::isReachableTile(const std::shared_ptr<Tile>& tile) {
    std::pair<int, std::vector<int>> distance = calculateDistanceGBFS(tile_.lock(), tile);

    return distance.first <= movement_left_;
}

bool Unit::isLeavableTile(const std::shared_ptr<Tile>& tile) {
    return getOwner() == tile->getOwner().lock();
}

/*

TODO:

Implement a checkLegalMove function

A tile is not always reachable or possible to pass through, e.g. if it is occupied 
by another unit or if it is not within 
the movement range of the unit. The function 
checkLegalMove should take a shared pointer to 
a tile as input and return a boolean indicating 
whether the move is legal or not. 

This function can then be passed as a parameter
to the calculateDistanceGBFS function in the
Movement file. (It also requires update.)

*/

/*

TODO:

Now that checkLegalMove is implemented,
implement the move function & a function that
returns all legal moves.

*/
