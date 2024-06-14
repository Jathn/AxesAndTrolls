#include "CurrentTileView.hpp"

const std::pair<int, int> position = {100, 800};
const std::pair<int, int> size = {800, 150};
const int unit_view_size = 75;
const std::map<UnitType, int> unitview_x_pos = {
    {UnitType::INFANTRY, 0},
    {UnitType::ARTILLERY, 1},
    {UnitType::RIDER, 2},
    {UnitType::DRAGON, 3}
};

CurrentTileView::CurrentTileView() {
    if (!font_.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        throw std::runtime_error("Font not found");
    }
    text_.setFont(font_);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::Black);

    background_.setSize(sf::Vector2f(200, 200));
    background_.setFillColor(sf::Color(255, 255, 255, 200));

    for (const auto& [type, x_pos] : unitview_x_pos) {
        unit_views_.push_back(UnitView(type));
    }
}

void CurrentTileView::draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units) {
    window.draw(background_);

    text_.setString("Building: " + building);
    text_.setPosition(position.first + 10, position.second + 10);
    window.draw(text_);

    int i = 0;
    std::map<UnitType, int> unit_count;
    for (const auto& unit : units) {
        if (unit.expired()) {
            continue;
        }
        unit_count[unit.lock()->getType()]++;
    }
    
    for (const auto& [type, count] : unit_count) {
        unit_views_[i].draw(window, {position.first + i * size.first / 4, position.second}, unit_view_size, count);
        i++;
    }
}