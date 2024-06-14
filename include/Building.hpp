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

#include "Tile.hpp"

enum class BuildingType {
    CITY,
    FARM,
    LODGE,
    MINE
};

enum class ResourceType {
    FOOD,
    WOOD,
    GOLD
};

class Building {
    public:
        Building(BuildingType type, const std::shared_ptr<Tile>& tile);
        Building(BuildingType type);
        /* Getter functions */
        const BuildingType& getType() const;
        const char& getTypeChar() const;
        const std::shared_ptr<Tile>& getTile() const;
        const int& getCost() const;
        const std::pair<ResourceType, int>& getIncome() const;
        const std::string& getName() const;

        /* Setter functions */
        void setType(const BuildingType& type);
        void setTile(const std::shared_ptr<Tile>& tile);

        /**
         * @brief Check if a building can be placed on a type of tile.
         * 
         * @param tile_type The type of tile to check.
         * @return true if the building can be placed on the tile, false otherwise.
         */
        bool isSuitablePlacement(const TileType& tile_type);
        
    private:
        BuildingType type_;
        std::shared_ptr<Tile> tile_;
        int cost_;
        std::pair<ResourceType, int> income_;
        std::vector<TileType> suitable_tile_types_;
};
#endif // BUILDING_HPP
