#include "MapView.hpp"

MapView::MapView(std::vector<std::shared_ptr<Tile>> tiles, std::pair<int, int> position, std::pair<int, int> size, const std::vector<std::shared_ptr<Player>>& players)
 : position_(position), size_(size) {
    font_.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::White);
    text_.setOutlineColor(sf::Color::Black);
    text_.setOutlineThickness(1);
    background_.setSize(sf::Vector2f(size_.first, size_.second));
    background_.setPosition(sf::Vector2f(position_.first, position_.second));
    background_.setFillColor(sf::Color(0, 0, 0, 200));

    for (auto player : players) {
        players_.push_back(player);
    }

    for (auto tile : tiles) {
        TileView tile_view(tile, {size_.first / 10, size_.first / 10});
        tile_views_.push_back(tile_view);
    }
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