#ifndef REINFORCEMENT_PHASE_HPP
#define REINFORCEMENT_PHASE_HPP

#include "Phase.hpp"
#include "UnitView.hpp"
#include "Button.hpp"

/**
 * @file ReinforcementPhase.hpp
 * @brief Class for handling the reinforcement phase of the game.
 * 
 * This class is responsible for handling the reinforcement phase of the game.
 * The reinforcement phase is when the current player receives reinforcements.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class ReinforcementPhase : public Phase {
public:
    ReinforcementPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);

    void unitPlacement(sf::Event& event, sf::RenderWindow& window);
    void buildingPlacement(sf::Event& event, sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;

    void drawUnplacedUnits(sf::RenderWindow& window);
    void drawUnplacedBuildings(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;
    bool allUnitsPlaced() const;
    bool allBuildingsPlaced() const;
private:
    std::weak_ptr<Player> current_player_;
    std::vector<std::weak_ptr<Unit>> unplaced_units_;
    std::vector<std::weak_ptr<Building>> unplaced_buildings_;
    std::unique_ptr<Button> sell_button_;
};

#endif // REINFORCEMENT_PHASE_HPP