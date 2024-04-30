#include "Game.hpp"

std::map<Phase, Phase> following_phase = {
    {Phase::START, Phase::PURCHASE},
    {Phase::PURCHASE, Phase::COMBAT_MOVE},
    {Phase::COMBAT_MOVE, Phase::COMBAT},
    {Phase::COMBAT, Phase::MOVEMENT},
    {Phase::MOVEMENT, Phase::PLACEMENT},
    {Phase::PLACEMENT, Phase::INCOME},
    {Phase::INCOME, Phase::NEXT_PLAYER},
    {Phase::NEXT_PLAYER, Phase::PLACEMENT}
};

Game::Game(const std::shared_ptr<GameStateManager>& state_manager) : state_manager_(state_manager), graphics_manager_(std::make_shared<GameGraphicsManager>(state_manager)) {
    round_ = 1;
}

const int& Game::getRound() {
    return round_;
}

const Phase& Game::getPhase() {
    return phase_;
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

void Game::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 13) {
            std::cout << "Enter pressed" << std::endl;
        }
    }
}

void Game::updateGraphicsManager() {
    graphics_manager_->update(state_manager_);
}
