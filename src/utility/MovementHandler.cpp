#include "MovementHandler.hpp"

MovementHandler::MovementHandler() {
}

void MovementHandler::addUnit(const std::shared_ptr<Unit>& unit) {
    units_.push_back(unit);
}

void MovementHandler::removeUnit(const std::shared_ptr<Unit>& unit) {
    for (auto it = units_.begin(); it != units_.end(); it++) {
        if (it->lock() == unit) {
            units_.erase(it);
            break;
        }
    }
}

std::vector<std::shared_ptr<Tile>> MovementHandler::getAvailableTiles(const std::shared_ptr<Unit>& unit) {
    std::vector<std::shared_ptr<Tile>> availableTiles;
    
    for (auto tile : map_) {
        if (unit->isReachableTile(tile.lock())) {
            availableTiles.push_back(tile.lock());
        }
    }

    return availableTiles;
}

std::vector<std::shared_ptr<Tile>> MovementHandler::getAvailableTiles(const std::vector<std::shared_ptr<Unit>>& units) {
    std::vector<std::shared_ptr<Tile>> availableTiles;
    for (auto unit : units) {
        for (auto tile : map_) {
            if (unit->isReachableTile(tile.lock())) {
                availableTiles.push_back(tile.lock());
            }
        }
    }
    
    return availableTiles;
}

void MovementHandler::moveUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile) {
    std::pair<int, std::vector<int>> route = calculateDistanceGBFS(unit->getTile(), tile);

    /* Handle situation where the position isn't reachable */
    if (route.first == -1) {
        return;
    }

    /* Handle situation where the path is longer than movement left */
    if (route.first > unit->getMovementLeft()) {
        return;
    }

    /* Movement: 
        Takes 1 step through the route at a time. For the sake of it this also has some safety nets.
        The idea is that at the time this is called, there is no possibility of enemy units being encountered.
        If the route is longer than the movement left, the route is shortened to the movement left.
    */
    for (auto it = route.second.begin(); it != route.second.end(); it++) {
        if (unit->getMovementLeft() == 0) {
            break;
        }

        /* Checkout the following Tile object pointer */
        std::shared_ptr<Tile> nextTile = unit->getTile()->getNeighbor(*it);
        if (nextTile == nullptr) {
            break;
        }

        /* Move to the tile */
        int current_movement = unit->getMovementLeft();
        unit->setTile(nextTile);
        unit->setMovementLeft(current_movement - 1);
    }   
}

void MovementHandler::moveUnits(const std::vector<std::shared_ptr<Unit>>& units, const std::shared_ptr<Tile>& tile) {
    for (auto unit : units) {
        moveUnit(unit, tile);
    }
}