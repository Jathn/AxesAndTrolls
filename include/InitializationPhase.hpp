#ifndef INITIALIZATION_PHASE_HPP
#define INITIALIZATION_PHASE_HPP

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

#include "Phase.hpp"

/**
 * @file InitializationPhase.hpp
 * @brief Class for initializing the game.
 * 
 * This class is responsible for initializing the game.
 * It allows the user to input the number of players and their names.
 * 
 * @version 1.0
 * @date 2024-04-25
 */

class InitializationPhase : public Phase {
    public:
        InitializationPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);

        /* Getter functions */
        std::vector<std::string> getPlayerNames();

        
        void handleEvent(sf::Event& event, sf::RenderWindow& window) override;
        void draw(sf::RenderWindow& window) override;
        std::shared_ptr<Phase> getNextPhase() override;
    private:
        std::vector<std::string> player_names_;
        std::string current_name_;
        int num_players_;
        bool is_done_;
};

#endif // INITIALIZATION_PHASE_HPP