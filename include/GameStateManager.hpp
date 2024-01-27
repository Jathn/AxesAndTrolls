#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <vector>
#include <memory>

#include "Tile.hpp"

/**
 * @brief The GameStateManager class is responsible for managing the game state.
 * 
 */
class GameStateManager {
public:

    /**
     * @brief Constructor for GameStateManager class.
     * 
     */
    GameStateManager(const std::pair<int, int>& mapSize = std::make_pair(10, 10));

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
     * @brief 
     * 
     */
    void setCurrentTile(const int& id);

    /**
     * @brief Function for getting the map
     * 
     * @return std::vector<Tile> The game map
     */
    std::vector<std::shared_ptr<Tile>> getMap();

    /**
     * @brief Function for getting the map size
     * 
     * @return std::pair<int, int> width, height in that order.
     */
    std::pair<int, int> getMapSize();

    /**
     * @brief Returns a shared_ptr to the current tile.
     * 
     */
    std::shared_ptr<Tile> getCurrentTile();

private:
    std::vector<std::shared_ptr<Tile>> map_;
    std::pair<int, int> map_size_;
    std::shared_ptr<Tile> current_tile_;
};

#endif // GAME_STATE_MANAGER_HPP