#ifndef PLACEMENT_PHASE_HPP
#define PLACEMENT_PHASE_HPP

#include "Phase.hpp"

class PlacementPhase : public Phase {
public:
    PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager);
    void handleEvent(sf::Event& event) override;
};

#endif // PLACEMENT_PHASE_HPP