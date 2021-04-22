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

    wearable();

    int get_weight() const;

    int get_armour_points() const;

    int get_x() const;

    int get_y() const;

    std::string get_type() const;

    void destroy();

    bool operator==(wearable& other);
};

}  // namespace wearable
