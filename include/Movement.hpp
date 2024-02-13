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
int calculateDistance(const std::shared_ptr<Tile>& start, const std::shared_ptr<Tile>& goal) {
    // A* algorithm
    std::shared_ptr<Tile> current_tile = start;
    std::vector<int> visited;
    std::map<std::weak_ptr<Tile>, double> possibilities;

    int gScore = 0;
    current_tile = start;
    visited.push_back(current_tile->getId());

    while(!possibilities.empty()) {

        if (current_tile->getId() == goal->getId()) {
            return gScore;
        }

        std::map<std::weak_ptr<Tile>, double>::iterator it = possibilities.begin();
        while(it->first.lock().get() != current_tile.get() && it != possibilities.end()) {
            it++;
        }

        possibilities.erase(it);
        for (auto neighbor : current_tile->getNeighbors()) {
            int f_value = countFScore(neighbor.lock(), goal, gScore);
            possibilities[neighbor] = f_value;
        }

        double lowest = 1000000;

        for (auto possibility : possibilities) {
            if (possibility.second < lowest) {
                current_tile = possibility.first.lock();
                lowest = possibility.second;
            }
        }

        gScore++;
        visited.push_back(current_tile->getId());
    }
    
    
    // No possibilities found
    return -1;
}

#endif // MOVEMENT_HPP