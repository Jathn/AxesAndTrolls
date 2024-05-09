#ifndef PLACEMENT_PHASE_HPP
#define PLACEMENT_PHASE_HPP

#include "Phase.hpp"

class PlacementPhase : public Phase {
public:
    PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);

    void onTileClick(int tile_id);
    void handleEvent(sf::Event& event) override;
};

#endif // PLACEMENT_PHASE_HPP