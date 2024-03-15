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

const int Player::getResource(ResourceType resource) const {
    return resources_.at(resource);
}

const int Player::getResourceGeneration(ResourceType resource) const {
    return resource_generation_.at(resource);
}

void Player::buyUnit(std::shared_ptr<Unit> unit) {
    std::pair<int, int> cost = unit->getCost();
    if (resources_[ResourceType::FOOD] < cost.first || resources_[ResourceType::WOOD] < cost.second) {
        /* Not enough resources to buy unit */
        throw NotEnoughResourcesException();
    }

    resources_[ResourceType::FOOD] -= cost.first;
    resources_[ResourceType::WOOD] -= cost.second;
    movement_handler_.addUnit(unit);
}