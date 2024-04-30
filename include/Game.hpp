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
        Game(const std::shared_ptr<GameStateManager>& state_manager);

        /* Getter Functions*/
        const int& getRound();
        const Phase& getPhase();
        const std::shared_ptr<GameStateManager>& getStateManager();
        const std::shared_ptr<GameGraphicsManager>& getGraphicsManager();

        void draw(sf::RenderWindow& window);

        void handleEvent(sf::Event& event);

        void updateGraphicsManager();

    private:
        int round_;
        Phase phase_;
        std::shared_ptr<GameStateManager> state_manager_;
        std::shared_ptr<GameGraphicsManager> graphics_manager_;
};

#endif // GAME_HPP