#include "TileView.hpp"

/* type character : picture url */
std::map<char, std::string> tile_pics = {
    {'G', "../../resources/pics/grass_tile.png"},
    {'F', "../../resources/pics/forest_tile.png"},
    {'M', "../../resources/pics/mountain_tile.png"},
    {'W', "../../resources/pics/water_tile.png"},
};

TileView::TileView(const std::shared_ptr<Tile>& tile) {
    size_ = std::make_pair(50, 50);
    position_ = std::make_pair(tile->getX() * size_.first, tile->getY() * size_.second);
    texture_.loadFromFile(tile_pics[tile->getTypeChar()]);
};

void TileView::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(size_.first, size_.second));
    rectangle.setPosition(position_.first, position_.second);
    rectangle.setTexture(&texture_);
    window.draw(rectangle);
}