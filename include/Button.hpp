#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

/**
 * @file
 * @brief A visual button.
 * 
 * This class represents a visual button that can be clicked.
 * 
 * The button has a text and a rectangle shape.
 * 
 * @version 1.0
 * @date 2024-05-15
 */
class Button {
public:
    Button(const std::string& text, const std::pair<int, int>& size, const std::pair<int, int>& position);
    
    void draw(sf::RenderWindow& window);

    /**
     * @brief Returns true if x and y are within the rectangle object of the button.
     * 
     * @param x 
     * @param y 
     * @return true 
     * @return false 
     */
    bool isInside(int x, int y);
protected:
    void setColors(sf::Color fill_color, sf::Color outline_color, const int& outline_thickness);
    void setTexture(const sf::Texture texture);
    sf::Font font_;
    sf::Text text_;
    sf::RectangleShape rectangle_;
};

#endif // BUTTON_HPP