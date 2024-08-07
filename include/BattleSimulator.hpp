#ifndef BATTLE_SIMULATOR_HPP
#define BATTLE_SIMULATOR_HPP

#include <map>
#include <vector>
#include <memory>

#include "Unit.hpp"
#include "Player.hpp"

/**
 * @file BattleSimulator.hpp
 * @brief BattleSimulator is a class that handles the simulation of battles between units.
 * 
 * @author Jonathan Ramstedt
 * @version 0.1
 * @date 2024-01-23
 */
class BattleSimulator {
public:
    BattleSimulator(std::vector<std::shared_ptr<Unit>> attackers, std::vector<std::shared_ptr<Unit>> defenders);

    /**
     * @brief Simulates the battle of a tile.
     * 
     * @param attacking attaccking units
     * @param defender defending units
     * @return true if attackers win, false if defenders win
     */
    bool simulateBattle(const std::vector<std::shared_ptr<Unit>>& attacking, const std::vector<std::shared_ptr<Unit>>& defender);

    /**
     * @brief Rolls to hit for a unit.
     * 
     * @param unit the unit to roll to hit for
     * @return std::pair<bool, int> a pair where the first value is true if the unit hit and the second value is the hit level
     */
    std::pair<bool, int> rollToHit(const std::shared_ptr<Unit>& unit) const;

    /**
     * @brief Assigns a hit to a unit. Reduces hitpoints.
     * 
     * @param unit the unit to assign a hit to
     */
    void assignHit(const std::shared_ptr<Unit>& unit);

    /**
     * @brief Refreshes the battle simulator.
     *        - Resets the hit map.
     *        - Resets the dice roll tracker.
     */
    void refresh();

    /**
     * @brief Get the status of the battle.
     * 
     * @return std::pair<int, int> a pair where the first value is the number of attackers and the second value is the number of defenders
     */
    std::pair<int, int> getStatus() const;

    bool isBattleOver() const;
private:
    std::map<std::shared_ptr<Player>, std::map<UnitType, int>> dices_rolled_; /**< Dice rolls for each player. */
    std::pair<int, int> hitMap_;   /**< Accumulated hits for a round. */
    std::vector<std::weak_ptr<Unit>> attackers_;    /**< The hit level of the unit. */
    std::vector<std::weak_ptr<Unit>> defenders_;
};

#endif // BATTLE_SIMULATOR_HPP
