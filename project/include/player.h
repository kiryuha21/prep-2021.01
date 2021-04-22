#pragma once

#include "enemy.h"
#include "wearable.h"
#include <vector>

namespace player {

class player {
 private:
    int health = 100;
    int x = 0, y = 0;
    int armour_points = 0;
    int armour_weight = 0;
    std::vector<wearable::wearable> wearables_on;
 public:
    void move_x(int shift);

    void move_y(int shift);

    int get_x() const;

    int get_y() const;

    int get_health() const;

    void take_damage(const enemy::enemy& _enemy);
    
    void put_on_wearable(const wearable::wearable& _wearable);
};

}  // namespace player
