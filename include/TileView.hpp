#ifndef TILE_VIEW_HPP
#define TILE_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.hpp"

class TileView {
public:
    TileView(const std::shared_ptr<Tile>& tile);

    void draw(sf::RenderWindow& window);

    void drawUnits(sf::RenderWindow& window);

    void setSize(const std::pair<int, int>& size);
private:
    std::pair<int, int> size_;
    std::pair<int, int> position_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::weak_ptr<Tile> tile_;
};

#endif // TILE_VIEW_HPP
