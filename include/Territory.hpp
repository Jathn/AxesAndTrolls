#ifndef TERRITORY_HPP
#define TERRITORY_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include "Tile.hpp"

/**
 * @file Territory.hpp
 * @brief Class for handling the player's territory.
 * 
 * This class is responsible for handling the player's territory.
 * The territory is the area of the map that the player controls.
 * 
 * @version 1.0
 * @date 2024-03-xx
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