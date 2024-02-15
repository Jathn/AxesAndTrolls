#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>

#include "Tile.hpp"
#include "Unit.hpp"

/**
 * @file Movement.hpp
 * @brief File containing functions for movement.
 * 
 * @version 0.1
 * @date 2024-01-10
 */

/**
 * @brief Calculates the manhattan distance between two tiles. 
 *        Formula: sqrt((x1 - x2)^2 + (y1 - y2)^2)
 * @param tile1 
 * @param tile2 
 * @return int 
 */
double manhattanDistance(const std::shared_ptr<Tile>& tile1, const std::shared_ptr<Tile>& tile2) {
    return std::abs(tile1->getX() - tile2->getX()) + std::abs(tile1->getY() - tile2->getY());
}

/**
 * @brief Helper function for A* algorithm implementation.
 * 
 * @param tile 
 * @return int 
 */
int countFScore(std::shared_ptr<Tile> tile, const std::shared_ptr<Tile>& goal, int gScore) {
        return gScore + manhattanDistance(tile, goal);
}

/**
 * @brief Algorithmically finds the shortest path between two tiles.
 * @param unit the unit that we're calculating from
 * @param tile the tile that we're calculating to
 * @return int distance between the unit and the tile
 */
std::pair<int, std::vector<int>> calculateDistance(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& goal) {
    std::shared_ptr<Tile> current_tile = start;
    std::cout << "Starting tile" << current_tile->getId() << std::endl;
    std::vector<int> visited;
    std::map<std::shared_ptr<Tile>, double> possibilities;

    possibilities[current_tile] = 0;

    int gScore = 0;
    current_tile = start;
    visited.push_back(current_tile->getId());

    while (!possibilities.empty()) {
        std::cout << "Possibilities not empty" << std::endl;
        
        if (current_tile->getId() == goal->getId()) {
            std::cout << "Found goal" << std::endl;
            std::cout << "### PATH ###" << std::endl;
            for (auto tile : visited) {
                std::cout << tile << std::endl;
            }
            return std::make_pair(gScore, visited);
        }

        for (auto neighbor : current_tile->getNeighbors()) {
            std::cout << "Calculating f-value for tile nr. " << neighbor.lock()->getId() << std::endl;
            int f_value = countFScore(neighbor.lock(), goal, gScore);
            std::cout << "f-value: " << f_value << std::endl;
            if (std::find(visited.begin(), visited.end(), neighbor.lock()->getId()) != visited.end()) {
                std::cout << "Tile nr. " << neighbor.lock()->getId() << " was already in visited" << std::endl;
                continue;
            }
            std::cout << "Adding to possibilities" << std::endl;
            possibilities[neighbor.lock()] = f_value;
        }

        possibilities.erase(current_tile);

        double lowest = 1000000;
        std::cout << "Searching for lowest from possibilties" << std::endl;
        for (const auto& possibility : possibilities) {
            if (possibility.second < lowest) {
                std::cout << "Assigning new lowest: " << possibility.first->getId() << " score: " << possibility.second  << std::endl; 
                current_tile = possibility.first;
                lowest = possibility.second;
            }
        }

        // Removing the other possibilities except the lowest
        for (auto it = possibilities.begin(); it != possibilities.end(); ) {
            if (it->first->getId() != current_tile->getId()) {
                it = possibilities.erase(it);
            } else {
                it++;
            }
        }

        std::cout << "Lowest was tile nr. " << current_tile->getId() << " with score " << lowest << std::endl;
    
        gScore++;
        visited.push_back(current_tile->getId());
    }

    // No possibilities found
    return std::make_pair(-1, visited);
}

#endif // MOVEMENT_HPP