#include "BattleSimulator.hpp"
#include "BattleWindow.hpp"

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

    hitMap_ = std::make_pair(0, 0);
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

    if (player == attackers_[unit->getType()].back().lock()->getOwner()) {
        attackers_[unit->getType()].pop_back();
        hitMap_.second--;
    } else {
        defenders_[unit->getType()].pop_back();
        hitMap_.first--;
    }

    player->removeUnit(unit);

}

void BattleSimulator::takeHitDefender(UnitType unitType) {
    assignHit(attackers_[unitType].back().lock());
}

void BattleSimulator::takeHitAttacker(UnitType unitType) {
    assignHit(defenders_[unitType].back().lock());
}

void BattleSimulator::takeHit(UnitType unitType, std::map<UnitType, std::vector<std::weak_ptr<Unit>>>& units) {
    assignHit(units[unitType].back().lock());
}

std::pair<int, int> BattleSimulator::getStatus() const {
    return std::make_pair(attackers_.size(), defenders_.size());
}

const int BattleSimulator::getAttackersCount(UnitType type) {
    if (attackers_.find(type) == attackers_.end()) {
        return 0;
    }
    return attackers_.at(type).size();
}

const int BattleSimulator::getDefendersCount(UnitType type) {
    if (defenders_.find(type) == defenders_.end()) {
        return 0;
    }
    return defenders_.at(type).size();
}

void BattleSimulator::refresh() {
    hitMap_ = std::make_pair(0, 0);
    dices_rolled_.clear();
}

void BattleSimulator::rollAllDie() {
    std::shared_ptr<Player> attacker = attackers_.begin()->second[0].lock()->getOwner();
    std::shared_ptr<Player> defender = defenders_.begin()->second[0].lock()->getOwner();
    std::vector<UnitType> unittypes = {UnitType::INFANTRY, UnitType::ARTILLERY, UnitType::RIDER, UnitType::DRAGON}; 
    for (auto type : unittypes) {
        if (getAttackersCount(type) > 0)  {
            std::pair<bool, int> result = rollToHit(attackers_[type].back().lock());
            if (result.first) {
                hitMap_.first++;
            }
            dices_rolled_[attacker][type] = result.second;
        } else {
            dices_rolled_[attacker][type] = 0;
        }

        if (getDefendersCount(type) > 0) {
            std::pair<bool, int> result = rollToHit(defenders_[type].back().lock());
            if (result.first) {
                hitMap_.second++;
            }
            dices_rolled_[defender][type] = result.second;
        } else {
            dices_rolled_[defender][type] = 0;
        }
    }
}

bool BattleSimulator::isBattleOver() const {
    bool isOver = true;
    for (auto& attacker : attackers_) {
        if (attacker.second.size() > 0) {
            isOver = false;
            break;
        }
    }

    if (isOver) return true;
    
    for (auto& defender : defenders_) {
        if (defender.second.size() > 0) {
            isOver = false;
            break;
        }
    }

    return isOver;
}

const std::map<UnitType, int>& BattleSimulator::getDicesRolled(const std::shared_ptr<Player>& player) {
    return dices_rolled_.at(player);
}

const std::pair<int, int>& BattleSimulator::getHitMap() {
    return hitMap_;
}