#ifndef MAP_VIEW_HPP
#define MAP_VIEW_HPP

#include <algorithm>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "Player.hpp"
#include "TileView.hpp"

/**
 * @file MapView.hpp
 * @brief Class for handling the map view.
 * 
 * This class is responsible for handling the map view.
 * It draws the map and the players' views.
 * 
 * @version 1.0
 * @date 2024-04-24
 */
class MapView {
public:
    MapView(std::vector<std::shared_ptr<Tile>> tiles, std::pair<int, int> position, std::pair<int, int> size, const std::vector<std::shared_ptr<Player>>& players);
    void draw(sf::RenderWindow& window);
    void drawTiles(sf::RenderWindow& window);

    /**
     * @brief Returns the id of a tile at a given position (x, y) on the map.
     * 
     * @param x Tile x position.
     * @param y Tile y position..
     * @return int Tile id, -1 if out of bounds.
     */
    int getTileId(int x, int y);

    /**
     * @brief Sets the players of the map view. Called upon initialization.
     * 
     * @param players 
     */
    void setPlayers(const std::vector<std::shared_ptr<Player>>& players);
private:
    std::vector<std::weak_ptr<Player>> players_;
    std::vector<TileView> tile_views_;
    std::pair<int, int> position_;
    std::pair<int, int> size_;
    sf::Font font_;
    sf::Text text_;
};

#endif // MAP_VIEW_HPP