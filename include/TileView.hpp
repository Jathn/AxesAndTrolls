#ifndef TILE_VIEW_HPP
#define TILE_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.hpp"
#include "Player.hpp"

class TileView {
public:
    TileView(const std::shared_ptr<Tile>& tile, const std::pair<int, int>& size = std::make_pair(100, 100), const std::pair<int, int>& position = std::make_pair(0, 0));

    const int& getTileId() const;
    void draw(sf::RenderWindow& window);

    void drawUnits(sf::RenderWindow& window);

    void setSize(const std::pair<int, int>& size);

    void drawTerritoryFilter(sf::RenderWindow& window, const std::shared_ptr<Player> player);

    bool isInside(int x, int y);
private:
    std::pair<int, int> size_;
    std::pair<int, int> position_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::weak_ptr<Tile> tile_;
};

#endif // TILE_VIEW_HPP
