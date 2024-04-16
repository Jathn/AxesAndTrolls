#include "Player.hpp"

Player::Player() {
    territory_ = std::make_shared<Territory>();
    movement_handler_ = MovementHandler(territory_);
    resources_[ResourceType::GOLD] = 0;
    resources_[ResourceType::WOOD] = 0;
    resources_[ResourceType::FOOD] = 0;
}

const std::vector<std::shared_ptr<Tile>> Player::getTiles() const {
    return territory_->getTiles();
}

std::vector<std::shared_ptr<Unit>> Player::getUnits() const {
    return movement_handler_.getUnits();
}

std::vector<std::shared_ptr<Building>> Player::getBuildings() const {
    std::vector<std::shared_ptr<Building>> buildings;
    for (auto tile : getTiles()) {
        std::shared_ptr<Building> building = tile->getBuilding();
        if (building != nullptr) {
            buildings.push_back(building);
        }
    }

    return buildings;
}

std::vector<std::shared_ptr<Building>> Player::getUnplacedBuildings() const {
    return unplaced_buildings_;
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
    territory_->getTiles();

    /* Check whether the tile is own tile */
    if (std::find(territory_->getTiles().begin(), territory_->getTiles().end(), tile) == territory_->getTiles().end()) {
        /* Tile is not owned by player */
        throw InvalidPlacementException();
    }

    /* Check that there is city on this tile */
    if (tile->getBuilding() == nullptr || tile->getBuilding()->getType() != BuildingType::CITY) {
        /* Tile does not have city */
        throw InvalidPlacementException();
    }

    tile->addUnit(unit);
    unit->setTile(tile);
}

/* Checks only gold cost */
void Player::buyBuilding(const BuildingType& type) {
    std::shared_ptr<Building> building = std::make_shared<Building>(type);

    if (resources_[ResourceType::GOLD] < building->getCost()) {
        /* Not enough resources to buy building */
        throw NotEnoughResourcesException();
    }

    removeResource(ResourceType::GOLD, building->getCost());
    unplaced_buildings_.push_back(building);
    resource_generation_[building->getIncome().first] += building->getIncome().second;
}

void Player::placeBuilding(const std::shared_ptr<Building>& building, const std::shared_ptr<Tile>& tile) {
    territory_->getTiles();

    /* Check whether the tile is own tile */
    if (std::find(territory_->getTiles().begin(), territory_->getTiles().end(), tile) == territory_->getTiles().end()) {
        /* Tile is not owned by player */
        throw InvalidPlacementException();
    }

    /* Check that the building can be placed on this tile */
    if (!building->isSuitablePlacement(tile->getType())) {
        /* Building cannot be placed on this tile */
        throw InvalidPlacementException();
    }

    /* Check that the tile is empty */
    if (tile->getBuilding() != nullptr) {
        /* Tile already has a building */
        throw InvalidPlacementException();
    }
    
    for (auto it = unplaced_buildings_.begin(); it != unplaced_buildings_.end(); it++) {
        if (*it == building) {
            unplaced_buildings_.erase(it);
            break;
        }
    }
    tile->setBuilding(building);
    building->setTile(tile);
}

void Player::addResource(ResourceType resource, int amount) {
    resources_[resource] += amount;
}

void Player::removeResource(ResourceType resource, int amount) {
    resources_[resource] -= amount;
}
