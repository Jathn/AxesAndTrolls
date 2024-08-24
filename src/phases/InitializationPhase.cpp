#include "InitializationPhase.hpp"
#include "PlacementPhase.hpp"

InitializationPhase::InitializationPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Initialization Phase") {
    
    num_players_ = 0;
    is_done_ = false;
    current_name_ = "";
}

std::vector<std::string> InitializationPhase::getPlayerNames() {
    return player_names_;
}

void InitializationPhase::draw(sf::RenderWindow& window) {
    graphics_manager_.lock()->draw(window);
}

void InitializationPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    if (checkLeftClick(event)) {
        std::vector<std::shared_ptr<Player>> players;
        players.push_back(std::make_shared<Player>(sf::Color::Red, "Player 1"));
        players.push_back(std::make_shared<Player>(sf::Color::Blue, "Player 2"));
        players.push_back(std::make_shared<Player>(sf::Color::Green, "Player 3"));
        players.push_back(std::make_shared<Player>(sf::Color::Yellow, "Player 4"));

        state_manager_.lock()->setPlayers(players);

        setDone();
    }
}


std::shared_ptr<Phase> InitializationPhase::getNextPhase() {
    return std::make_shared<PlacementPhase>(state_manager_.lock(), graphics_manager_.lock());  
}