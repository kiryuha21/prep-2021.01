#include "player.h"

namespace player {
    int player::get_y() const {
        return y;
    }

    int player::get_x() const {
        return x;
    }

    void player::move_x(const int shift) {
        x += shift;
    }

    void player::move_y(const int shift) {
        y += shift;
    }

    int player::get_health() const {
        return health;
    }

    int player::get_armour_points() const {
        return armour_points;
    }

    void player::take_damage(const enemy::enemy& _enemy) {
        if (armour_points >= _enemy.get_damage()) {
            health -= 1;
        } else {
            health -= (_enemy.get_damage() - armour_points);
        }
    }

    void player::put_on_wearable(const wearable::wearable& _wearable) {
        armour_points += _wearable.get_armour_points();
        armour_weight += _wearable.get_weight();
        wearables_on.push_back(_wearable);
    }

    void player::throw_out_wearable(const std::string& wearable_type) {
        size_t wearables_on_size = wearables_on.size();
        for (size_t i = 0; i < wearables_on_size; ++i) {
            if (wearable_type == wearables_on[i].get_type()) {
                armour_points -= wearables_on[i].get_armour_points();
                wearables_on.erase(wearables_on.begin() + i);
                return;
            }
        }
    }

    bool player::cmp(const wearable::wearable &first, const wearable::wearable &second) {
        return first.get_type() < second.get_type();
    }

    void player::alph_sort() {
        sort(wearables_on.begin(), wearables_on.end(), cmp);
    }

    void player::throw_offer() {
        if (!wearables_on.empty()) {
            alph_sort();
            for (const wearable::wearable& i : wearables_on) {
                std::cout << " * throw " << i.get_type() << std::endl;
            }
        }
    }

    bool player::already_on_check(const wearable::wearable& _wearable) {
        for (const wearable::wearable& i : wearables_on) {
            if (_wearable.get_type() == i.get_type()) {
                return true;
            }
        }
        return false;
    }
}  // namespace player
