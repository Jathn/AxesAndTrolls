#ifndef BATTLE_WINDOW_HPP
#define BATTLE_WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "Tile.hpp"
#include "GameStateManager.hpp"
#include "Button.hpp"
#include "BattleSimulator.hpp"

class BattleWindow {
public:
    BattleWindow(std::shared_ptr<Player> player1, std::shared_ptr<Player> player2, std::vector<std::shared_ptr<Unit>> a_units, std::vector<std::shared_ptr<Unit>> d_units, std::pair<int, int> position);
    void handleEvent(sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

    bool isOver();
private:
    // Add private member variables and functions as needed
    std::unique_ptr<Button> roll_button_;
    std::weak_ptr<Player> player1_;
    std::weak_ptr<Player> player2_;
    std::unique_ptr<BattleSimulator> battle_simulator_;
    std::pair<int, int> position_;

    sf::RectangleShape background_;
};

#endif // BATTLE_WINDOW_HPP