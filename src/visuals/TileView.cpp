#include "TileView.hpp"

/* type character : picture url */
std::map<char, std::string> tile_pics = {
    {'G', "../resources/pics/grass_tile.png"},
    {'F', "../resources/pics/forest_tile.png"},
    {'M', "../resources/pics/mountain_tile.png"},
    {'W', "../resources/pics/water_tile.png"},
};

/* buildingtype : picture url */
std::map<char, std::string> building_pics = {
    {'C', "../resources/pics/city.png"},
    {'F', "../resources/pics/farm.png"},
    {'M', "../resources/pics/mine.png"},
    {'L', "../resources/pics/mine.png"},
};

TileView::TileView(const std::shared_ptr<Tile>& tile, const std::pair<double, double>& size, const std::pair<double, double>& position) {
    size_ = size;
    position_ = position;
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
    drawBuilding(window);
    if (tile_.lock()->isCurrent()) {
        drawCurrentFrame(window);
    }

    if (tile_.lock()->isActive()) {
        drawActiveFilter(window);
    }
    
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

void TileView::drawBuilding(sf::RenderWindow& window) {
    if (tile_.lock()->getBuilding() != nullptr) {
        sf::RectangleShape rectangle(sf::Vector2f(size_.first / 2, size_.second /2));
        rectangle.setPosition(position_.first, position_.second);
        sf::Texture building_texture;
        building_texture.loadFromFile(building_pics[tile_.lock()->getBuilding()->getTypeChar()]);
        rectangle.setTexture(&building_texture);
        window.draw(rectangle);
    }
}

void TileView::drawColorFilter(sf::RenderWindow& window, sf::Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(size_.first, size_.second));
    rectangle.setPosition(position_.first, position_.second);
    color.a = 100;
    rectangle.setFillColor(color);
    window.draw(rectangle);
}

void TileView::drawActiveFilter(sf::RenderWindow& window) {
    sf::Color color = sf::Color::Black;
    drawColorFilter(window, sf::Color::Green);
}

void TileView::drawTerritoryFilter(sf::RenderWindow& window, const std::shared_ptr<Player> player) {
    drawColorFilter(window, player->getColor());
}

void TileView::drawCurrentFrame(sf::RenderWindow& window) {
    sf::RectangleShape rectangle(sf::Vector2f(size_.first, size_.second));
    rectangle.setPosition(position_.first, position_.second);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(size_.first / 40);
    window.draw(rectangle);
}

bool TileView::isInside(int x, int y) {
    return x >= position_.first && x <= position_.first + size_.first && y >= position_.second && y <= position_.second + size_.second;
}