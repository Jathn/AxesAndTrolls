#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <algorithm>
#include <vector>

#include "MovementHandler.hpp"

class Unit;
/**
 * @brief The Player class represents a player in the game.
 * 
 * A player has resources, tiles, units, and cities.
 */
class Player {
public:
    /**
     * @brief Construct a new Player object.
     * 
     */
    Player();

    /* Getter functions */
    const std::vector<std::shared_ptr<Tile>> getTiles() const;
    std::vector<Unit> getUnits() const;
    
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

private:
    MovementHandler movement_handler_;
    std::vector<std::weak_ptr<Tile>> tiles_;
};

#endif // PLAYER_HPP
