#ifndef COMBAT_PHASE_HPP
#define COMBAT_PHASE_HPP

#include "Phase.hpp"
#include "BattleSimulator.hpp"
#include "BattleWindow.hpp"
#include "Button.hpp"

/**
 * @file CombatPhase.hpp
 * @brief Class for handling the combat phase of the game.
 * 
 * This class is responsible for handling the combat phase of the game.
 * The combat phase is when the outcomes of attacks are simulated.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class CombatPhase : public Phase {
public:
    CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    
    std::shared_ptr<Player> getAttackingPlayer();
    std::shared_ptr<Player> getDefendingPlayer(const std::shared_ptr<Tile>& tile);
    std::vector<std::shared_ptr<Unit>> getPlayerUnits(const std::shared_ptr<Tile>& tile, const std::shared_ptr<Player>& player);
    
    void resolveBattle();
    void inCombatHandleEvent(sf::Event& event, sf::RenderWindow& window);
    void outCombatHandleEvent(sf::Event& event, sf::RenderWindow& window);
    void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
    
    void startCombat(std::shared_ptr<Tile> tile);

    void updateContestedTiles();
    void draw(sf::RenderWindow& window) override;
    std::shared_ptr<Phase> getNextPhase() override;

private:
    bool isContested(const std::shared_ptr<Tile>& tile);
    bool in_combat_ = false;
    std::unique_ptr<BattleWindow> battle_window_;
    std::unique_ptr<Button> finish_button_;
    std::weak_ptr<Tile> battle_tile_;
};

#endif // COMBAT_PHASE_HPP