#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <algorithm>
#include <vector>

#include "Tile.hpp"

enum class PlayerType {
    Greedy, 
    Balanced,
    WideStrategy
};

/**
 * @brief The Player class represents a player in the game.
 * 
 * A player has resources, tiles, units, and cities.
 */
class Player {
public:
    // /**
    //  * @brief Adds a resource to the player's resources.
    //  * 
    //  * @param resource The resource to be added.
    //  */
    // void addResource(const Resource& resource);

    // /**
    //  * @brief Removes a resource from the player's resources.
    //  * 
    //  * @param resource The resource to be removed.
    //  */
    // void removeResource(const Resource& resource);

    // /**
    //  * @brief Gets the resources owned by the player.
    //  * 
    //  * @return The vector of resources owned by the player.
    //  */
    // std::vector<Resource> getResources() const;

    /**
     * @brief Adds a tile to the player's tiles.
     * 
     * @param tile The tile to be added.
     */
    void addTile(const std::shared_ptr<Tile>& tile);

    /**
     * @brief Removes a tile from the player's tiles.
     * 
     * @param tile The tile to be removed.
     */
    void removeTile(const int& id);

    /**
     * @brief Gets the tiles owned by the player.
     * 
     * @return The vector of tiles owned by the player.
     */
    const std::vector<std::weak_ptr<Tile>>& getTiles() const;

//     /**
//      * @brief Adds a unit to the player's units.
//      * 
//      * @param unit The unit to be added.
//      */
//     void addUnit(const Unit& unit);

//     /**
//      * @brief Removes a unit from the player's units.
//      * 
//      * @param unit The unit to be removed.
//      */
//     void removeUnit(const Unit& unit);

//     /**
//      * @brief Gets the units owned by the player.
//      * 
//      * @return The vector of units owned by the player.
//      */
//     std::vector<Unit> getUnits() const;

//     /**
//      * @brief Adds a city to the player's cities.
//      * 
//      * @param city The city to be added.
//      */
//     void addCity(const City& city);

//     /**
//      * @brief Removes a city from the player's cities.
//      * 
//      * @param city The city to be removed.
//      */
//     void removeCity(const City& city);

//     /**
//      * @brief Gets the cities owned by the player.
//      * 
//      * @return The vector of cities owned by the player.
//      */
//     std::vector<City> getCities() const;
// };

private:
    // std::vector<Resource> resources; /**< The resources owned by the player. */
    std::vector<std::weak_ptr<Tile>> tiles_; /**< The tiles owned by the player. */
    PlayerType player_type_;
    // std::vector<Unit> units; /**< The units owned by the player. */
    // std::vector<City> cities; /**< The cities owned by the player. */
};

#endif // PLAYER_HPP
