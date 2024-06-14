#include <map>

#include "Building.hpp"

std::map<BuildingType, int> building_costs = {
    {BuildingType::CITY, 30},
    {BuildingType::FARM, 15},
    {BuildingType::LODGE, 15},
    {BuildingType::MINE, 20}
};

std::map<BuildingType, std::pair<ResourceType, int>> building_incomes = {
    {BuildingType::CITY, {ResourceType::GOLD, 5}},
    {BuildingType::FARM, {ResourceType::FOOD, 5}},
    {BuildingType::LODGE, {ResourceType::WOOD, 5}},
    {BuildingType::MINE, {ResourceType::GOLD, 10}}
};

std::map<BuildingType, std::vector<TileType>> suitable_tile_types = {
    {BuildingType::CITY, {TileType::GRASS, TileType::FOREST}},
    {BuildingType::FARM, {TileType::GRASS}},
    {BuildingType::LODGE, {TileType::FOREST}},
    {BuildingType::MINE, {TileType::MOUNTAIN}}
};

std::map<BuildingType, char> type_chars {
    {BuildingType::CITY, 'C'},
    {BuildingType::FARM, 'F'},
    {BuildingType::LODGE, 'L'},
    {BuildingType::MINE, 'M'}
};

std::map<BuildingType, std::string> type_names {
    {BuildingType::CITY, "City"},
    {BuildingType::FARM, "Farm"},
    {BuildingType::LODGE, "Lodge"},
    {BuildingType::MINE, "Mine"}
};

Building::Building(BuildingType type, const std::shared_ptr<Tile>& tile) : type_(type), tile_(tile) {
    cost_ = building_costs[type];
    income_ = building_incomes[type];
    suitable_tile_types_ = suitable_tile_types[type];
}

Building::Building(BuildingType type) : type_(type) {
    cost_ = building_costs[type];
    income_ = building_incomes[type];
    suitable_tile_types_ = suitable_tile_types[type];
}

const BuildingType& Building::getType() const {
    return type_;
}

const char& Building::getTypeChar() const {
    return type_chars[type_];
}
const std::shared_ptr<Tile>& Building::getTile() const {
    return tile_;
}

const int& Building::getCost() const {
    return cost_;
}

const std::pair<ResourceType, int>& Building::getIncome() const {
    return income_;
}

const std::string& Building::getName() const {
    return type_names[type_];
}

void Building::setType(const BuildingType& type) {
    type_ = type;
}

void Building::setTile(const std::shared_ptr<Tile>& tile) {
    tile_ = tile;
}

bool Building::isSuitablePlacement (const TileType& tile_type) {
    for (auto type : suitable_tile_types_) {
        if (type == tile_type) {
            return true;
        }
    }
    return false;
}
