#ifndef DICE_VIEW_HPP
#define DICE_VIEW_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <unordered_map>

/**
 * @file DiceView.hpp
 * @brief A visual representation of a dice.
 * 
 * This class represents a visual representation of a dice.
 * 
 * @version 1.0
 * @date 2024-05-15
 */
class DiceView {
public:
    DiceView(const std::pair<int, int>& size, const std::pair<int, int>& position);
    
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture texture);
    void setNumber(int number);
    int getNumber();
    void roll();
private:
    int number_;
    sf::RectangleShape rectangle_;
    std::vector<sf::CircleShape> dots_;
};

#endif // DICE_VIEW_HPP