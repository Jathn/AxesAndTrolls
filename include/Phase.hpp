#ifndef PHASE_HPP
#define PHASE_HPP

#include <memory>
#include <SFML/Graphics.hpp>

#include "GameStateManager.hpp"
#include "GameGraphicsManager.hpp"

class Phase {
public:
    Phase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager, const std::string& name);
    virtual void handleEvent(sf::Event& event, sf::RenderWindow& window) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual std::shared_ptr<Phase> getNextPhase() = 0;

    bool checkLeftClick(sf::Event& event);

    bool isDone() const;
protected:
    std::weak_ptr<GameStateManager> state_manager_;
    std::weak_ptr<GameGraphicsManager> graphics_manager_;
    std::string name_;
    bool is_done_;

    void setDone();
};

#endif // PHASE_HPP