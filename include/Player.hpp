#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>
#include <algorithm>
#include <vector>
#include <exception>

#include <SFML/Graphics.hpp>
#include "MovementHandler.hpp"
#include "Territory.hpp"
#include "Building.hpp"

class Unit;

/**
 * @brief 
 * 
 */
class NotEnoughResourcesException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Not enough resources to perform this operation";
    }
};

class InvalidPlacementException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid placement of unit";
    }
};

/**
 * @file Player.hpp
 * @brief Class for handling the player in the game.
 * 
 * This class is responsible for handling the player in the game. It allows the player to buy units, place units, buy buildings, place buildings, generate income and more.
 * 
 * The class works with Territory, MovementHandler, Unit and Building to handle player interactions with the game.
 * Player keeps track of the players resources, units, buildings and territory.
 * 
 * @see Territory, MovementHandler, Unit, Building
 * 
 * @author Jathn
 * @version 1.1
 * @date 2024-08-02
 */
class Player {
public:
    /**
     * @brief Construct a new Player object.
     * 
     */
    Player(const sf::Color& color = sf::Color::Black, const std::string& name = "Unkown Player");

    /* Getter functions */
    const int& getPlayerNr() const;
    const std::string& getName() const;
    const sf::Color& getColor() const;
    const std::shared_ptr<Territory>& getTerritory() const;
    const std::shared_ptr<MovementHandler>& getMovementHandler() const;
    const std::vector<std::shared_ptr<Tile>> getTiles() const;
    std::vector<std::shared_ptr<Unit>> getUnits() const;
    std::vector<std::shared_ptr<Unit>> getUnplacedUnits() const;
    std::vector<std::shared_ptr<Building>> getBuildings() const;
    std::vector<std::shared_ptr<Building>> getUnplacedBuildings() const;
    const int getResource(ResourceType resource) const;
    const int getResourceGeneration(ResourceType resource) const;

    /* Setter functions */
    void setPlayerNr(int player_nr);
    void setName(const std::string& name);

    /* Unit functions */

    /**
     * @brief Buy a unit. If the player has insufficient resources, a NotEnoughResourcesException is thrown. See: NotEnoughResourcesException
     * 
     * @param unit The unit to buy.
     */
    void buyUnit(const UnitType& unit);

    /**
     * @brief Place a unit on a tile.
     * 
     * @param unit The unit to place.
     * @param tile The tile to place the unit on.
     */
    void placeUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile);

    /* Building functions */

    /**
     * @brief Buy a building. If the player has insufficient resources, a NotEnoughResourcesException is thrown. See: NotEnoughResourcesException
     * 
     * @param building The building to buy.
     */
    void buyBuilding(const BuildingType& building);

    /**
     * @brief Place a building on a tile.
     * 
     * @param building The building to place.
     * @param tile The tile to place the building on.
     */
    void placeBuilding(const std::shared_ptr<Building>& building, const std::shared_ptr<Tile>& tile);
    
    /* Resource functions */

    /**
     * @brief Adds amount of resource to players resources.
     * 
     * @param resource The resource to get the amount of.
     * @return int The amount of the resource.
     */
    void addResource(ResourceType resource, int amount);

    /**
     * @brief Removes amount of resource from players resources.
     * 
     * @param resource The resource to remove the amount of.
     * @return int The amount of the resource.
     */
    void removeResource(ResourceType resource, int amount);

    /**
     * @brief Generates the income: adds resource income value  to players resources.
     * 
     */
    void generateIncome();

    /**
     * @brief Sets the resource generation value for all resources.
     *
     */
    void updateGeneration();

private:
    int player_nr_;
    std::string name_;
    sf::Color color_;
    std::shared_ptr<MovementHandler> movement_handler_;
    std::shared_ptr<Territory> territory_;
    std::vector<std::shared_ptr<Building>> unplaced_buildings_;
    std::map<ResourceType, int> resources_;
    std::map<ResourceType, int> resource_generation_;

};

#endif // PLAYER_HPP
