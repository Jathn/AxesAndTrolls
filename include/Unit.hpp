#ifndef UNIT_HPP
#define UNIT_HPP

#include <memory>
#include <string>

class Unit {
public:
    /**
     * @brief Destructor for the Unit class.
     */
    virtual ~Unit() {}

    /**
     * @brief Get the hit level of the unit.
     * @return The hit level of the unit.
     */
    virtual int getHitLevel() const = 0;

    /**
     * @brief Get the cost of the unit.
     * @return The cost of the unit.
     */
    virtual int getCost() const = 0;

    /**
     * @brief Check if the unit has a combined unit.
     * @return True if the unit has a combined unit, false otherwise.
     */
    virtual bool hasCombinedUnit() const = 0;

    /**
     * @brief Get the benefits of the unit.
     * @return The benefits of the unit.
     */
    virtual std::string getBenefits() const = 0;

protected:
    /**
     * @brief Set the cost of the unit.
     * @param cost The cost of the unit.
     */
    virtual void setCost(int cost) = 0;

    /**
     * @brief Set whether the unit has a combined unit.
     * @param hasCombinedUnit True if the unit has a combined unit, false otherwise.
     */
    virtual void setCombinedUnit(bool hasCombinedUnit) = 0;

    /**
     * @brief Set the benefits of the unit.
     * @param benefits The benefits of the unit.
     */
    virtual void setBenefits(const std::string& benefits) = 0;

    int hit_level_; /**< The hit level of the unit. */
    int cost_; /**< The cost of the unit. */
    std::weak_ptr<Unit> combined_unit_; /**< True if the unit has a combined unit, false otherwise. */
    std::string benefits_; /**< The benefits of the unit. */
};

#endif // UNIT_HPP
