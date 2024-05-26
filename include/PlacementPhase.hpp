#ifndef PLACEMENT_PHASE_HPP
#define PLACEMENT_PHASE_HPP

#include "Phase.hpp"
#include "BuyPhase.hpp"
#include "Button.hpp"

/**
 * @file PlacementPhase.hpp
 * @brief Class for handling the placement phase of the game.
 * 
 * This class is responsible for handling the placement phase of the game.
 * The placement phase is when the players place their initial cities on the map.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class PlacementPhase : public Phase {
public:
    PlacementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);

    void handleLeftClick(sf::Event& event, sf::Vector2f localPosition);
    void onTileClick(int tile_id);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
private:
    sf::Text text_;
    sf::Font font_;
    std::string text_string_;
    std::shared_ptr<Button> button_;
};

#endif // PLACEMENT_PHASE_HPP