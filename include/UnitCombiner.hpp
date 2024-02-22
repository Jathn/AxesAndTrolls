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
    void combineUnits(const std::shared_ptr<Unit>& unit1, const std::shared_ptr<Unit>& unit2);
    std::shared_ptr<Unit> getCombinedUnit(const std::shared_ptr<Unit>& unit);
    void removeCombinedUnit(const std::shared_ptr<Unit>& unit);
private:
    std::map<int, std::vector<int>> combined_units_;
};

#endif // UNITCOMBINER_HPP
