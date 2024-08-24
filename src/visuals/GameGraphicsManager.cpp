#include "GameGraphicsManager.hpp"

GameGraphicsManager::GameGraphicsManager(GameState game_state) 
: map_view_(game_state.map, std::make_pair(100, 100), std::make_pair(1000, 650), game_state.players) {
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

void GameGraphicsManager::update(GameState game_state) {
    updatePlayerViews(game_state);
    updateMapView(game_state);
}

int GameGraphicsManager::getTileId(int x, int y) {
    return map_view_.getTileId(x, y);
}

void GameGraphicsManager::updatePlayerViews(GameState game_state) {
    std::vector<std::shared_ptr<Player>> players = game_state.players;
    for (int i = 0; i < players.size(); i++) {
        std::shared_ptr<PlayerView> player_view = std::make_shared<PlayerView>(players[i], std::make_pair(1400, i*(200 + 20) + 40 ), std::make_pair(400, 200));
        player_views_.push_back(player_view);
    }
}

void GameGraphicsManager::updateMapView(GameState game_state) {
    map_view_.setPlayers(game_state.players);
}
