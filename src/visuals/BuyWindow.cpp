#include "BuyWindow.hpp"

const std::vector<UnitType> unit_types = {UnitType::SURFACE_WARSHIP, UnitType::SEA_TRANSPORT, UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON};

BuyWindow::BuyWindow() {
    font_.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf");
    text_.setFont(font_);
    text_.setString("Buy Units");
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Black);
    text_.setPosition(10, 10);

    background_.setSize(sf::Vector2f(750, 750));
    background_.setOutlineThickness(5);
    background_.setOutlineColor(sf::Color(150, 150, 150));
    background_.setFillColor(sf::Color::White);
    background_.setPosition(200, 200);

    int i = 0;
    for (std::vector<UnitType>::const_iterator it = unit_types.begin(); it != unit_types.end(); it++) {
        buttons_.push_back(BuyButton(std::make_pair(50 + i*260, 50 + i*260), std::make_pair(250, 250), *it));
    }
} 

void BuyWindow::draw(sf::RenderWindow& window) {
    window.draw(background_);
    window.draw(text_);
}

void BuyWindow::handleEvent(sf::Event& event, sf::RenderWindow& window, const std::shared_ptr<Player>& player) {
    if (event.type == sf::Event::MouseButtonPressed) {
        for (std::vector<BuyButton>::iterator it = buttons_.begin(); it != buttons_.end(); it++) {
            
            if (it->isInside(event.mouseButton.x, event.mouseButton.y)) {
                player->buyUnit(it->getUnitType());
            }
        }
    }
}
