#ifndef UNIT_HPP
#define UNIT_HPP

#include <memory>
#include <string>

#include "Randoms.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Movement.hpp"


enum class UnitType {
    SURFACE_WARSHIP,
    SEA_TRANSPORT,
    INFANTRY,
    SPEARMAN,
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
class Unit {
public:

    Unit(const int& hit_level, const int& cost, const int& movement, const std::string& benefits, const int& id);
    /**
     * @brief Destructor for the Unit class.
     */
    ~Unit();

    /* Getter functions */
    const int& getHitLevel() const;
    const int& getCost() const;
    const int& getMovement() const;
    const int& getMovementLeft() const;
    const int& getId() const;
    bool hasCombinedUnit() const;
    std::string getBenefits() const;
    std::shared_ptr<Player> getOwner() const;
    std::vector<std::shared_ptr<Tile>> getReachableTiles() const;
    std::shared_ptr<Tile> getTile() const;
    void setCost(int cost);

    /* Setter functions */
    void setCombinedUnit(const std::shared_ptr<Unit>& combined_unit);
    void setBenefits(const std::string& benefits);
    void setMovementLeft(int movement_left);
    void setMovement(int movement);
    void setOwner(const std::shared_ptr<Player>& owner);
    void setTile(const std::shared_ptr<Tile>& tile);
    void addReachableTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Checks if a tile is leavable.
     * 
     * A tile is leavable if it is not occupied by an enemy unit.
     */
    bool isLeavableTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Checks if a tile is reachable.
     * 
     * A tile is reachable if it is within the movement range of the unit.
     */
    bool isReachableTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Updates the reachable tiles of the unit.
     * 
     * The reachable tiles are the tiles the unit can reach.
     */
    void updateReachableTiles();

    /**
     * @brief Moves the unit to a new tile.
     * 
     * @param tile The tile to move to.
     */
    void move(const std::shared_ptr<Tile>& tile);

protected:
    int id_; /**< The id of the unit. */
    int hit_level_; /**< The hit level of the unit. */
    int cost_; /**< The cost of the unit. */
    int movement_; /**< Amount of steps per round. */
    int movement_left_; /**< Amount of steps left in the current round. */
    std::weak_ptr<Unit> combined_unit_; /**< True if the unit has a combined unit, false otherwise. */
    std::string benefits_; /**< The benefits of the unit. */
    std::weak_ptr<Tile> tile_; /**< The tile the unit is currently on. */
    std::weak_ptr<Player> owner_; /**< The owner of the unit. */
    std::vector<std::weak_ptr<Tile>> reachable_tiles_; /**< The tiles the unit can reach. */
};

#endif // UNIT_HPP
