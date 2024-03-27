#ifndef UNIT_COMBINER_HPP
#define UNIT_COMBINER_HPP

#include <map>
#include <vector>
#include <memory>
#include "Unit.hpp"

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
    void addAttribute(const std::pair<char, int>& attribute, const std::shared_ptr<Unit>& unit);
    void combineUnits(const std::shared_ptr<Unit>& unit1, const std::shared_ptr<Unit>& unit2);
    bool hasCombinedUnit(int id) const;
private:
    std::map<std::weak_ptr<Unit>, std::weak_ptr<Unit>> combined_units_;
};

#endif // UNITCOMBINER_HPP
