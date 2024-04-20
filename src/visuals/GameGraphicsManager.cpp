#include "GameGraphicsManager.hpp"

GameGraphicsManager::GameGraphicsManager(GameStateManager& game_state_manager) : map_view_(game_state_manager.getMap(), std::make_pair(400, 0), std::make_pair(800, 800), game_state_manager.getPlayers()) {
    int i = 0;
    for (auto player : game_state_manager.getPlayers()) {
        player_views_.push_back(PlayerView(player, std::make_pair(1400, i*(200 + 20) + 40 ), std::make_pair(400, 200)));
        i++;
    }
    
}

void GameGraphicsManager::draw(sf::RenderWindow &window) {
    drawMapView(window);
    drawPlayerViews(window);
}

void GameGraphicsManager::drawPlayerViews(sf::RenderWindow& window) {
    for (auto player_view : player_views_) {
        player_view.draw(window);
    }
}

void GameGraphicsManager::drawMapView(sf::RenderWindow& window) {
    map_view_.draw(window);
}
