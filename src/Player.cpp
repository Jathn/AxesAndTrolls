#include "Player.hpp"

Player::Player() {
    territory_ = std::make_shared<Territory>();
    movement_handler_ = MovementHandler(territory_.lock());
}

const std::vector<std::shared_ptr<Tile>> Player::getTiles() const {
    return territory_.lock()->getTiles();
}

std::vector<std::shared_ptr<Unit>> Player::getUnits() const {
    return movement_handler_.getUnits();
}