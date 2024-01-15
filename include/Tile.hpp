#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <memory>

#include <SFML/Graphics.hpp>
#include "Map.hpp"

/**
 * @file Tile.hpp
 * @author Jonathan Ramstedt
 * @brief The Tile represents a square that is part of the game map.
 * 
 * @version 0.1
 * @date 2024-01-15 
 */
class Tile {
public:
    /**
     * @brief Constructor for Tile class.
     * @param id The id of the tile.
     */
    Tile(const int& id) : id_(id) {}
    /**
     * @brief Destructor for Tile class.
     */
    ~Tile();

private:
    const int& id_;
};
#endif // TILE_HPP