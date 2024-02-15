#ifndef TILE_HPP
#define TILE_HPP

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <Randoms.hpp>

class Unit;

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
    Tile(const int& id, const int& x, const int& y, const std::vector<std::shared_ptr<Tile>>& neighbors, bool random = true, TileType type = TileType::GRASS);

    /**
     * @brief Destructor for Tile class.
     */
    ~Tile();

    /**
     * @brief Getter for neighbors of this tile.
     * 
     * @return std::vector<Tile> 
     */
    std::vector<std::weak_ptr<Tile>> getNeighbors();

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

    /**
     * @brief Getter for id of tile.
     * @return The id of the tile.
     */
    const int& getId() const;

    /**
     * @brief Getter for x coordinate of tile.
     * @return The x coordinate of the tile.
     */
    const int& getX() const;

    /**
     * @brief Getter for y coordinate of tile.
     * @return The y coordinate of the tile.
     */
    const int& getY() const;

    const std::vector<std::weak_ptr<Unit>>& getUnits() const;

    /**
     * @brief Function for setting the neighbors of a tile.
     * @param neighbors The neighbors of the tile.
     */
    void setNeighbors(const std::vector<std::weak_ptr<Tile>>& neighbors);

    /**
     * @brief Adds a neighbor to the tile.
     * 
     * @param neighbor The neighbor to add.
     */
    void addNeighbor(const std::shared_ptr<Tile>& neighbor);

    /**
     * @brief Adds a unit to the tile.
     * 
     * @param unit The unit to add.
     */
    void addUnit(const std::shared_ptr<Unit>& unit);

private:
    int x_;
    int y_;
    int id_;
    TileType type_;
    std::vector<std::weak_ptr<Tile>> neighbors_;
    std::vector<std::weak_ptr<Unit>> units_;

    /**
     * @brief Randomizes the type of the tile, by calculating the majority type of the neighbors and then adding a random factor.
     * 
     */
    void randomizeType();
};
#endif // TILE_HPP