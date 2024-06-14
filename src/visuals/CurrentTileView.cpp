#include "CurrentTileView.hpp"

const std::pair<int, int> position = {100, 800};
const std::pair<int, int> size = {800, 150};
const int unit_view_size = 100;
const std::map<UnitType, int> unitview_x_pos = {
    {UnitType::INFANTRY, 0},
    {UnitType::ARTILLERY, 1},
    {UnitType::RIDER, 2},
    {UnitType::DRAGON, 3}
};

CurrentTileView::CurrentTileView() {
    for (auto type : {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON}) {
        unit_views_.push_back(UnitView(type));
    }
    std::cout << "CurrentTileView created" << std::endl;
}

void CurrentTileView::draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units) {
    std::map<UnitType, int> unit_count = {
        {UnitType::INFANTRY, 0},
        {UnitType::ARTILLERY, 0},
        {UnitType::RIDER, 0},
        {UnitType::DRAGON, 0}
    };
    std::cout << "Drawing" << std::endl;
    for (const auto& unit : units) {
        if (unit.expired()) {
            continue;
        }
        unit_count[unit.lock()->getType()]++;
    }

    int i = 0;
    for (auto [type, count] : unit_count) {
        std::cout << i << std::endl;
        unit_views_[i].draw(window, {position.first + i * size.first / 4, position.second}, unit_view_size, count);
        i++;
    }
}