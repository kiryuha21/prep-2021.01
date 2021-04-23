#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

#include "enemy.h"
#include "wearable.h"

namespace player {

class player {
 private:
    int health = 100;
    int x = 0, y = 0;
    int armour_points = 0;
    int armour_weight = 0;
    std::vector<wearable::wearable> wearables_on;
    void alph_sort();
    static bool cmp(const wearable::wearable& first, const wearable::wearable& second);

 public:
    void move_x(int shift);

    void move_y(int shift);

    int get_x() const;

    int get_y() const;

    int get_health() const;

    int get_armour_points() const;

    void take_damage(const enemy::enemy& _enemy);

    void put_on_wearable(const wearable::wearable& _wearable);

    void throw_out_wearable(const std::string& wearable_type);

    void throw_offer();
};

}  // namespace player
