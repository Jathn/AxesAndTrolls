#ifndef TERRITORY_HPP
#define TERRITORY_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include "Tile.hpp"

/**
 * @brief The Territory class represents a player's tiles in the game.
 * 
 * A player has tiles.
 */
class Territory {
public:
    /**
     * @brief Construct a new Territory object.
     * 
     */
    Territory();

    /* Getter functions */
    const std::vector<std::shared_ptr<Tile>> getTiles() const;
    const std::vector<std::weak_ptr<Building>> getBuildings() const;
    
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
    void removeTile(const std::shared_ptr<Tile>& tile);

private:
    std::vector<std::weak_ptr<Tile>> tiles_;
};

#endif // TERRITORY_HPP