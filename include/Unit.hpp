#ifndef UNIT_HPP
#define UNIT_HPP

#include <memory>
#include <string>

#include "Randoms.hpp"
#include "Tile.hpp"
#include "Movement.hpp"


enum class UnitType {
    SURFACE_WARSHIP,
    SEA_TRANSPORT,
    INFANTRY,
    ARTILLERY,
    RIDER,
    DRAGON
};

/**
 * @file Unit.hpp
 * @brief Unit is a class that represents a unit in the game.
 * 
 * @version 0.1
 * @date 2024-01-23
 */

/**
 * @brief Class Unit represents a unit in the game.
 * 
 * Class variables:
 * 
 * - id_ (int): The id of the unit.
 * - hit_level_ (int): The hit level of the unit.
 * - cost_ (std::pair<int, int>): The cost of the unit. <food, wood>
 * - movement_ (int): The amount of steps per round.
 * - movement_left_ (int): The amount of steps left in the current round.
 * - type_ (UnitType): The type of the unit.
 * - tile_ (std::weak_ptr<Tile>): The tile the unit is currently on.
 * - owner_ (std::weak_ptr<Player>): The owner of the unit.
 * 
 */
class Unit {
public:
    /**
     * @brief Construct a new Unit object.
     * 
     * @param id 
     * @param type 
     */
    Unit(const int& id, UnitType type);

    /**
     * @brief Construct a new Unit object, without specifying an id.
     * 
     */
    Unit(UnitType type);

    /**
     * @brief Destructor for the Unit class.
     */
    ~Unit();

    /* Getter functions */
    const int& getHitLevel() const;
    const std::pair<int, int>& getCost() const;
    const int& getMovement() const;
    const int& getMovementLeft() const;
    const int& getId() const;
    UnitType getType() const;
    const char& getTypeChar() const;
    std::shared_ptr<Player> getOwner() const;
    std::shared_ptr<Tile> getTile() const;
    void setCost(std::pair<int, int> cost);

    /* Setter functions */
    void setHitLevel(int hit_level);
    void setMovementLeft(int movement_left);
    void setMovement(int movement);
    void setOwner(const std::shared_ptr<Player>& owner);
    void setTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Checks if a tile is leavable for this particular unit.
     * 
     * A tile is leavable if it is not occupied by an enemy unit.
     */
    bool isLeavableTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Checks if a tile is reachable for this particular unit.
     * 
     * A tile is reachable if it is within the movement range of the unit.
     */
    bool isReachableTile(const std::shared_ptr<Tile>& tile);

protected:
    int id_; /**< The id of the unit. */
    int hit_level_; /**< The hit level of the unit. */
    std::pair<int, int> cost_; /**< The cost of the unit. */
    int movement_; /**< Amount of steps per round. */
    int movement_left_; /**< Amount of steps left in the current round. */

    UnitType type_; /**< The type of the unit. */
    std::weak_ptr<Tile> tile_; /**< The tile the unit is currently on. */
    std::weak_ptr<Player> owner_; /**< The owner of the unit. */
};

#endif // UNIT_HPP
