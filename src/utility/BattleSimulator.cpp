#include "BattleSimulator.hpp"

std::vector<UnitType> unitTypes = {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON};

BattleSimulator::BattleSimulator(std::vector<std::shared_ptr<Unit>> attackers, std::vector<std::shared_ptr<Unit>> defenders) {
    

    for (auto& attacker : attackers) {
        attackers_[attacker->getType()].push_back(attacker);
    }
    for (auto& defender : defenders) {
        defenders_[defender->getType()].push_back(defender);
    }

    hitMap_ = std::make_pair(0, 0);

    if (attackers.size() < 1) {
        throw std::invalid_argument("No attackers in battle");
    } else if (defenders.size() < 1) {
        throw std::invalid_argument("No defenders in battle");
    }

    std::shared_ptr<Player> attacker = attackers[0]->getOwner();
    std::shared_ptr<Player> defender = defenders[0]->getOwner();
    if (attacker == nullptr || defender == nullptr) {
        throw std::invalid_argument("No owner for units");
    }

    if (attacker == defender) {
        throw std::invalid_argument("Attacker and defender are the same player");
    }

    dices_rolled_[attacker] = std::map<UnitType, int>();
    dices_rolled_[defender] = std::map<UnitType, int>();
    
}

// Currently always ends up returning true, since Player etc. is not properly implemented
bool BattleSimulator::simulateBattle(const std::vector<std::shared_ptr<Unit>>& attacking, const std::vector<std::shared_ptr<Unit>>& defender) {
    return true;
}

std::pair<bool, int> BattleSimulator::rollToHit(const std::shared_ptr<Unit>& unit) const {

    /* Distribution for dice roll */
    std::map<int, double> alternatives;
    for (int i = 1; i <= 6; i++) {
        alternatives[i] = 1.0 / 6.0;
    }

    /* Outcome of dice roll */
    int fall_out = chooseAlternative<int>(alternatives);

    /* If the outcome is less than or equal to the hit level, the unit hits. First: boolean, Second: rolled number */
    return std::make_pair(fall_out <= unit->getHitLevel(), fall_out);

}

void BattleSimulator::assignHit(const std::shared_ptr<Unit>& unit) {
    std::shared_ptr<Player> player = unit->getOwner();
    if (player == nullptr) return;

    player->removeUnit(unit);
}

void BattleSimulator::takeHit(UnitType unitType, std::map<UnitType, std::vector<std::weak_ptr<Unit>>>& units) {
    assignHit(units[unitType].back().lock());
}

std::pair<int, int> BattleSimulator::getStatus() const {
    return std::make_pair(attackers_.size(), defenders_.size());
}

void BattleSimulator::refresh() {
    hitMap_ = std::make_pair(0, 0);
    dices_rolled_.clear();
}

bool BattleSimulator::isBattleOver() const {
    return attackers_.size() == 0 || defenders_.size() == 0;
}