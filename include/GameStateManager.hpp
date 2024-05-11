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
    GameStateManager(std::pair<int, int> mapSize = std::make_pair(10, 10), int num_players = 2);

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
     * @brief Sets the next player to current player.
     * 
     */
    void nextPlayer();
    
    /* Getter functions */
    const std::vector<std::shared_ptr<Tile>>& getMap();
    std::pair<int, int> getMapSize();
    const std::vector<std::shared_ptr<Player>>& getPlayers();
    const std::shared_ptr<Player> getCurrentPlayer();
    std::shared_ptr<Tile> getCurrentTile();

    /* Setter functions */
    void setCurrentTile(const int& id);
    void setCurrentPlayer(const std::shared_ptr<Player>& player);
    void setPlayers(const std::vector<std::shared_ptr<Player>>& players);

private:
    std::vector<std::shared_ptr<Tile>> map_;
    std::vector<std::shared_ptr<Player>> players_;
    int current_player_;
    std::vector<std::weak_ptr<Unit>> selected_units_;
    std::pair<int, int> map_size_;
    std::shared_ptr<Tile> current_tile_;
};

#endif // GAME_STATE_MANAGER_HPP