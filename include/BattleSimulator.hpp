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
     * @brief Assigns a hit to a unittype. Reducing the number of this unittype by one.
     *          Affects the attacker.
     */
    void takeHitAttacker(UnitType unitType);

    /**
     * @brief Assigns a hit to a unittype. Reducing the number of this unittype by one.
     *          Affects the defender.
     */
    void takeHitDefender(UnitType unitType);

    /**
     * @brief Assigns a hit to a unittype. Reducing the number of this unittype by one.
     * 
     */
    void takeHit(UnitType unitType, std::map<UnitType, std::vector<std::weak_ptr<Unit>>>& units);

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

    /**
     * @brief Get the number of attackers of a specific type.
     * 
     * @param type the type of unit to get the number of attackers for
     * @return const int& the number of attackers of the specified type
     */
    const int getAttackersCount(UnitType type);

    /**
     * @brief Get the number of defenders of a specific type.
     * 
     * @param type the type of unit to get the number of defenders for
     * @return const int& the number of defenders of the specified type
     */
    const int getDefendersCount(UnitType type);

    void rollAllDie();

    /**
     * @brief Check if the battle is over.
     * 
     * @return bool true if the battle is over, false otherwise
     */
    bool isBattleOver() const;

    /**
     * @brief Get the dices rolled for a player.
     * 
     * @param player the player to get the dices rolled for
     * @return const std::map<UnitType, int>& the dices rolled for the player
     */
    const std::map<UnitType, int>& getDicesRolled(const std::shared_ptr<Player>& player);

    /**
     * @brief Get the hitmap for the battle.
     */
    const std::pair<int, int>& getHitMap();

private:
    std::map<std::shared_ptr<Player>, std::map<UnitType, int>> dices_rolled_; /**< Dice rolls for each player. */
    std::pair<int, int> hitMap_;   /**< Accumulated hits for a round. */
    std::map<UnitType, std::vector<std::weak_ptr<Unit>>> attackers_;    /**< The hit level of the unit. */
    std::map<UnitType, std::vector<std::weak_ptr<Unit>>> defenders_;
};

#endif // BATTLE_SIMULATOR_HPP
