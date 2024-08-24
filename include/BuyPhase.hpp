#ifndef BUY_PHASE_HPP
#define BUY_PHASE_HPP

#include "BuyWindow.hpp"
#include "Phase.hpp"

/**
 * @file BuyPhase.hpp
 * @brief Class for handling the buy phase of the game.
 * 
 * This class is responsible for handling the buy phase of the game. It allows the "current player" to buy units and buildings.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class BuyPhase : public Phase {
public:
    BuyPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
private:
    BuyWindow buy_window_;
    std::unique_ptr<Button> confirm_button_;
    std::unique_ptr<Button> buy_menu_button_;
    bool buy_menu_open_;
};

#endif // BUY_PHASE_HPP