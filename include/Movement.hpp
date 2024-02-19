#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <map>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <functional>

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
inline double manhattanDistance(const std::shared_ptr<Tile>& tile1, const std::shared_ptr<Tile>& tile2) {
    return std::sqrt(std::pow((double)tile1->getX() - (double)tile2->getX(), 2) + std::pow((double)tile1->getY() - (double)tile2->getY(), 2));
}

/**
 * @brief Helper function for A* algorithm implementation.
 * 
 * @param tile 
 * @return int 
 */
inline int countFScore(std::shared_ptr<Tile> tile, const std::shared_ptr<Tile>& goal, int gScore) {
        return gScore + manhattanDistance(tile, goal);
}

/**
 * @brief Base function for checking movement legality
 * 
 * @return true, always
 */
inline bool trueFunction(const std::shared_ptr<Tile>& tile) {
    return true;
}

/**
 * @brief Algorithmically finds the shortest path between two tiles.
 * @param unit the unit that we're calculating from
 * @param tile the tile that we're calculating to
 * @return int distance between the unit and the tile
 */
inline std::pair<int, std::vector<int>> calculateDistanceGBFS(const std::shared_ptr<Tile>& start, 
                                                              const std::shared_ptr<Tile>& goal, 
                                                              std::function<bool(const std::shared_ptr<Tile>&)> check = trueFunction, 
                                                              std::function<bool(const std::shared_ptr<Tile>&)> leaveCheck = trueFunction) {
    // GBFS algorithm
    std::shared_ptr<Tile> current_tile = start;
    std::vector<int> visited;
    std::map<std::shared_ptr<Tile>, double> possibilities;

    possibilities[current_tile] = 0;

    int gScore = 0;
    current_tile = start;
    visited.push_back(current_tile->getId());

    // Continue until goal is found or all possible states are visited
    while (!possibilities.empty()) {
        
        if (current_tile->getId() == goal->getId()) {
            for (auto tile : visited) {
                std::cout << tile << std::endl;
            }
            return std::make_pair(gScore, visited);
        }
        // Add suitable niehgbors to possible solutions
        for (auto neighbor : current_tile->getNeighbors()) {
            double f_value = manhattanDistance(neighbor.lock(), goal);
            if ((std::find(visited.begin(), visited.end(), neighbor.lock()->getId()) != visited.end()) || !check(neighbor.lock()) || !leaveCheck(current_tile)) {
                continue;
            }
            possibilities[neighbor.lock()] = f_value;
        }

        possibilities.erase(current_tile);

        double lowest = 1000000;
        for (const auto& possibility : possibilities) {
            if (possibility.second < lowest) {
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
    
        gScore++;
        visited.push_back(current_tile->getId());
    }

    // No possibilities found
    return std::make_pair(-1, visited);
}

#endif // MOVEMENT_HPP