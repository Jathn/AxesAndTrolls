#include "BuildingBuyButton.hpp"

std::map<BuildingType, std::string> BuildingType_to_string = {
    {BuildingType::CITY, "City"},
    {BuildingType::FARM, "Farm"},
    {BuildingType::LODGE, "Lodge"},
    {BuildingType::MINE, "Mine"}
};

BuildingBuyButton::BuildingBuyButton(const std::pair<int, int>& size, const std::pair<int, int>& position, BuildingType building_type) : Button(BuildingType_to_string.at(building_type), size, position), building_type_(building_type) { 
}

const BuildingType& BuildingBuyButton::getBuildingType() const {
    return building_type_;
}