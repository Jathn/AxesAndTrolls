#include "Game.hpp"

Game::Game() : state_manager_(std::make_shared<GameStateManager>(std::make_pair<int, int>(22, 14))), graphics_manager_(std::make_shared<GameGraphicsManager>(state_manager_->getGameState())) {
    round_ = 1;
    phase_ = std::make_shared<InitializationPhase>(state_manager_, graphics_manager_);
    game_info_ = std::make_shared<GameInfo>(std::make_pair<int, int>(100, 0), 20);
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
    phase_->draw(window);
    int num_players = state_manager_->getPlayers().size();
    if (num_players > 0) {
        std::shared_ptr<Player> player = state_manager_->getCurrentPlayer();
        game_info_->draw(window, round_, player, phase_);
    }
}

void Game::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    phase_->handleEvent(event, window);
    GameState state = state_manager_->getGameState();
    
    if (event.type == sf::Event::MouseButtonPressed) {
        graphics_manager_->update(state);
    }
    if (phase_->isDone()) {
        if (state_manager_->getCurrentPlayer() == nullptr) {
            std::cout << "Yeah, buddy... we're done here." << std::endl;
        }
        std::cout << "Go on" << std::endl;
        phase_ = phase_->getNextPhase();
        if (phase_ == nullptr) {
            std::cout << "Phase is nullptr" << std::endl;
        }
    }
}

void Game::updateGraphicsManager() {
    graphics_manager_->update(state_manager_->getGameState());
}
