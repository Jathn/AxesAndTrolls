#ifndef UNIT_VIEW_HPP
#define UNIT_VIEW_HPP

#include <SFML/Graphics.hpp>
#include "Unit.hpp"

class UnitView {
public:
    UnitView(const UnitType& type);
    void draw(sf::RenderWindow& window, const std::pair<int, int>& position, const int& size);
private:
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Text text_;
    sf::Font font_;
};

#endif // UNIT_VIEW_HPP