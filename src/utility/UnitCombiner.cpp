#include "UnitCombiner.hpp"

/**
 * @brief A map of combinations of units and their benefits.
 * 
 * S stands for sea movement, M stands for movement, and H stands for hit level.
 */
std::map<std::pair<UnitType, UnitType>, std::pair<char, int>> combinations =
{
    {{UnitType::INFANTRY, UnitType::RIDER}, {'M', 1}},
    {{UnitType::INFANTRY, UnitType::DRAGON}, {'H', 1}},
    {{UnitType::RIDER, UnitType::DRAGON}, {'H', 2}}
};

void UnitCombiner::addAttribute(const std::pair<char, int>& attribute, const std::shared_ptr<Unit>& unit) {
    const char c = attribute.first;
    const int amount = attribute.second;

    if (c == 'M') {
        const int current_movement = unit->getMovement();
        unit->setMovement(current_movement + amount);
    }

    if (c == 'H') {
        const int current_hit_level = unit->getHitLevel();
        unit->setHitLevel(current_hit_level + amount);
    }
}

UnitCombiner::UnitCombiner() {
}

UnitCombiner::~UnitCombiner() {
    combined_units_.clear();
}

void UnitCombiner::combineUnits(const std::shared_ptr<Unit>& unit1, const std::shared_ptr<Unit>& unit2) {
    // std::pair<UnitType, UnitType> combo1 = std::make_pair(unit1->getType(), unit2->getType());
    // std::pair<UnitType, UnitType> combo2 = std::make_pair(unit2->getType(), unit1->getType());

    // for (auto combo : combinations) {
    //     if (combo.first == combo1) {

    //         combined_units_[unit1] = unit2;
    //         addAttribute(combo.second, unit1);
    //     }
        
    //     if (combo.first == combo2) {
    //         combined_units_[unit2] = unit1;
    //         addAttribute(combo.second, unit2);
    //     }
    // }
}