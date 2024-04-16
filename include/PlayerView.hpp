#ifndef PLAYER_VIEW_HPP
#define PLAYER_VIEW_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Player.hpp"

class PlayerView {
public:
    PlayerView(std::shared_ptr<Player> player, std::pair<int, int> position, std::pair<int, int> size);
    void draw(sf::RenderWindow& window);
    void drawBackground(sf::RenderWindow& window);
    void initializeIcons(const int& y_offset);
    void drawCounts(sf::RenderWindow& window);
    void drawTerritoryCount(sf::RenderWindow& window);
private:
    const std::weak_ptr<Player> player_;
    std::pair<int, int> position_;
    std::pair<int, int> size_;
    sf::Font font_;
    sf::Text text_;
    sf::RectangleShape background_;
    sf::RectangleShape wood_;
    sf::CircleShape gold_;
    sf::CircleShape food_;
};

#endif // PLAYER_VIEW_HPP