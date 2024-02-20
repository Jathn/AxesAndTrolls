#ifndef BATTLE_SIMULATOR_HPP
#define BATTLE_SIMULATOR_HPP

#include <map>
#include <vector>
#include <memory>

#include "Unit.hpp"

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

private:
    /***/
    std::pair<bool, int> rollToHit(const std::shared_ptr<Unit>& unit) const;
    std::vector<std::weak_ptr<Unit>> attackers_;    /**< The hit level of the unit. */
    std::vector<std::weak_ptr<Unit>> defenders_;
};

#endif // BATTLE_SIMULATOR_HPP
