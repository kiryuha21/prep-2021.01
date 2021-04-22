#include "enemy.h"

namespace enemy {
    enemy::enemy(const std::string& enemy_name, const int _x, const int _y) : enemy_name(enemy_name), x(_x), y(_y) {
        if (enemy_name == "wolf") {
            health = 6;
            damage = 11;
        }
        if (enemy_name == "dog") {
            health = 3;
            damage = 6;
        }
        if (enemy_name == "rat") {
            health = 2;
            damage = 4;
        }
    }

    enemy::enemy() : damage(0), health(0), x(0), y(0) { }

    int enemy::get_x() const {
        return x;
    }

    int enemy::get_y() const {
        return y;
    }

    std::string enemy::get_name() const {
        return enemy_name;
    }

    int enemy::get_health() const {
        return health;
    }

    void enemy::take_damage() {
        health -= 1;
    }

    int enemy::get_damage() const {
        return damage;
    }

    void enemy::die() {
        health = 0;
    }
}
