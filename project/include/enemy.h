#pragma  once

#include <string>

namespace enemy {

class enemy {
 private:
    int damage = 0;
    int health = 0;
    std::string enemy_name;
    int x, y;
    bool injured = false;

 public:
    explicit enemy(const std::string& enemy_name, int x, int y);

    enemy();

    ~enemy() = default;

    int get_x() const;

    int get_y() const;

    std::string get_name() const;

    int get_health() const;

    int get_damage() const;

    void die();

    void take_damage();

    bool is_injured() const;
};

}  // namespace enemy
