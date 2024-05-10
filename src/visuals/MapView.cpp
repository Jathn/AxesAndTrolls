#include "MapView.hpp"

MapView::MapView(std::vector<std::shared_ptr<Tile>> tiles, std::pair<int, int> position, std::pair<int, int> size, const std::vector<std::shared_ptr<Player>>& players)
 : position_(position), size_(size) {
    font_.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::White);
    text_.setOutlineColor(sf::Color::Black);
    text_.setOutlineThickness(1);
    
    for (auto player : players) {
        players_.push_back(player);
    }

    int largestX = std::numeric_limits<int>::min();
    int largestY = std::numeric_limits<int>::min();

    for (auto tile : tiles) {
        int tileX = tile->getX();
        largestX = std::max(largestX, tileX);

        int tileY = tile->getY();
        largestY = std::max(largestY, tileY);
    }

    int tile_size = size.first / (largestX + 2);
    int spacing = 0.1 * tile_size;

    for (auto tile : tiles) {
        int tileX = tile->getX();
        int tileY = tile->getY();
        int x = position.first + tileX * (tile_size + spacing);
        int y = position.second + tileY * (tile_size + spacing);
        tile_views_.push_back(TileView(tile, std::make_pair(tile_size, tile_size), std::make_pair(x, y)));
    }

}

void MapView::draw(sf::RenderWindow& window) {
    drawTiles(window);
}

void MapView::drawTiles(sf::RenderWindow& window) {
    for (auto tile_view : tile_views_) {
        tile_view.draw(window);
        auto tile_nr = tile_view.getTileId();
        for (auto player : players_) {
            for (auto tile : player.lock()->getTiles()) {
                if (tile->getId() == tile_nr) {
                    tile_view.drawTerritoryFilter(window, player.lock());
                }
            }
        }
    }
}

int MapView::getTileId(int x, int y) {
    for (auto tile_view : tile_views_) {
        if (tile_view.isInside(x, y)) {
            return tile_view.getTileId();
        }
    }
    return -1;
}