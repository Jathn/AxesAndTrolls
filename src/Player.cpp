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

void Player::buyUnit(const UnitType& type) {
    std::shared_ptr<Unit> unit = std::make_shared<Unit>(type);

    std::pair<int, int> cost = unit->getCost();
    if (resources_[ResourceType::FOOD] < cost.first || resources_[ResourceType::WOOD] < cost.second) {
        /* Not enough resources to buy unit */
        throw NotEnoughResourcesException();
    }

    removeResource(ResourceType::FOOD, cost.first);
    removeResource(ResourceType::WOOD, cost.second);

    movement_handler_.addUnit(unit);
}

void Player::placeUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile) {
    tile->addUnit(unit);
    unit->setTile(tile);
}

void Player::addResource(ResourceType resource, int amount) {
    resources_[resource] += amount;
}

void Player::removeResource(ResourceType resource, int amount) {
    resources_[resource] -= amount;
}
