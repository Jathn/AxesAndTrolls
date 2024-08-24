#include "Player.hpp"

Player::Player(const sf::Color& color, const std::string& name) {
    name_ = name;
    territory_ = std::make_shared<Territory>();
    movement_handler_ = std::make_shared<MovementHandler>(territory_);
    color_ = color;
    resources_[ResourceType::GOLD] = 0;
    resources_[ResourceType::WOOD] = 0;
    resources_[ResourceType::FOOD] = 0;
}

const int& Player::getPlayerNr() const {
    return player_nr_;
}

const std::string& Player::getName() const {
    return name_;
}

const sf::Color& Player::getColor() const {
    return color_;
}

const std::shared_ptr<Territory>& Player::getTerritory() const {
    return territory_;
}

const std::shared_ptr<MovementHandler>& Player::getMovementHandler() const {
    return movement_handler_;
}

const std::vector<std::shared_ptr<Tile>> Player::getTiles() const {
    return territory_->getTiles();
}

std::vector<std::shared_ptr<Unit>> Player::getUnits() const {
    return movement_handler_->getUnits();
}

std::vector<std::shared_ptr<Unit>> Player::getUnplacedUnits() const {
    return movement_handler_->getUnplacedUnits();
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

void Player::setPlayerNr(int player_nr) {
    player_nr_ = player_nr;
}

void Player::setName(const std::string& name) {
    name_ = name;
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

    unit->setOwner(getThisPlayer());

    movement_handler_->addUnit(unit);
}

void Player::sellUnit(const std::shared_ptr<Unit>& unit) {
    movement_handler_->removeUnit(unit);
    addResource(ResourceType::FOOD, unit->getCost().first);
    addResource(ResourceType::WOOD, unit->getCost().second);
}

void Player::placeUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile) {
    int tile_id = tile->getId();
    
    /* Check whether the tile is own tile */
    std::vector<int> tile_ids;
    for (auto t : getTiles()) {
        tile_ids.push_back(t->getId());
    }

    if (std::find(tile_ids.begin(), tile_ids.end(), tile_id) == tile_ids.end()) {
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
    unit->setOwner(getThisPlayer());
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
}

void Player::sellBuilding(const std::shared_ptr<Building>& building) {
    auto it = std::find(unplaced_buildings_.begin(), unplaced_buildings_.end(), building);
    if (it != unplaced_buildings_.end()) {
        unplaced_buildings_.erase(it);
        addResource(ResourceType::GOLD, building->getCost());
    }
}

void Player::placeBuilding(const std::shared_ptr<Building>& building, const std::shared_ptr<Tile>& tile) {
    int tile_id = tile->getId();
    /* Check whether the tile is own tile */
    std::vector<int> tile_ids;
    for (auto t : getTiles()) {
        tile_ids.push_back(t->getId());
    }

    if (std::find(tile_ids.begin(), tile_ids.end(), tile_id) == tile_ids.end()) {
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

void Player::removeUnit(const std::shared_ptr<Unit>& unit) {
    movement_handler_->removeUnit(unit);
}
void Player::generateIncome() {
    for (auto resource_income : resource_generation_) {
        resources_[resource_income.first] += resource_income.second;
    }
}

void Player::updateGeneration() {
    /* Remove old values */
    resource_generation_.clear();
    /* Add the currently owned buildings incomes */
    for (auto building : territory_->getBuildings()) {
        auto b = building.lock();

        if (b != nullptr) {
            resource_generation_[b->getIncome().first] += b->getIncome().second;
        }
    }
}

std::shared_ptr<Player> Player::getThisPlayer() {
    return shared_from_this();
}