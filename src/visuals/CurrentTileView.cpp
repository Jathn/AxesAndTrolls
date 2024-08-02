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

    select_unit_buttons_.push_back(std::make_unique<Button>("Select Infantry", std::make_pair(size.first / 4, 50), std::make_pair(position.first + unitview_x_pos.at(UnitType::INFANTRY) * size.first / 4, position.second + unit_view_size * 2)));
    select_unit_buttons_.push_back(std::make_unique<Button>("Select Artillery", std::make_pair(size.first / 4, 50), std::make_pair(position.first + unitview_x_pos.at(UnitType::ARTILLERY) * size.first / 4, position.second + unit_view_size * 2)));
    select_unit_buttons_.push_back(std::make_unique<Button>("Select Rider", std::make_pair(size.first / 4, 50), std::make_pair(position.first + unitview_x_pos.at(UnitType::RIDER) * size.first / 4, position.second + unit_view_size * 2)));
    select_unit_buttons_.push_back(std::make_unique<Button>("Select Dragon", std::make_pair(size.first / 4, 50), std::make_pair(position.first + unitview_x_pos.at(UnitType::DRAGON) * size.first / 4, position.second + unit_view_size * 2)));

    move_button_ = std::make_unique<Button>("Move Units", std::make_pair(size.first / 3, 75), std::make_pair(position.first + size.first, position.second + size.second + 10));
    cancel_button_ = std::make_unique<Button>("Cancel", std::make_pair(size.first / 3, 75), std::make_pair(position.first + size.first, position.second + size.second / 2 + 10));
    move_active_ = false;
}

std::vector<std::shared_ptr<Unit>> CurrentTileView::getSelectedUnits() const {
    std::vector<std::shared_ptr<Unit>> selected_units;
    for (auto unit : selected_units_) {
        selected_units.push_back(unit.lock());
    }

    return selected_units;
}

void CurrentTileView::setMoveActive(bool active) {
    move_active_ = active;
}

void CurrentTileView::wipeSelectedUnits() {
    selected_units_.clear();
}

void CurrentTileView::drawUnitViews(sf::RenderWindow& window, const std::vector<std::weak_ptr<Unit>>& units, const std::pair<int, int>& position, const std::pair<int, int>& size) {
    std::map<UnitType, int> unit_count = count_units(units);
    int i = 0;
    for (auto [type, count] : unit_count) {
        unit_views_[i].draw(window, {position.first + i * size.first / 4, position.second}, unit_view_size, count);
        i++;
    }
    drawSelectedCounts(window, position, size);
}


void CurrentTileView::drawSelectedCounts(sf::RenderWindow& window, const std::pair<int, int>& position, const std::pair<int, int>& size) {
    int i = 0;
    std::map<UnitType, int> selected_unit_count = count_units(selected_units_);
    font_ = sf::Font();
    if (!font_.loadFromFile("../resources/fonts/TTF/Crimson-Bold.ttf")) {
        throw std::runtime_error("Could not load font");
    }
    text_.setFont(font_);
    text_.setCharacterSize(unit_view_size / 4);
    text_.setFillColor(sf::Color::Red);
    for (auto [type, count] : selected_unit_count) {
        text_.setString(std::to_string(count));
        text_.setPosition(position.first + i * size.first / 4 + unit_view_size / 2, position.second + unit_view_size);
        window.draw(text_);
        i++;
    }
}

void CurrentTileView::draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units) {

    drawUnitViews(window, units, position, size);

    for (auto& button : select_unit_buttons_) {
        button->draw(window);
    }

    move_button_->draw(window);
    cancel_button_->draw(window);
}

void CurrentTileView::handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position, const std::shared_ptr<GameStateManager>& state_manager) {
    int index = isSelectUnitButtonClicked(position);
    if (index != -1) {
        onSelectUnitButtonClicked(index, state_manager);
    }

    if (isMoveButtonClicked(position)) {
        onMoveButtonClicked();
    } else if (isCancelButtonClicked(position)) {
        onCancelButtonClicked();
    }
}

bool CurrentTileView::isMoveButtonClicked(const sf::Vector2i& position) const {
    return move_button_->isInside(position.x, position.y);
}

bool CurrentTileView::isCancelButtonClicked(const sf::Vector2i& position) const {
    return cancel_button_->isInside(position.x, position.y);
}

int CurrentTileView::isSelectUnitButtonClicked(const sf::Vector2i& position) const {
    for (int i = 0; i < select_unit_buttons_.size(); i++) {
        if (select_unit_buttons_[i]->isInside(position.x, position.y)) {
            return i;
        }
    }
    return -1;
}

void CurrentTileView::onMoveButtonClicked() {
    move_active_ = true;
}

void CurrentTileView::onCancelButtonClicked() {
    if (move_active_) {
        move_active_ = false;
        selected_units_.clear();
    }
}

bool CurrentTileView::isMoveActive() const {
    return move_active_;
}

const std::vector<std::shared_ptr<Unit>> CurrentTileView::filterUnits(const std::vector<std::weak_ptr<Unit>>& units, UnitType type) {
    std::vector<std::shared_ptr<Unit>> filtered_units;
    for (const auto& unit : units) {
        if (unit.expired()) {
            continue;
        }
        if (unit.lock()->getType() == type) {
            filtered_units.push_back(unit.lock());
        }
    }
    return filtered_units;
}

void CurrentTileView::onSelectUnitButtonClicked(const int& index, const std::shared_ptr<GameStateManager>& state_manager) {
    std::map<int, UnitType> unit_types = {
        {0, UnitType::INFANTRY},
        {1, UnitType::ARTILLERY},
        {2, UnitType::RIDER},
        {3, UnitType::DRAGON}
    };

    if (move_active_) {
        return;
    }

    const UnitType type = unit_types[index];
    const int& max = count_units(state_manager->getCurrentTile()->getUnits()).at(type);
    const int& selected = count_units(selected_units_).at(type);

    if (selected >= max) {
        return;
    }

    std::vector<std::shared_ptr<Unit>> filtered_units = filterUnits(state_manager->getCurrentTile()->getUnits(), type);

    std::sort(filtered_units.begin(), filtered_units.end(), [](const std::shared_ptr<Unit>& a, const std::shared_ptr<Unit>& b) {
        return a->getMovementLeft() >= b->getMovementLeft();
    });

    for (const auto& unit : filtered_units) {
        if (unit->getMovementLeft() > 0) {
            selected_units_.push_back(unit);
            break;
        }
    }
}

const std::map<UnitType, int> CurrentTileView::count_units(const std::vector<std::weak_ptr<Unit>>& units) const {
    std::map<UnitType, int> unit_count = {
        {UnitType::INFANTRY, 0},
        {UnitType::ARTILLERY, 0},
        {UnitType::RIDER, 0},
        {UnitType::DRAGON, 0}
    };
    for (const auto& unit : units) {
        if (unit.expired()) {
            continue;
        }
        unit_count[unit.lock()->getType()]++;
    }
    return unit_count;
}