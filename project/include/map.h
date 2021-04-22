#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <set>

#include "player.h"

#define MAP_ERR   (-1)
#define INPUT_ERR (-2)

namespace map {

class map {
 private:
    int x_size;
    int y_size;
    const std::set<std::string> all_wearables = {"armor", "helmet", "shield", "pants", "T-Shirt"};
    const std::set<std::string> all_enemies = {"wolf", "dog", "rat"};
    player::player main_player;
    enemy::enemy current_enemy;
    std::vector<enemy::enemy> enemies;
    std::vector<wearable::wearable> wearables;
 public:
    explicit map(const std::string& filename);

    ~map() = default;

    void show_info();

    bool search_for_enemy();

    void take_double_damage();

    void make_action(const std::string& action);

    int get_player_health();
};

}  // namespace map
