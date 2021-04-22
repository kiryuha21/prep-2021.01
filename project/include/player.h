#pragma once

#include "enemy.h"

namespace player {

class player {
 private:
    int health = 100;
    int x = 0, y = 0;
 public:
    void move_x(int shift);

    void move_y(int shift);

    int get_x() const;

    int get_y() const;

    int get_health() const;

    void take_damage(const enemy::enemy& _enemy);
};

}  // namespace player
