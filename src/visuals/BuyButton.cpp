#include "BuyButton.hpp"

std::map<UnitType, std::string> unittype_to_string = {
    {UnitType::INFANTRY, "I"},
    {UnitType::ARTILLERY, "A"},
    {UnitType::RIDER, "R"},
    {UnitType::DRAGON, "D"}
};

BuyButton::BuyButton(const std::pair<int, int>& size, const std::pair<int, int>& position, UnitType unit_type) : Button(unittype_to_string.at(unit_type), size, position), unit_type_(unit_type) {
}

const UnitType& BuyButton::getUnitType() const {
    return unit_type_;
}