#ifndef COMBATMOVE_PHASE_HPP
#define COMBATMOVE_PHASE_HPP

#include "Phase.hpp"
#include "CurrentTileView.hpp"
#include "Button.hpp"

/**
 * @file CombatMovePhase.hpp
 * @brief Class for handling the combat move phase of the game.
 * 
 * This class is responsible for handling the combat move phase of the game. It allows the "current player" to move units to attack a square.
 * 
 * 
 * @author Jathn
 * @version 1.0
 * @date 2024-05-26
 */
class CombatMovePhase : public Phase {
public:
    std::shared_ptr<Phase> getNextPhase() override;

    CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position);
    void draw(sf::RenderWindow& window) override;
private:
    sf::Text text_;
    sf::Font font_;
    CurrentTileView current_tile_view_;
    std::shared_ptr<Button> next_button_;
};

#endif // COMBATMOVE_PHASE_HPP