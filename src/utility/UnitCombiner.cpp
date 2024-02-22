#include "UnitCombiner.hpp"

UnitCombiner::UnitCombiner() {
    combined_units_ = std::map<int, std::vector<int>>();
}

UnitCombiner::~UnitCombiner() {
    combined_units_.clear();
}

void UnitCombiner::combineUnits(const std::shared_ptr<Unit>& unit1, const std::shared_ptr<Unit>& unit2) {
    int unit1_id = unit1->getId();
    int unit2_id = unit2->getId();
    // Adding to vectors, note it is not, x[a] = y
    combined_units_[unit1_id].push_back(unit2_id);
    combined_units_[unit2_id].push_back(unit1_id);
}