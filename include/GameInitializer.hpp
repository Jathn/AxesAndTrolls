#ifndef GAME_INITIALIZER_HPP
#define GAME_INITIALIZER_HPP

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>
#include "GameGraphicsManager.hpp"

class GameInitializer {
    public:
        GameInitializer();

        /* Getter functions */
        std::vector<std::string> getPlayerNames();

        /* Setter functions */
        void setDone(bool is_done);

        void draw(sf::RenderWindow& window);

        void handleEvent(sf::Event& event, const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);

        bool isDone();
        
        void toggleDone();
    private:
        std::vector<std::string> player_names_;
        std::string current_name_;
        int num_players_;
        bool is_done_;
};

#endif // GAME_INTIALIZER_HPP