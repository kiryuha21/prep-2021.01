#pragma once

#include <string>

namespace wearable {

class wearable {
private:
    std::string type;
    int armour_points;
    int weight;
    int x, y;

public:
    wearable(const std::string& type, int x, int y);

    int get_weight() const;

    int get_armour_points() const;
};

}

