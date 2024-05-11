#ifndef PHASE_HPP
#define PHASE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "GameStateManager.hpp"
#include "GameGraphicsManager.hpp"

class Phase {
public:
    Phase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager);
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    bool checkLeftClick(sf::Event& event);
protected:
    std::weak_ptr<GameStateManager> state_manager_;
    std::weak_ptr<GameGraphicsManager> graphics_manager_;
    std::weak_ptr<Phase> next_phase_;
};

#endif // PHASE_HPP