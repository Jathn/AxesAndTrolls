#ifndef GAME_GRAPHICS_MANAGER_HPP
#define GAME_GRAPHICS_MANAGER_HPP

#include <vector>
#include "PlayerView.hpp"
#include "MapView.hpp"
#include "GameStateManager.hpp"

class GameGraphicsManager {
public:
    GameGraphicsManager(const std::shared_ptr<GameStateManager>& game_state_manager);
    void draw(sf::RenderWindow& window);
    void update(const std::shared_ptr<GameStateManager>& game_state_manager);
    int getTileId(int x, int y);
private:
    void drawPlayerViews(sf::RenderWindow& window);
    void updatePlayerViews(const std::shared_ptr<GameStateManager>& game_state_manager);
    void drawMapView(sf::RenderWindow& window);
    std::vector<std::shared_ptr<PlayerView>> player_views_;
    MapView map_view_;
};

#endif // GAME_GRAPHICS_MANAGER_HPP