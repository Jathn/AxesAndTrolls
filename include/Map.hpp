#ifndef MAP_HPP
#define MAP_HPP

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include "Tile.hpp"

/**
 * @file ResourceLoading.hpp
 * @author Jonathan Ramstedt
 * @brief The Map class represents a game map.
 * 
 * @version 0.1
 * @date 2024-01-15 
 */
class Map {
public:
    /**
     * @brief Constructs a Map object.
     */
    Map(const int& tile_size=32) : tile_size_(tile_size) { loadMap(); generate(); }

    /**
     * @brief Destroys the Map object.
     */
    ~Map();

    /**
     * @brief Draws the map.
     */
    void draw();

    /**
     * @brief Updates the map.
     */
    void update();

    /**
     * @brief Loads the map.
     */
    void loadMap();

    /**
     * @brief Generates the map.
     */
    void generate();

    /**
     * @brief Adds a tile to the map.
     * @param id The id of the tile.
     */
    void addTile(int id);

private:
    int tile_size_; /**< The size of each tile. */
    std::vector<Tile> map_; /**< The map data. */
};

#endif // MAP_HPP