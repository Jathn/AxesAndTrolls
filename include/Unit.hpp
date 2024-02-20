#ifndef UNIT_HPP
#define UNIT_HPP

#include <memory>
#include <string>

#include "Randoms.hpp"
#include "Tile.hpp"
#include "Player.hpp"
#include "Movement.hpp"

class Unit {
public:

    Unit(const int& hit_level, const int& cost, const int& movement, const std::string& benefits);
    /**
     * @brief Destructor for the Unit class.
     */
    ~Unit();

    /* Getter functions */
    int getHitLevel() const;
    int getCost() const;
    bool hasCombinedUnit() const;
    std::string getBenefits() const;
    int getMovement() const;
    int getMovementLeft() const;
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

protected:
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
