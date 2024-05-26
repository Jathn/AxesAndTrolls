#ifndef COMBAT_PHASE_HPP
#define COMBAT_PHASE_HPP

#include "Phase.hpp"

/**
 * @file CombatPhase.hpp
 * @brief Class for handling the combat phase of the game.
 * 
 * This class is responsible for handling the combat phase of the game.
 * The combat phase is when the outcomes of attacks are simulated.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class CombatPhase : public Phase {
public:
    CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // COMBAT_PHASE_HPP