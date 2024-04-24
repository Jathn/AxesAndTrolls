#ifndef GAME_INITIALIZER_HPP
#define GAME_INITIALIZER_HPP

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class GameInitializer {
    public:
        GameInitializer();

        /* Getter functions */
        std::vector<std::string> getPlayerNames();

        void draw(sf::RenderWindow& window);

        void handleEvent(sf::Event& event);

        bool isDone();
        
    private:
        std::vector<std::string> player_names_;
        std::string current_name_;
        int num_players_;
};

#endif // GAME_INTIALIZER_HPP