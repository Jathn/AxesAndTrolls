#include "MapView.hpp"

MapView::MapView(std::vector<std::shared_ptr<Tile>> tiles, std::pair<int, int> position, std::pair<int, int> size) : position_(position), size_(size) {
    font_.loadFromFile("C:/Users/jonne/Documents/OOPC/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::White);
    text_.setOutlineColor(sf::Color::Black);
    text_.setOutlineThickness(1);
    background_.setSize(sf::Vector2f(size_.first, size_.second));
    background_.setPosition(sf::Vector2f(position_.first, position_.second));
    background_.setFillColor(sf::Color(0, 0, 0, 200));

    for (auto tile : tiles) {
        TileView tile_view(tile);
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
    }
}