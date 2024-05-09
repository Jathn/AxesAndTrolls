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

    const int& margin = size_.first / 100;
    const int& tile_size = size_.first / tiles.back()->getX() - margin * 2;
    
    for (auto tile : tiles) {
        int centering_factor_x = tile->getX() == 0 ? margin : 0;
        int centering_factor_y = tile->getY() == 0 ? margin * 2 : 0;
        TileView tile_view( tile, 
                            {tile_size, tile_size}, 
                            {position_.first + tile->getX() * (tile_size + margin) + centering_factor_x, position_.second + tile->getY() * (tile_size + margin) + centering_factor_y});
        tile_views_.push_back(tile_view);
    }
    background_.setSize(sf::Vector2f(size_.first, size_.second));
    background_.setPosition(sf::Vector2f(position_.first, position_.second));
    background_.setFillColor(sf::Color(255, 255, 255, 200));

}

void MapView::draw(sf::RenderWindow& window) {
    drawBackground(window);
    drawTiles(window);
}

void MapView::drawBackground(sf::RenderWindow& window) {
    window.draw(background_);
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