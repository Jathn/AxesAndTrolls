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

        handleLeftClick(window, localPosition);
    }
}

void CombatMovePhase::handleLeftClick(sf::RenderWindow& window, const sf::Vector2i& position) {
    int tile_id = graphics_manager_.lock()->getTileId(position.x, position.y);
    if (tile_id == -1) {
        std::cout << "Something else clicked" << std::endl;
    } else {
        if (current_tile_view_.isMoveActive()) {
            std::vector<std::shared_ptr<Unit>> units_to_move = current_tile_view_.getSelectedUnits();
            try {
                state_manager_.lock()->getCurrentPlayer()->getMovementHandler()->moveUnits(units_to_move, state_manager_.lock()->getMap().at(tile_id));
            } catch (std::exception& e) {
                std::cout << e.what() << std::endl;
            }
            
        }

        state_manager_.lock()->setCurrentTile(tile_id);
        current_tile_view_.wipeSelectedUnits();
    }

    current_tile_view_.handleLeftClick(window, position, state_manager_.lock());
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