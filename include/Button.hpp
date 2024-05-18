#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
public:
    Button(const std::string& text, const std::pair<int, int>& size, const std::pair<int, int>& position);
    void draw(sf::RenderWindow& window);
    bool isInside(int x, int y);
private:
    sf::Font font_;
    sf::Text text_;
    sf::RectangleShape rectangle_;
};

#endif // BUTTON_HPP