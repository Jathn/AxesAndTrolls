#include "TileView.hpp"

/* type character : picture url */
std::map<char, std::string> tile_pics = {
    {'G', "../resources/pics/grass_tile.png"},
    {'F', "../resources/pics/forest_tile.png"},
    {'M', "../resources/pics/mountain_tile.png"},
    {'W', "../resources/pics/water_tile.png"},
};

TileView::TileView(const std::shared_ptr<Tile>& tile, const std::pair<int, int>& size) {
    size_ = size;
    position_ = std::make_pair(tile->getX() * size_.first * 1.10 , tile->getY() * size_.second * 1.10);
    texture_.loadFromFile(tile_pics[tile->getTypeChar()]);
    tile_ = tile;
};

const int& TileView::getTileId() const {
    return tile_.lock()->getId();
}

void TileView::draw(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(size_.first, size_.second));
    rectangle.setPosition(position_.first, position_.second);
    rectangle.setTexture(&texture_);
    window.draw(rectangle);
    drawUnits(window);
}

void TileView::drawUnits(sf::RenderWindow& window) {
    int unit_count = tile_.lock()->getUnits().size();
    int current_position_y = -10; // Initialize current position y
    int object_size = size_.first / 8;
    
    while (unit_count > 0) {
        if (unit_count >= 5) {
            sf::CircleShape circle(object_size);
            circle.setFillColor(sf::Color::Black);
            circle.setPosition(position_.first + size_.first / 2 - object_size, position_.second + size_.second / 3 + current_position_y);
            window.draw(circle);
            unit_count -= 5;
            current_position_y += object_size * 2; // Update current position y after drawing circle
        } else if (unit_count >= 3) {
            sf::ConvexShape triangle;
            triangle.setPointCount(3);
            triangle.setPoint(0, sf::Vector2f(0, 0));
            triangle.setPoint(1, sf::Vector2f(object_size * 2, 0));
            triangle.setPoint(2, sf::Vector2f(object_size, object_size * 2));
            triangle.setFillColor(sf::Color::Black);
            triangle.setPosition(position_.first + size_.first / 2 - object_size, position_.second + size_.second / 3 + current_position_y);
            window.draw(triangle);
            unit_count -= 3;
            current_position_y += object_size * 2; // Update current position y after drawing triangle
        } else {
            sf::RectangleShape rectangle(sf::Vector2f(object_size * 2, object_size / 2));
            rectangle.setFillColor(sf::Color::Black);
            rectangle.setPosition(position_.first + size_.first / 2 - object_size, position_.second + size_.second / 3 + current_position_y);
            window.draw(rectangle);
            unit_count -= 1;
            current_position_y += object_size * 2; // Update current position y after drawing rectangle
        } 
    }
}

void TileView::drawTerritoryFilter(sf::RenderWindow& window, const std::shared_ptr<Player> player) {
    sf::RectangleShape rectangle(sf::Vector2f(size_.first, size_.second));
    rectangle.setPosition(position_.first, position_.second);
    sf::Color player_color = player->getColor();
    player_color.a = 100;
    rectangle.setFillColor(player_color);
    window.draw(rectangle);
}