#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <vector>
#include <memory>

#include "Unit.hpp"
#include "Player.hpp"

/**
 * @file GameStateManager.hpp
 * @author Jonathan Ramstedt
 * @brief GameStateManager handles the state of the game from unit positions to tile types and handles communication between components.
 * 
 * @version 0.1
 * @date 2024-01-23
 */
class GameStateManager {
public:

    /**
     * @brief Constructor for GameStateManager class.
     * 
     */
    GameStateManager(const std::pair<int, int>& mapSize = std::make_pair(10, 10), const int& num_players = 2);

    /**
     * @brief Destructor for GameStateManager class.
     * 
     */
    ~GameStateManager();

    /**
     * @brief Function for generating the map based on the map size. see: map_size_ Random map, no seed.
     * 
     */
    void generateMap();

    /**
     * @brief Creates the player vector, based on number of players.
     * 
     */
    void createPlayers(const int& num_players);

    /**
     * @brief 
     * 
     */
    void setCurrentTile(const int& id);

    /* Getter functions */
    std::vector<std::shared_ptr<Tile>> getMap();
    std::pair<int, int> getMapSize();
    std::vector<std::shared_ptr<Player>> getPlayers();
    std::shared_ptr<Tile> getCurrentTile();

private:
    std::vector<std::shared_ptr<Tile>> map_;
    std::vector<std::shared_ptr<Player>> players_;
    std::pair<int, int> map_size_;
    std::shared_ptr<Tile> current_tile_;
};

#endif // GAME_STATE_MANAGER_HPP