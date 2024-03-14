#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <algorithm>
#include <vector>

#include "MovementHandler.hpp"
#include "Territory.hpp"

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
    std::vector<std::shared_ptr<Unit>> getUnits() const;

private:
    MovementHandler movement_handler_;
    std::weak_ptr<Territory> territory_;
};

#endif // PLAYER_HPP
