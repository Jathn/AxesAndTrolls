#ifndef GAME_HPP
#define GAME_HPP

#include "GameStateManager.hpp"
#include "GameGraphicsManager.hpp"

enum class Phase {
    START,
    PURCHASE,
    COMBAT_MOVE,
    COMBAT,
    MOVEMENT,
    PLACEMENT,
    INCOME,
    NEXT_PLAYER
};

class Game {
    public:
        Game(std::vector<std::string> player_names);

        void draw(sf::RenderWindow& window);

        void handleEvent(sf::Event& event);

        void initializeGame(int num_players, std::vector<std::string> player_names);

    private:
        int round_;
        Phase phase_;
        GameStateManager state_manager_;
        GameGraphicsManager graphics_manager_;
};

#endif // GAME_HPP