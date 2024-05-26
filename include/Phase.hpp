#ifndef PHASE_HPP
#define PHASE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "GameStateManager.hpp"
#include "GameGraphicsManager.hpp"

/**
 * @file Phase.hpp
 * @brief Class for handling the phases of the game.
 * 
 * This class is responsible for handling the phases of the game.
 * It is an abstract class that is inherited by the different phases of the game.
 * 
 * @version 1.0
 * @date 2024-05-15
 */
class Phase {
public:
    Phase(const std::shared_ptr<GameStateManager>& state_manager,
          const std::shared_ptr<GameGraphicsManager>& graphics_manager, 
          const std::string& name);
    
    /**
     * @brief Reacts to different situations in the game, uniquely based on which phase.
     * 
     * 
     * @param event Event polled from window.
     * @param window The game window, singular, always.
     */
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;

    /**
     * @brief Draws the unique elements of the phase.
     * 
     * This means buttons, text, UI elements or anything else that is needed for the phase.
     * 
     * @param window The game window, singular, always.
     */
    virtual void draw(sf::RenderWindow& window) = 0;

    /**
     * @brief Gets the next phase of the game.
     * 
     * Linked list of phases.
     * This function is used to determine which phase comes after the current phase.
     * 
     * Order:
     * 1. BuyPhase
     * 2. CombatMovePhase
     * 3. CombatPhase
     * 4. FriendlyMovePhase
     * 5. ReinforcementPhase
     * 6. IncomePhase
     * 
     * @return std::shared_ptr<Phase> The next phase of the game.
     */
    virtual std::shared_ptr<Phase> getNextPhase() = 0;

    /* Event analyzer functions */
    bool checkLeftClick(sf::Event& event);

    /**
     * @brief Returns true when the phase is done.
     * 
     * Signals that the game is ready for next phase.
     * 
     * @return true 
     * @return false 
     */
    bool isDone() const;
protected:
    std::weak_ptr<GameStateManager> state_manager_;
    std::weak_ptr<GameGraphicsManager> graphics_manager_;
    std::string name_;
    bool is_done_;

    /**
     * @brief Sets the phase as done.
     * 
     * This function is used to send the game to the next phase.
     */
    void setDone();
};

#endif // PHASE_HPP