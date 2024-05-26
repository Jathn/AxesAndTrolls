#ifndef INCOME_PHASE_HPP
#define INCOME_PHASE_HPP

#include "Phase.hpp"

/**
 * @file IncomePhase.hpp
 * @brief Class for handling the income phase of the game.
 * 
 * This class is responsible for handling the income phase of the game.
 * It collects the income for the current player before moving to next round.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class IncomePhase : public Phase {
public:
    IncomePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
};

#endif // INCOME_PHASE_HPP