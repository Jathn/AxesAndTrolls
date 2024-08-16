#include "UnitView.hpp"

std::map<UnitType, std::string> urls = {
    {UnitType::INFANTRY, "../resources/pics/infantry.png"},
    {UnitType::ARTILLERY, "../resources/pics/artillery.png"},
    {UnitType::RIDER, "../resources/pics/rider.png"},
    {UnitType::DRAGON, "../resources/pics/dragon.png"}
};

UnitView::UnitView(const UnitType& type) {

    type_ = type;

    if (!font_.loadFromFile("../resources/fonts/TTF/crimson-bold.ttf")) {
        throw std::runtime_error("Font not found");
    }

    if (!texture_.loadFromFile(urls[type])) {
        throw std::runtime_error("Texture not found");
    }
}

void UnitView::draw(sf::RenderWindow& window, const std::pair<int, int>& position, const int& size, const int& count) {
    sprite_.setTexture(texture_);
    sprite_.setScale((double) size / texture_.getSize().x, (double) size / texture_.getSize().y);
    sprite_.setPosition(position.first, position.second);
    window.draw(sprite_);
    text_.setFont(font_);
    text_.setCharacterSize(20);
    text_.setFillColor(sf::Color::Black);
    text_.setString(std::to_string(count));
    text_.setPosition((double) (position.first + 1.5 * size), (double) (position.second + 0.5 * size));
    window.draw(text_);
}

UnitType UnitView::getType() {
    return type_;
}