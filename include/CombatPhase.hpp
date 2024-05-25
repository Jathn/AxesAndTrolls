#ifndef COMBAT_PHASE_HPP
#define COMBAT_PHASE_HPP

#include "Phase.hpp"

class CombatPhase : public Phase {
public:
    CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // COMBAT_PHASE_HPP