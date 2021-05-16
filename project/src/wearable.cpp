#include "wearable.h"

namespace wearable {
    wearable::wearable(const std::string& type, int x, int y) : x(x), y(y) {
        if (type == "armor") {
            this->type = "armor";
            weight = 3;
            armour_points = 3;
        }
        if (type == "helmet") {
            this->type = "helmet";
            weight = 2;
            armour_points = 3;
        }
        if (type == "shield") {
            this->type = "shield";
            weight = 7;
            armour_points = 5;
        }
        if (type == "pants") {
            this->type = "pants";
            weight = 1;
            armour_points = 1;
        }
        if (type == "T-Shirt") {
            this->type = "T-Shirt";
            weight = 1;
            armour_points = 1;
        }
    }

    wearable::wearable() {
        armour_points = 0;
        x = 0;
        y = 0;
    }

    int wearable::get_armour_points() const {
        return armour_points;
    }

    int wearable::get_weight() const {
        return weight;
    }

    int wearable::get_y() const {
        return y;
    }

    int wearable::get_x() const {
        return x;
    }

    std::string wearable::get_type() const {
        return type;
    }

    void wearable::destroy() {
        armour_points = 0;
    }

    bool wearable::operator==(const wearable &other) {
        return type == other.type && armour_points == other.armour_points &&
        weight == other.weight && x == other.x && y == other.y;
    }
}  // namespace wearable
