#ifndef COMBATMOVE_PHASE_HPP
#define COMBATMOVE_PHASE_HPP

#include "Phase.hpp"

class CombatMovePhase : public Phase {
public:
    CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // COMBATMOVE_PHASE_HPP