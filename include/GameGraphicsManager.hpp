#ifndef GAME_GRAPHICS_MANAGER_HPP
#define GAME_GRAPHICS_MANAGER_HPP

#include <vector>
#include "PlayerView.hpp"
#include "MapView.hpp"
#include "GameStateManager.hpp"

class GameGraphicsManager {
public:
    GameGraphicsManager(GameStateManager& game_state_manager);
    void draw(sf::RenderWindow& window);
private:
    void drawPlayerViews(sf::RenderWindow& window);
    void drawMapView(sf::RenderWindow& window);
    std::vector<PlayerView> player_views_;
    MapView map_view_;
};

#endif // GAME_GRAPHICS_MANAGER_HPP