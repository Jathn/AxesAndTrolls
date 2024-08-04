#ifndef TILE_HPP
#define TILE_HPP

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <Randoms.hpp>

class Unit;
class Player;
class Building;

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

    /* Getter functions */
    std::vector<std::weak_ptr<Tile>> getNeighbors();
    std::shared_ptr<Tile> getNeighbor(int id);
    TileType getNeighborMajorityType();
    TileType getType();
    char getTypeChar();
    const int& getId() const;
    const int& getX() const;
    const int& getY() const;
    const std::vector<std::weak_ptr<Unit>>& getUnits() const;
    const std::shared_ptr<Building>& getBuilding() const;
    const std::weak_ptr<Player>& getOwner() const;

    /* Setter functions */
    void setNeighbors(const std::vector<std::weak_ptr<Tile>>& neighbors);
    void setOwner(const std::shared_ptr<Player>& owner);
    void setBuilding(const std::shared_ptr<Building>& building);
    void setActive(bool active);

    /**
     * @brief Returns true if this tile is the "current tile."
     * 
     */
    bool isCurrent();
    bool isActive();
    /**
     * @brief Makes this tile current if not, and vice versa.
     * 
     */
    void toggleCurrent();
    
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

    /**
     * @brief Removes a unit from the tile.
     * 
     * @param unit The unit to remove.
     */
    void removeUnit(const std::shared_ptr<Unit>& unit);

    /**
     * @brief Checks if a tile is full.
     * 
     * A tile can hold a maximum of 4 units, with heavy units taking up 2 slots.
     */
    bool isFull();

    /**
     * @brief Homogenous checker, i.e. checks if all units on the tile are of the same player.
     * 
     */
    bool isHomogenous();

private:
    int x_;
    int y_;
    int id_;
    bool is_current_;
    bool is_active_;
    TileType type_;
    std::vector<std::weak_ptr<Tile>> neighbors_;
    std::vector<std::weak_ptr<Unit>> units_;
    std::shared_ptr<Building> building_;
    std::weak_ptr<Player> owner_;

    /**
     * @brief Randomizes the type of the tile, by calculating the majority type of the neighbors and then adding a random factor.
     * 
     */
    void randomizeType();
};
#endif // TILE_HPP