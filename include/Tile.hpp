#ifndef TILE_HPP
#define TILE_HPP

#include <vector>
#include <map>

#include <MapTester.hpp>
#include <Randoms.hpp>

/**
 * @brief The TileType enum represents the type of a tile.
 * 
 */
enum class TileType {
    GRASS,
    FOREST,
    WATER,
    MOUNTAIN,
};

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
    Tile(const int& id, const std::vector<Tile>& neighbors);

    /**
     * @brief Destructor for Tile class.
     */
    ~Tile();

    /**
     * @brief Function for setting the neighbors of a tile.
     * @param neighbors The neighbors of the tile.
     */
    void setNeighbors(const std::vector<Tile>& neighbors);

    /**
     * @brief Getter for neighbors of this tile.
     * 
     * @return std::vector<Tile> 
     */
    std::vector<Tile> getNeighbours();

    /**
     * @brief Gets the neighbor majority
     * 
     */
    TileType getNeighborMajorityType();

    /**
     * @brief Getter for type 
     * 
     */
    TileType getType();

    /**
     * @brief 
     * 
     */
    char getTypeChar();

private:
    int id_;
    TileType type_;
    std::vector<Tile> neighbors_;
};
#endif // TILE_HPP