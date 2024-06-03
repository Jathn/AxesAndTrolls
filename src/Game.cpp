#include "Game.hpp"

Game::Game(const std::shared_ptr<GameStateManager>& state_manager) : state_manager_(state_manager), graphics_manager_(std::make_shared<GameGraphicsManager>(state_manager)) {
    round_ = 1;
    phase_ = std::make_shared<PlacementPhase>(state_manager_, graphics_manager_);
    game_info_ = std::make_shared<GameInfo>(std::make_pair(100, 100), 24);
}

const int& Game::getRound() {
    return round_;
}

const std::shared_ptr<GameStateManager>& Game::getStateManager() {
    return state_manager_;
}

const std::shared_ptr<GameGraphicsManager>& Game::getGraphicsManager() {
    return graphics_manager_;
}

void Game::draw(sf::RenderWindow& window) {
    graphics_manager_->draw(window);
    phase_->draw(window);
    game_info_->draw(window, round_, state_manager_->getCurrentPlayer(), phase_);
}

void Game::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    phase_->handleEvent(event, window);
    if (phase_->isDone()) {
        phase_ = phase_->getNextPhase();
    }
}

void Game::updateGraphicsManager() {
    graphics_manager_->update(state_manager_);
}
