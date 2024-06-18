#include "CombatMovePhase.hpp"
#include "CombatPhase.hpp"

CombatMovePhase::CombatMovePhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Move Phase") {
        current_tile_view_ = CurrentTileView();
    }

void CombatMovePhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);

        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            state_manager_.lock()->setCurrentTile(tile_id);
        }
    }
}

void CombatMovePhase::draw(sf::RenderWindow& window) {
    if (state_manager_.lock()->getCurrentTile() == nullptr) {
        return;
    }
    std::vector<std::weak_ptr<Unit>> tile_units = state_manager_.lock()->getCurrentTile()->getUnits();
    std::vector<std::shared_ptr<Unit>> player_units = state_manager_.lock()->getCurrentPlayer()->getUnits();
    std::vector<std::weak_ptr<Unit>> units;
    
    for (auto unit : tile_units) {
        if (player_units.end() != std::find(player_units.begin(), player_units.end(), unit.lock())) {
            units.push_back(unit);
        }
    }

    std::string building_name = "No building";
    if (state_manager_.lock()->getCurrentTile()->getBuilding() != nullptr) {
        building_name = state_manager_.lock()->getCurrentTile()->getBuilding()->getName();
    }
    current_tile_view_.draw(window, building_name, units);
}

std::shared_ptr<Phase> CombatMovePhase::getNextPhase() {
    return std::make_shared<CombatPhase>(state_manager_.lock(), graphics_manager_.lock());
}