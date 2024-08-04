#include "MovementHandler.hpp"


std::map<UnitType, std::vector<TileType>> availability_map = {
    {UnitType::INFANTRY, {TileType::GRASS, TileType::FOREST}},
    {UnitType::ARTILLERY, {TileType::GRASS, TileType::FOREST}},
    {UnitType::RIDER, {TileType::GRASS, TileType::FOREST}},
    {UnitType::DRAGON, {TileType::GRASS, TileType::FOREST, TileType::MOUNTAIN, TileType::WATER}},
    {UnitType::SURFACE_WARSHIP, {TileType::WATER}},
    {UnitType::SEA_TRANSPORT, {TileType::WATER}}
};

MovementHandler::MovementHandler(const std::shared_ptr<Territory>& territory) : territory_(territory) { }

std::vector<std::shared_ptr<Unit>> MovementHandler::getUnits() const {
    std::vector<std::shared_ptr<Unit>> units;
    for (auto unit : units_) {
        units.push_back(unit);
    }
    return units;
}

void MovementHandler::addUnit(const std::shared_ptr<Unit>& unit) {
    units_.push_back(unit);
}

void MovementHandler::removeUnit(const std::shared_ptr<Unit>& unit) {
    for (auto it = units_.begin(); it != units_.end(); it++) {
        if (*it == unit) {
            units_.erase(it);
            break;
        }
    }
}

std::vector<std::shared_ptr<Tile>> MovementHandler::getAvailableTiles(const std::shared_ptr<Unit>& unit) {
    /* BFS algortihm */
    std::vector<std::shared_ptr<Tile>> available_tiles;
    std::queue<std::pair<std::shared_ptr<Tile>, int>> q;
    std::set<std::shared_ptr<Tile>> visited;

    q.push({unit->getTile(), 0});
    visited.insert(unit->getTile());

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        std::shared_ptr<Tile> current_tile = current.first;
        int current_distance = current.second;

        if (current_distance <= unit->getMovementLeft() && std::find(availability_map[unit->getType()].begin(), availability_map[unit->getType()].end(), current_tile->getType()) != availability_map[unit->getType()].end()) {
            available_tiles.push_back(current_tile);
        }

        if (current_distance < unit->getMovementLeft()) {
            for (const auto& neighbor : current_tile->getNeighbors()) {
                if (visited.find(neighbor.lock()) == visited.end()) {
                    q.push({neighbor.lock(), current_distance + 1});
                    visited.insert(neighbor.lock());
                }
            }
        }
    }

    return available_tiles;
}

std::vector<std::shared_ptr<Tile>> MovementHandler::getAvailableTiles(const std::vector<std::shared_ptr<Unit>>& units) {
    std::vector<std::shared_ptr<Tile>> available_tiles;
    std::map<std::shared_ptr<Tile>, int> tile_count;

    for (const auto& unit : units) {
        auto unit_tiles = getAvailableTiles(unit);
        for (const auto& tile : unit_tiles) {
            tile_count[tile]++;
        }
    }

    for (const auto& tile : tile_count) {
        if (tile.second == units.size()) {
            available_tiles.push_back(tile.first);
        }
    }
    
    return available_tiles;
}

std::vector<std::shared_ptr<Unit>> MovementHandler::getUnplacedUnits() const {
    std::vector<std::shared_ptr<Unit>> unplaced_units;
    for (auto unit : units_) {
        if (unit->getTile() == nullptr) {
            unplaced_units.push_back(unit);
        }
    }
    return unplaced_units;
}

void MovementHandler::moveUnit(const std::shared_ptr<Unit>& unit, const std::shared_ptr<Tile>& tile) {
    std::pair<int, std::vector<int>> route = calculateDistanceGBFS(unit->getTile(), tile, getReachableTileFunction(unit));
    std::vector<int> path = route.second;
    std::cout << "Path calculated, length: " << path.size() << std::endl;
    path.erase(path.begin());
    /* Handle situation where the position isn't reachable */
    if (route.first == -1) {
        throw MovementUnaccessibleException();
    }

    std::vector<std::shared_ptr<Tile>> available_tiles = getAvailableTiles(unit);
    std::cout << "Available tiles: " << available_tiles.size() << std::endl;
    /* Handle situation where the tile is not in the available tiles */
    if (std::find(available_tiles.begin(), available_tiles.end(), tile) == available_tiles.end()) {
        return;
    } 

    /* Movement: 
        Takes 1 step through the route at a time. For the sake of it this also has some safety nets.
        The idea is that at the time this is called, there is no possibility of enemy units being encountered.
        If the route is longer than the movement left, the route is shortened to the movement left.
    */
    for (auto it = path.begin(); it != path.end(); it++) {
        std::cout << "Moving along the path" << std::endl;
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
        unit->getTile()->removeUnit(unit);
        unit->setTile(nextTile);
        nextTile->addUnit(unit);
        unit->setMovementLeft(current_movement - 1);
        territory_->addTile(nextTile);
    }   
}

void MovementHandler::moveUnits(const std::vector<std::shared_ptr<Unit>>& units, const std::shared_ptr<Tile>& tile) {
    std::cout << "Moving units" << std::endl;
    std::cout << "Units: " << units.size() << std::endl;
    /* Don't move if all units can't reach the tile */
    for (auto unit : units) {
        if (!unit->isReachableTile(tile)) {
            return;
        }
    }
    std::cout << "All units can reach the tile" << std::endl;

    std::cout << "Moving all Units" << std::endl;
    for (auto unit : units) {
        moveUnit(unit, tile);
    }
}

std::function<bool(const std::shared_ptr<Tile>&)> MovementHandler::getReachableTileFunction(const std::shared_ptr<Unit>& unit) {
    return [unit](const std::shared_ptr<Tile>& tile) {
        return std::find(availability_map[unit->getType()].begin(), availability_map[unit->getType()].end(), tile->getType()) != availability_map[unit->getType()].end();
    };
}