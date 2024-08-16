#include "DiceView.hpp"

std::unordered_map<int, std::vector<bool>> dice_dots = {
    {0, {false, false, false, false, true, false, false, false, false}},
    {1, {false, false, false, false, true, false, false, false, false}},
    {2, {true, false, false, false, false, false, false, false, true}},
    {3, {true, false, false, false, true, false, false, false, true}},
    {4, {true, false, true, false, false, false, true, false, true}},
    {5, {true, false, true, false, true, false, true, false, true}},
    {6, {true, false, true, true, false, true, true, false, true}}
};

DiceView::DiceView(const std::pair<int, int>& size, const std::pair<int, int>& position) {
    rectangle_.setSize(sf::Vector2f(size.first, size.second));
    rectangle_.setPosition(sf::Vector2f(position.first, position.second));
    rectangle_.setFillColor(sf::Color::Red);
    rectangle_.setOutlineColor(sf::Color::Black);
    rectangle_.setOutlineThickness(2);

    int dotSize = std::min(size.first, size.second) / 15;
    int dotSpacing = (size.first - 3 * dotSize) / 4;
    int dotY = position.second + dotSpacing;
    for (int i = 0; i < 9; i++) {
        int dotX = position.first + dotSpacing + (i % 3) * (dotSize + dotSpacing);
        sf::CircleShape dot(dotSize);
        dot.setPosition(dotX, dotY);
        dot.setFillColor(sf::Color::White);
        dots_.push_back(dot);
        if ((i + 1) % 3 == 0) {
            dotY += dotSize + dotSpacing;
        }
    }
}

void DiceView::draw(sf::RenderWindow& window) {
    window.draw(rectangle_);
    for (auto& dot : dots_) {
        window.draw(dot);
    }
}

void DiceView::setNumber(int number) {
    for (int i = 0; i < 9; i++) {
        dots_[i].setFillColor(dice_dots[number][i] ? sf::Color::White : sf::Color::Red);
    }
}