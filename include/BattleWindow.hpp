#ifndef BATTLE_WINDOW_HPP
#define BATTLE_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "Tile.hpp"
#include "GameStateManager.hpp"

class BattleWindow {
public:
    BattleWindow(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::shared_ptr<Tile> tile, std::shared_ptr<GameStateManager> game_state_manager, std::pair<int, int> position);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    // Add private member variables and functions as needed
};

#endif // BATTLE_WINDOW_HPP