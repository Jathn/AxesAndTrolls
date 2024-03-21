#ifndef BUILDING_HPP
#define BUILDING_HPP

/**
 * @file Building.hpp
 * @author Jonathan Ramstedt
 * @brief Class for storing pointers to resource requiring objects.
 * 
 * @version 0.1
 * @date 2024-03-21 
 */
#include <string>
#include <vector>
#include <memory>
#include <iostream>

class Tile;

enum class BuildingType {
    CITY,
    FARM,
    LODGE,
    MINE
};

class Building {
    public:
        Building(BuildingType type, const std::shared_ptr<Tile>& tile);
        
        /* Getter functions */
        const BuildingType& getType() const;
        const std::shared_ptr<Tile>& getTile() const;

        /* Setter functions */
        void setType(const BuildingType& type);
        void setTile(const std::shared_ptr<Tile>& tile);
    private:
        BuildingType type_;
        std::shared_ptr<Tile> tile_;
};
#endif // BUILDING_HPP
