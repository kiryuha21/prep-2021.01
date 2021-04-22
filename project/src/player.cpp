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

    void player::take_damage(const enemy::enemy& _enemy) {
        health -= _enemy.get_damage();
    }

    void player::put_on_wearable(const wearable::wearable& _wearable) {
        armour_points += _wearable.get_armour_points();
        armour_weight += _wearable.get_weight();
        wearables_on.push_back(_wearable);
    }
}  // namespace player
