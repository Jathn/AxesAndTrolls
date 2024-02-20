#include "BattleSimulator.hpp"

BattleSimulator::BattleSimulator(std::vector<std::shared_ptr<Unit>> attackers, std::vector<std::shared_ptr<Unit>> defenders) {
    for (auto& attacker : attackers) {
        attackers_.push_back(attacker);
    }
    for (auto& defender : defenders) {
        defenders_.push_back(defender);
    }
}

BattleSimulator::~BattleSimulator() {
}

// Currently always ends up returning true, since Player etc. is not properly implemented
bool BattleSimulator::simulateBattle(const std::vector<std::shared_ptr<Unit>>& attacking, const std::vector<std::shared_ptr<Unit>>& defender) {
    int attacking_hits = 0;
    int defending_hits = 0;
    for (auto& attacker : attacking) {
        auto [hit, hits] = rollToHit(attacker);
        if (hit) {
            attacking_hits += hits;
        }
    }
    for (auto& defender : defender) {
        auto [hit, hits] = rollToHit(defender);
        if (hit) {
            defending_hits += hits;
        }
    }
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