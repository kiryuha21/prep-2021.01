#include "wearable.h"

namespace wearable {
    wearable::wearable(const std::string& type, int x, int y) : x(x), y(y) {
        if (type == "armor") {
            weight = 3;
            armour_points = 3;
        }
        if (type == "helmet") {
            weight = 2;
            armour_points = 3;
        }
        if (type == "shield") {
            weight = 7;
            armour_points = 5;
        }
        if (type == "pants") {
            weight = 1;
            armour_points = 1;
        }
        if (type == "T-Shirt") {
            weight = 1;
            armour_points = 1;
        }
    }

    int wearable::get_armour_points() const {
        return armour_points;
    }

    int wearable::get_weight() const {
        return weight;
    }
}
