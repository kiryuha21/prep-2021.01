#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>

#include "player.h"

#define MAP_ERR   (-1)
#define INPUT_ERR (-2)

namespace map {

class map {
 private:
    int x_size;
    int y_size;
    player::player main_player;
    std::vector<enemy::enemy> enemies;
    enemy::enemy current_enemy;
 public:
    explicit map(const std::string& filename);

    ~map() = default;

    void show_info();

    void make_action(const std::string& action);

    int get_player_health();
};

}  // namespace map
