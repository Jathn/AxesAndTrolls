#include "Game.hpp"

Game::Game(const std::shared_ptr<GameStateManager>& state_manager) : state_manager_(state_manager), graphics_manager_(std::make_shared<GameGraphicsManager>(state_manager)) {
    round_ = 1;
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
}

void Game::handleEvent(sf::Event& event, const std::shared_ptr<Phase>& phase, sf::RenderWindow& window) {
    phase->handleEvent(event, window);
}

void Game::updateGraphicsManager() {
    graphics_manager_->update(state_manager_);
}
