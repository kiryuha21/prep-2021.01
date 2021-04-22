#include "map.h"

namespace map {
    map::map(const std::string& filename) {
        std::ifstream file(filename);
        if (!(file >> x_size >> y_size).good()) {
            throw std::istream::failure("file reading problem");
        }
        std::string enemy_name;
        int x, y;
        while (file >> x >> y >> enemy_name) {
            enemy::enemy new_enemy(enemy_name, x, y);
            enemies.push_back(new_enemy);
        }
    }

    bool map::search_for_enemy() {
        for (enemy::enemy &i : enemies) {
            if (i.get_x() == main_player.get_x() && i.get_y() == main_player.get_y() && i.get_health() != 0) {
                current_enemy = i;
                return true;
            }
        }
        return false;
    }

    void map::show_info() {
        bool enemy_found = search_for_enemy();
        if (enemy_found && !current_enemy.is_injured()) {
            std::cout << std::endl << current_enemy.get_name() << " found, " << current_enemy.get_health() << " hp" << std::endl;
            std::cout << "Supported actions:" << std::endl << " * kick enemy" << std::endl;
        }
        if (current_enemy.get_health() > 0 && current_enemy.is_injured()) {
            enemy_found = true;
            std::cout << "Supported actions:" << std::endl << " * kick enemy" << std::endl;
        }
        if (!enemy_found) {
            bool actions_exist = false;
            std::cout << "Supported actions:" << std::endl;
            if (main_player.get_x() > 0) {
                std::cout << " * move left" << std::endl;
                actions_exist = true;
            }
            if (main_player.get_x() < x_size - 1) {
                std::cout << " * move right" << std::endl;
                actions_exist = true;
            }
            if (main_player.get_y() > 0) {
                std::cout << " * move down" << std::endl;
                actions_exist = true;
            }
            if (main_player.get_y() < y_size - 1) {
                std::cout << " * move up" << std::endl;
                actions_exist = true;
            }
            if (!actions_exist) {
                std::cout << std::endl;
            }
        }
        std::cout << main_player.get_x() << " x " << main_player.get_y() << ", hp: " << main_player.get_health() << " > ";
    }

    void map::make_action(const std::string& action) {
        if (!search_for_enemy()) {
            if (action == "move left") {
                main_player.move_x(-1);
                if (!search_for_enemy()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
            }
            if (action == "move right") {
                main_player.move_x(1);
                if (!search_for_enemy()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
            }
            if (action == "move down") {
                main_player.move_y(-1);
                if (!search_for_enemy()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
            }
            if (action == "move up") {
                main_player.move_y(1);
                if (!search_for_enemy()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
            }
        }
        if (action == "kick enemy") {
            take_double_damage();
            if (current_enemy.get_health() > 0) {
                main_player.take_damage(current_enemy);
                if (main_player.get_health() > 0) {
                    std::cout << std::endl << "enemy kicked. Enemy hp: " << current_enemy.get_health() << std::endl;
                } else {
                    std::cout << std::endl << "player died" << std::endl;
                }
            } else {
                std::cout << std::endl << "enemy killed" << std::endl;
                for (enemy::enemy& i : enemies) {
                    if (current_enemy.get_x() == i.get_x() && current_enemy.get_y() == i.get_y()) {
                        i.die();
                        break;
                    }
                }
            }
        }
    }

    void map::take_double_damage() {
        for (enemy::enemy &i : enemies) {
            if (i.get_x() == current_enemy.get_x() && i.get_y() == current_enemy.get_y()) {
                i.take_damage();
                current_enemy.take_damage();
                return;
            }
        }
    }

    int map::get_player_health() {
        return main_player.get_health();
    }
}  // namespace map
