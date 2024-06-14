#ifndef CURRENT_TILE_VIEW_HPP
#define CURRENT_TILE_VIEW_HPP

#include "Tile.hpp"
#include "UnitView.hpp"
#include <SFML/Graphics.hpp>

class CurrentTileView {
public:
    CurrentTileView();
    void draw(sf::RenderWindow& window, const std::string& building, const std::vector<std::weak_ptr<Unit>>& units);
private:
    sf::RectangleShape background_;
    sf::Text text_;
    sf::Font font_;
    std::vector<UnitView> unit_views_;
};

#endif // CURRENT_TILE_VIEW_HPP
