#ifndef CURRENT_TILE_VIEW_HPP
#define CURRENT_TILE_VIEW_HPP

#include "Tile.hpp"
#include "UnitView.hpp"
#include <SFML/Graphics.hpp>

class CurrentTileView {
public:
    CurrentTileView();
    void draw(sf::RenderWindow& window, const int& building, const std::map<UnitType, int>& unit_count);
private:
    sf::RectangleShape background_;
    sf::Text text_;
    sf::Font font_;
};

#endif // CURRENT_TILE_VIEW_HPP
