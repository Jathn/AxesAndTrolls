#include "CombatPhase.hpp"
#include "FriendlyMovePhase.hpp"

CombatPhase::CombatPhase(const std::shared_ptr<GameStateManager>& state_manager, const std::shared_ptr<GameGraphicsManager>& graphics_manager) :
    Phase(state_manager, graphics_manager, "Combat Phase") {
        updateContestedTiles();
    }

std::shared_ptr<Player> CombatPhase::getAttackingPlayer() {
    // Get attacking player here
    return state_manager_.lock()->getCurrentPlayer();
}

std::shared_ptr<Player> CombatPhase::getDefendingPlayer(const std::shared_ptr<Tile>& tile) {
    // Get defending player here
    return tile->getOwner().lock();
}
    
std::vector<std::shared_ptr<Unit>> CombatPhase::getPlayerUnits(const std::shared_ptr<Tile>& tile, const std::shared_ptr<Player>& player) {
    // Get attacking units here
    std::vector<std::shared_ptr<Unit>> attacking_units;
    for (auto unit : tile->getUnits()) {
        if (unit.lock()->getOwner() == player) {
            attacking_units.push_back(unit.lock());
        }
    }

    return attacking_units;
}

void CombatPhase::startCombat(std::shared_ptr<Tile> tile) {
    // Start combat here
    std::shared_ptr<Player> attacking_player = getAttackingPlayer();
    std::shared_ptr<Player> defending_player = getDefendingPlayer(tile);

    std::vector<std::shared_ptr<Unit>> attacking_units = getPlayerUnits(tile, attacking_player);
    std::vector<std::shared_ptr<Unit>> defending_units = getPlayerUnits(tile, defending_player);

    battle_simulator_ = std::make_unique<BattleSimulator>(attacking_units, defending_units);
}

void CombatPhase::handleEvent(sf::Event& event, sf::RenderWindow& window) {
    // Handle events here
    if (checkLeftClick(event)) {
        sf::Vector2i localPosition = (sf::Vector2i) window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

        int tile_id = graphics_manager_.lock()->getTileId(localPosition.x, localPosition.y);

        if (tile_id == -1) {
            std::cout << "Something else clicked" << std::endl;
        } else {
            if (isContested(state_manager_.lock()->getMap().at(tile_id))) {
                std::cout << "Tile is contested" << std::endl;
            } else {
                std::cout << "Tile is not contested" << std::endl;
            }
        }
        
    }
}


void CombatPhase::updateContestedTiles() {
    // Update contested tiles here
    std::vector<std::shared_ptr<Tile>> contested_tiles = state_manager_.lock()->getContestedTiles();
    for (auto tile : state_manager_.lock()->getMap()) {
        bool is_contested = std::find(contested_tiles.begin(), contested_tiles.end(), tile) != contested_tiles.end();
        tile->setActive(is_contested);
    }
}

void CombatPhase::draw(sf::RenderWindow& window) {
    updateContestedTiles();
}

std::shared_ptr<Phase> CombatPhase::getNextPhase() {
    return std::make_shared<FriendlyMovePhase>(state_manager_.lock(), graphics_manager_.lock());
}

bool CombatPhase::isContested(const std::shared_ptr<Tile>& tile) {
    // Check if tile is contested
    std::vector<std::shared_ptr<Tile>> contested_tiles = state_manager_.lock()->getContestedTiles();

    // One liner -> shorter code -> so much better -> "so much wow" ~Copilot
    return std::find(contested_tiles.begin(), contested_tiles.end(), tile) != contested_tiles.end();
}