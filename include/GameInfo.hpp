#ifndef GAMEINFO_HPP
#define GAMEINFO_HPP

#include "GameStateManager.hpp"
#include "Phase.hpp"

/**
 * @file GameInfo.hpp
 * 
 * @brief Game Info is a visual object, displaying round number, player and phase currently active.
 * 
 * @version 1.0
 * @author Jonathan Ramstedt
 */
class GameInfo {
public:
    GameInfo(std::pair<int, int> position, int font_size);
    void draw(sf::RenderWindow& window, int round, std::shared_ptr<Player> player, std::shared_ptr<Phase> phase);
private:
    std::weak_ptr<GameStateManager> game_state_manager_;
    std::shared_ptr<Phase> phase_;
    std::pair<int, int> position_;
    int font_size_;
    sf::Text text_;
    sf::Font font_;
};

#endif // GAMEINFO_HPP