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

Game::Game(std::vector<std::string> player_names) : state_manager_(std::make_pair(11, 7), player_names.size()), graphics_manager_(state_manager_) {
    for (int i = 0; i < player_names.size(); i++) {
        state_manager_.getPlayers()[i]->setName(player_names[i]);
    }
    round_ = 1;
    phase_ = Phase::PLACEMENT;
}

void Game::draw(sf::RenderWindow& window) {
    graphics_manager_.draw(window);
}

void Game::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == 13) {
            phase_ = following_phase[phase_];
        }
    }
}
