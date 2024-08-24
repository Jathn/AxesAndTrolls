#ifndef GAME_GRAPHICS_MANAGER_HPP
#define GAME_GRAPHICS_MANAGER_HPP

#include <vector>
#include "PlayerView.hpp"
#include "MapView.hpp"
#include "GameStateManager.hpp"

/**
 * @file GameGraphicsManager.hpp
 * @brief Class for handling the graphics of the game.
 * 
 * This class is responsible for handling the graphics of the game.
 * It draws the map and the players' views.
 * 
 * @version 1.0
 * @date 2024-04-24
 */
class GameGraphicsManager {
public:
    GameGraphicsManager(GameState game_state);

    /**
     * @brief "Pass through" function for drawing the game graphics.
     * 
     * @param window
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Updates the game graphics class. Happens at initialization to update player count.
     * 
     * @param game_state_manager 
     */
    void update(GameState game_state);

    /**
     * @brief Returns the id of a tile at a given position (x, y) on the map.
     * 
     * @param x Tile x position.
     * @param y Tile y position..
     * @return int Tile id, -1 if out of bounds.
     */
    int getTileId(int x, int y);
private:
    void drawPlayerViews(sf::RenderWindow& window);
    void updatePlayerViews(GameState game_state_manager);
    void updateMapView(GameState game_state_manager);
    void drawMapView(sf::RenderWindow& window);
    std::vector<std::shared_ptr<PlayerView>> player_views_;
    MapView map_view_;
};

#endif // GAME_GRAPHICS_MANAGER_HPP