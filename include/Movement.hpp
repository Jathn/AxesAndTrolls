#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include <memory>
#include <string>

#include "Tile.hpp"
#include "Unit.hpp"

int manhattanDistance(const std::shared_ptr<Tile>& tile1, const std::shared_ptr<Tile>& tile2) {
    return std::abs(tile1->getX() - tile2->getX()) + std::abs(tile1->getY() - tile2->getY());
}

int calculateDistance(const std::shared_ptr<Tile>& tile1, const std::shared_ptr<Tile>& tile2);

bool isLegalMove(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile1, const std::shared_ptr<Tile>& tile2);

#endif // MOVEMENT_HPP