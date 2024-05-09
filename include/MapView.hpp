#ifndef MAP_VIEW_HPP
#define MAP_VIEW_HPP

#include <algorithm>
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Tile.hpp"
#include "Player.hpp"
#include "TileView.hpp"

class MapView {
public:
    MapView(std::vector<std::shared_ptr<Tile>> tiles, std::pair<int, int> position, std::pair<int, int> size, const std::vector<std::shared_ptr<Player>>& players);
    void draw(sf::RenderWindow& window);
    void drawBackground(sf::RenderWindow& window);
    void drawTiles(sf::RenderWindow& window);
    int getTileId(int x, int y);
private:
    std::vector<std::weak_ptr<Player>> players_;
    std::vector<TileView> tile_views_;
    std::pair<int, int> position_;
    std::pair<int, int> size_;
    sf::Font font_;
    sf::Text text_;
    sf::RectangleShape background_;
};

#endif // MAP_VIEW_HPP