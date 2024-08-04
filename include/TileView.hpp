#ifndef TILE_VIEW_HPP
#define TILE_VIEW_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.hpp"
#include "Player.hpp"

class TileView {
public:
    TileView(const std::shared_ptr<Tile>& tile, const std::pair<double, double>& size = std::make_pair(100, 100), const std::pair<double, double>& position = std::make_pair(0, 0));

    const int& getTileId() const;
    void draw(sf::RenderWindow& window);

    void drawUnits(sf::RenderWindow& window);

    void drawBuilding(sf::RenderWindow& window);

    void setSize(const std::pair<int, int>& size);

    /**
     * @brief Draws a frame around the tile if it is "current tile."
     * 
     * @param window 
     */
    void drawCurrentFrame(sf::RenderWindow& window);

    void drawColorFilter(sf::RenderWindow& window, sf::Color color);

    void drawActiveFilter(sf::RenderWindow& window);
    
    void drawTerritoryFilter(sf::RenderWindow& window, const std::shared_ptr<Player> player);

    bool isInside(int x, int y);
private:
    std::pair<double, double> size_;
    std::pair<double, double> position_;
    sf::RectangleShape current_frame_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    std::weak_ptr<Tile> tile_;
};

#endif // TILE_VIEW_HPP
