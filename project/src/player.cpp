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
}  // namespace player
