#include "GameGraphicsManager.hpp"

GameGraphicsManager::GameGraphicsManager(const std::shared_ptr<GameStateManager>& game_state_manager) : map_view_(game_state_manager->getMap(), std::make_pair(0, 0), std::make_pair(1000, 650), game_state_manager->getPlayers()) {
    for (int i = 0; i < 4; i++) {
        player_views_.push_back(nullptr);
    }
}

void GameGraphicsManager::draw(sf::RenderWindow &window) {
    drawMapView(window);
    drawPlayerViews(window);
}

void GameGraphicsManager::drawPlayerViews(sf::RenderWindow& window) {
    for (auto player_view : player_views_) {
        if (player_view != nullptr) { 
            player_view->draw(window);
        }
    }
}

void GameGraphicsManager::drawMapView(sf::RenderWindow& window) {
    map_view_.draw(window);
}

void GameGraphicsManager::update(const std::shared_ptr<GameStateManager>& game_state_manager) {
    updatePlayerViews(game_state_manager);
}

int GameGraphicsManager::getTileId(int x, int y) {
    return map_view_.getTileId(x, y);
}

void GameGraphicsManager::updatePlayerViews(const std::shared_ptr<GameStateManager>& game_state_manager) {
    std::vector<std::shared_ptr<Player>> players = game_state_manager->getPlayers();
    for (int i = 0; i < players.size(); i++) {
        player_views_[i] = std::make_shared<PlayerView>(players[i], std::make_pair(1400, i*(200 + 20) + 40 ), std::make_pair(400, 200));
    }
}
