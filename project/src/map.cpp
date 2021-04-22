#include "map.h"

namespace map {
    map::map(const std::string& filename) {
        try {
            std::ifstream file(filename);
            file >> x_size >> y_size;
            std::string enemy_name;
            int x, y;
            while (file >> x >> y >> enemy_name) {
                enemy::enemy new_enemy(enemy_name, x, y);
                enemies.push_back(new_enemy);
            }
        }
        catch (const std::ifstream::failure& e) {
            std::cout << e.what() << std::endl;
            throw(std::ifstream::failure("error while opening or reading file"));
        }
    }

    void map::show_info() {
        bool enemy_found = false;
        if (current_enemy.get_health() != 0) {
            enemy_found = true;
            std::cout << "Supported actions:" << std::endl << "* kick enemy" << " > ";
        }
        if (!enemy_found) {
            for (const enemy::enemy &i : enemies) {
                if (i.get_x() == main_player.get_x() && i.get_y() == main_player.get_y() && i.get_health() != 0) {
                    enemy_found = true;
                    current_enemy = i;
                    std::cout << i.get_name() << " found, " << i.get_health() << " hp" << std::endl;
                    std::cout << "Supported actions:" << std::endl << "* kick enemy" << std::endl;
                    break;
                }
            }
        }
        if (!enemy_found) {
            std::cout << "Supported actions:" << std::endl;
            if (main_player.get_x() != 0) {
                std::cout << "* move left" << std::endl;
            }
            if (main_player.get_x() != x_size - 1) {
                std::cout << "* move right" << std::endl;
            }
            if (main_player.get_y() != 0) {
                std::cout << "* move down" << std::endl;
            }
            if (main_player.get_y() != y_size - 1) {
                std::cout << "* move up" << std::endl;
            }
        }
        std::cout << main_player.get_x() << " x " << main_player.get_y() << ", hp: " << main_player.get_health() << " > ";
    }

    void map::make_action(const std::string& action) {
        if (action == "move left") {
            main_player.move_x(-1);
        }
        if (action == "move right") {
            main_player.move_x(1);
        }
        if (action == "move down") {
            main_player.move_y(-1);
        }
        if (action == "move up") {
            main_player.move_y(1);
        }
        if (action == "kick enemy") {
            current_enemy.take_damage();
            if (current_enemy.get_health() != 0) {
                main_player.take_damage(current_enemy);
                std::cout << "enemy kicked. Enemy hp: " << current_enemy.get_health() << std::endl;
            } else {
                std::cout << "enemy killed" << std::endl;
                for (enemy::enemy& i : enemies) {
                    if (current_enemy.get_x() == i.get_x() && current_enemy.get_y() == i.get_y()) {
                        i.die();
                        break;
                    }
                }
            }
        }
    }

    int map::get_player_health() {
        return main_player.get_health();
    }
}
