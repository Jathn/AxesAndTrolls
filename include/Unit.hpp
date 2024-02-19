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
    /**
     * @brief Get the hit level of the unit.
     * @return The hit level of the unit.
     */
    int getHitLevel() const;

    /**
     * @brief Get the cost of the unit.
     * @return The cost of the unit.
     */
    int getCost() const;

    /**
     * @brief Check if the unit has a combined unit.
     * @return True if the unit has a combined unit, false otherwise.
     */
    bool hasCombinedUnit() const;

    /**
     * @brief Get the benefits of the unit.
     * @return The benefits of the unit.
     */
    std::string getBenefits() const;

    /**
     * @brief Get the movement of the unit.
     * 
     * @return int The movement of the unit.
     */
    int getMovement() const;

    /**
     * @brief Get the movement left of the unit.
     * 
     * @return int The movement left of the unit.
     */
    int getMovementLeft() const;

    /**
     * @brief Get the owner of the unit.
     * 
     * @return std::shared_ptr<Player> The owner of the unit.
     */
    std::shared_ptr<Player> getOwner() const;

    /**
     * @brief Get the reachable tiles of the unit.
     * 
     * Used to mark the tiles the unit can reach.
     */
    std::vector<std::shared_ptr<Tile>> getReachableTiles() const;

    /**
     * @brief Get the tile of the unit.
     * 
     * @return std::shared_ptr<Tile> The tile of the unit.
     */
    std::shared_ptr<Tile> getTile() const;

    /**
     * @brief Set the cost of the unit.
     * @param cost The cost of the unit.
     */
    void setCost(int cost);

    /**
     * @brief Set whether the unit has a combined unit.
     * @param hasCombinedUnit True if the unit has a combined unit, false otherwise.
     */
    void setCombinedUnit(const std::shared_ptr<Unit>& combined_unit);

    /**
     * @brief Set the benefits of t he unit.
     * @param benefits The benefits of the unit.
     */
    void setBenefits(const std::string& benefits);

    /**
     * @brief Set the movement left of the unit.
     * @param movement_left The movement left of the unit.
     */
    void setMovementLeft(int movement_left);

    /**
     * @brief Set the owner of the unit.
     * 
     */
    void setOwner(const std::shared_ptr<Player>& owner);

    /**
     * @brief Set the tile of the unit.
     * @param tile The tile of the unit.
     */
    void setTile(const std::shared_ptr<Tile>& tile);
    
    
    /**
     * @brief Appends a tile to the reachable tiles of the unit.
     * 
     * Helper function for update reachable tiles.
     * 
     * @param tile 
     */
    void addReachableTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Rolls a dice to determine if unit hits. Returns a pair with the first element being the boolean outcome and the second element being the rolled number.
     * 
     */
    std::pair<bool, int> rollToHit() const;

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

    /**
     * @brief Set the movement of the unit.
     * 
     */
    void setMovement(int movement);

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
