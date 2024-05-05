#ifndef PHASE_HPP
#define PHASE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "GameStateManager.hpp"

class Phase {
public:
    Phase(std::shared_ptr<GameStateManager> state_manager);
    virtual void handleEvent(sf::Event& event) = 0;
private:
    std::weak_ptr<GameStateManager> state_manager_;
};

#endif // PHASE_HPP