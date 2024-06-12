#include "UnitView.hpp"

std::map<UnitType, std::string> urls = {
    {UnitType::INFANTRY, "../resources/pics/infantry.png"},
    {UnitType::ARTILLERY, "../resources/pics/artillery.png"},
    {UnitType::RIDER, "../resources/pics/rider.png"},
    {UnitType::DRAGON, "../resources/pics/dragon.png"}
};

UnitView::UnitView(const UnitType& type) {
    if (!font_.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        throw std::runtime_error("Font not found");
    }
    text_.setFont(font_);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::Black);

    if (!texture_.loadFromFile(urls[type])) {
        throw std::runtime_error("Texture not found");
    }

    sprite_.setTexture(texture_);
}

void UnitView::draw(sf::RenderWindow& window, const std::pair<int, int>& position, const int& size) {
    sprite_.setPosition(position.first, position.second);
    sprite_.setScale(size, size);
    window.draw(sprite_);

    text_.setString(std::to_string(1));
    text_.setPosition(position.first + 5, position.second + 5);
    window.draw(text_);
}