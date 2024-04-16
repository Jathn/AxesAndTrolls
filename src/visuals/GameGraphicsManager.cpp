#include "GameGraphicsManager.hpp"

GameGraphicsManager::GameGraphicsManager(GameStateManager& game_state_manager) : map_view_(game_state_manager.getMap(), std::make_pair(400, 0), std::make_pair(800, 800)) {
    for (auto i = 0; i <= 4; i++) {
        std::shared_ptr<Player> player = std::make_shared<Player>();
        player_views_.push_back(PlayerView(player, std::make_pair(0, 200 * i), std::make_pair(400, 200)));
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
