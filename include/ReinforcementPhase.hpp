#ifndef REINFORCEMENT_PHASE_HPP
#define REINFORCEMENT_PHASE_HPP

#include "Phase.hpp"

/**
 * @file ReinforcementPhase.hpp
 * @brief Class for handling the reinforcement phase of the game.
 * 
 * This class is responsible for handling the reinforcement phase of the game.
 * The reinforcement phase is when the current player receives reinforcements.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class ReinforcementPhase : public Phase {
public:
    ReinforcementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // REINFORCEMENT_PHASE_HPP