#ifndef FRIENDLYMOVE_PHASE_HPP
#define FRIENDLYMOVE_PHASE_HPP

#include "Phase.hpp"

/**
 * @file FriendlyMovePhase.hpp
 * @brief Class for handling the friendly move phase of the game.
 * 
 * This class is responsible for handling the friendly move phase of the game. It allows the "current player" to move units.
 * This happens after battles.
 * @version 1.0
 * @date 2024-05-26
 */
class FriendlyMovePhase : public Phase {
public:
    FriendlyMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // FRIENDLYMOVE_PHASE_HPP