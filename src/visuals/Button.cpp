#include "Button.hpp"

Button::Button(const std::string& text, const std::pair<int, int>& size, const std::pair<int, int>& position) {
    font_.loadFromFile("C:/Users/jonne/Documents/oopc/AxesAndTrolls/resources/fonts/TTF/Crimson-Bold.ttf");
    text_.setFont(font_);
    text_.setString(text);
    text_.setCharacterSize(24);
    text_.setFillColor(sf::Color::Black);
    text_.setPosition(position.first + 10, position.second + 10);

    rectangle_.setSize(sf::Vector2f(size.first, size.second));
    rectangle_.setPosition(position.first, position.second);

    rectangle_.setFillColor(sf::Color(196, 164, 132, 200));
    rectangle_.setOutlineColor(sf::Color::Black);
    rectangle_.setOutlineThickness(2);

}

void Button::draw(sf::RenderWindow& window) {
    window.draw(rectangle_);
    window.draw(text_);
}

bool Button::isInside(int x, int y) {
    return rectangle_.getGlobalBounds().contains(x, y);
}
