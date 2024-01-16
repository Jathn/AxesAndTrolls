#include "Map.hpp"

Map::Map(const int& width, const int& height) : width_(width), height_(height) { }

void Map::generate() {
    std::map<TileType, double> tile_types_with_odds = {
        std::make_pair<TileType, double>(TileType::GRASS, 0.5),
        std::make_pair<TileType, double>(TileType::WATER, 0.5)
    };
    for (int row = 0; row < height_; row++) {
        for (int col = 0; col < width_; col++) {
            addTile(row * width_ + col, RANDOM::chooseAlternative<TileType>(tile_types_with_odds));
        }
    }
}