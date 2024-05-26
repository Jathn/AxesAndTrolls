#ifndef GAME_HPP
#define GAME_HPP

#include "GameStateManager.hpp"
#include "GameGraphicsManager.hpp"

#include "Phase.hpp"
#include "PlacementPhase.hpp"

/**
 * @file Game.hpp
 * @brief Class for handling the game.
 * 
 * This class is responsible for handling the game. It is responsible for managing the game state and the game graphics.
 * 
 * @version 1.0
 * @date 2024-05-26
 */
class Game {
    public:
        Game(const std::shared_ptr<GameStateManager>& state_manager);

        /* Getter Functions*/
        const int& getRound();
        const Phase& getPhase();
        const std::shared_ptr<GameStateManager>& getStateManager();
        const std::shared_ptr<GameGraphicsManager>& getGraphicsManager();

        void draw(sf::RenderWindow& window);

        /**
         * @brief A "pass through" function to enable game and it's components to handle events.
         * 
         * @param event Event polled from the window.
         * @param window The window in main, singular, always.
         */
        void handleEvent(sf::Event& event, sf::RenderWindow& window);

        /**
         * @brief Updates the graphics manager. Called upon game initialization to update player count.
         */
        void updateGraphicsManager();

    private:
        int round_;
        std::shared_ptr<GameStateManager> state_manager_;
        std::shared_ptr<GameGraphicsManager> graphics_manager_;
        std::shared_ptr<Phase> phase_;
};

#endif // GAME_HPP