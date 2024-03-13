#ifndef MOVEMENT_HANDLER_HPP
#define MOVEMENT_HANDLER_HPP

#include <vector>
#include <queue>
#include <set>
#include <memory>
#include "Territory.hpp"
#include "Unit.hpp"


/**
 * @file MovementHandler.hpp
 * @brief MovementHandler is a class that handles the movement of units.
 * Is responsible for a players unit movements.
 * 
 * @version 0.1
 * @date 2024-01-23
 */
class MovementHandler {
public:
    MovementHandler(const std::shared_ptr<Territory>& territory);

    /* Getter functions */
    std::vector<std::shared_ptr<Unit>> getUnits() const;
    /**
     * @brief Adds a unit to the movement handler.
     * 
     * @param unit 
     */
    void addUnit(const std::shared_ptr<Unit>& unit);

    /**
     * @brief Removes a unit from the movement handler.
     * 
     * @param unit 
     */
    void removeUnit(const std::shared_ptr<Unit>& unit);

    /**
     * @brief Checks what tiles are available for the unit to move to.
     * 
     * @param unit 
     * 
     * @return std::vector<std::shared_ptr<Tile>> 
     */
    std::vector<std::shared_ptr<Tile>> getAvailableTiles(const std::shared_ptr<Unit>& unit);

    /**
     * @brief Checks what tiles are available for a group of units to move to.
     * 
     */
    std::vector<std::shared_ptr<Tile>> getAvailableTiles(const std::vector<std::shared_ptr<Unit>>& units);

    /**
     * @brief Moves the unit into the given position.
     * If the position is not valid, the unit will not move.
     * If the position is occupied by an enemy unit, it cannot move further, even though it has movement left.
     * Mostly so low movement, that some of conditions rarely matter, and unreachable tiles shouldn't be called with this function anyway.
     * 
     * @param unit 
     * @param tile
     * 
     */
    void moveUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile);

    /**
     * @brief Moves multiple units into the given tile.
     * 
     * @param units the units to be moved.
     * @param tile the tile to move the units to.
     * 
     */
    void moveUnits(const std::vector<std::shared_ptr<Unit>>& units, const std::shared_ptr<Tile>& tile);

private:
    std::vector<std::shared_ptr<Unit>> units_;
    std::shared_ptr<Territory> territory_;
};

#endif // MOVEMENT_HANDLER_HPP