#ifndef COMBATMOVE_PHASE_HPP
#define COMBATMOVE_PHASE_HPP

#include "Phase.hpp"
#include "CurrentTileView.hpp"

/**
 * @file CombatMovePhase.hpp
 * @brief Class for handling the combat move phase of the game.
 * 
 * This class is responsible for handling the combat move phase of the game. It allows the "current player" to move units to attack a square.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class CombatMovePhase : public Phase {
public:
    CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
private:
    CurrentTileView current_tile_view_;
};

#endif // COMBATMOVE_PHASE_HPP