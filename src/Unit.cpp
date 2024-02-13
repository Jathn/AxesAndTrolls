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

void Unit::setTile(const std::shared_ptr<Tile>& tile) {
    tile_ = tile;
}

std::pair<bool, int> Unit::rollToHit() const {

    /* Distribution for dice roll */
    std::map<int, double> alternatives;
    for (int i = 1; i <= 6; i++) {
        alternatives[i] = 1.0 / 6.0;
    }

    /* Outcome of dice roll */
    int fall_out = chooseAlternative<int>(alternatives);

    /* If the outcome is less than or equal to the hit level, the unit hits. First: boolean, Second: rolled number */
    return std::make_pair(fall_out <= hit_level_, fall_out);

}
