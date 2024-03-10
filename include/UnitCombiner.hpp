#ifndef UNIT_COMBINER_HPP
#define UNIT_COMBINER_HPP

#include <map>
#include <vector>
#include <memory>
#include "Unit.hpp"

/**
 * @brief A map of combinations of units and their benefits.
 * 
 * S stands for sea movement, M stands for movement, and H stands for hit level.
 */
std::map<std::pair<UnitType, UnitType>, std::pair<char, int>> combinations =
{
    {{UnitType::INFANTRY, UnitType::RIDER}, {'M', 1}},
    {{UnitType::INFANTRY, UnitType::DRAGON}, {'H', 1}},
    {{UnitType::INFANTRY, UnitType::SEA_TRANSPORT}, {'S', 2}},
    {{UnitType::RIDER, UnitType::DRAGON}, {'H', 2}},
    {{UnitType::RIDER, UnitType::SEA_TRANSPORT}, {'S', 2}},
};

/**
 * @file UnitCombiner.hpp
 * @brief UnitCombiner is a class that handles the combining of units and keeps track of benefits.
 * 
 * @version 0.1
 * @date 2024-01-23
 */
class UnitCombiner {
public:
    UnitCombiner();
    ~UnitCombiner();
    void combineUnits(const std::shared_ptr<Unit>& unit1, const std::shared_ptr<Unit>& unit2);
    std::shared_ptr<Unit> getCombinedUnit(const std::shared_ptr<Unit>& unit);
    void removeCombinedUnit(const std::shared_ptr<Unit>& unit);
private:
    std::map<int, std::vector<int>> combined_units_;
};

#endif // UNITCOMBINER_HPP
