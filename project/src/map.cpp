#include "map.h"

namespace map {
    map::map(const std::string& filename) {
        try {
            std::ifstream file(filename);
            file >> x_size >> y_size;
            std::string object_name;
            int x, y;
            while (file >> x >> y >> object_name) {
                if (all_enemies.find(object_name) != all_enemies.end()) {
                    enemy::enemy new_enemy(object_name, x, y);
                    enemies.push_back(new_enemy);
                }
                if (all_wearables.find(object_name) != all_wearables.end()) {
                    wearable::wearable wearable(object_name, x, y);
                    wearables.push_back(wearable);
                }
            }
        }
        catch(std::ifstream::failure&) {
            throw(std::ifstream::failure("input error"));
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

    bool map::search_for_wearables() {
        for (wearable::wearable &i : wearables) {
            if (i.get_x() == main_player.get_x() && i.get_y() == main_player.get_y() && i.get_armour_points() != 0) {
                current_wearable = i;
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

        bool wearable_found = search_for_wearables();
        if (wearable_found && !wearable_already_seen) {
            std::cout << std::endl << current_wearable.get_type() << " found" << std::endl;
            wearable_already_seen = true;
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
            if (wearable_found) {
                if (!(main_player.already_on_check(current_wearable))) {
                    std::cout << " * pick " << current_wearable.get_type() << std::endl;
                }
                main_player.throw_offer();
            }
            if (!actions_exist) {
                std::cout << std::endl;
            }
        }
        std::cout << main_player.get_x() << " x " << main_player.get_y() << ", hp: " << main_player.get_health() << ", armor: " << main_player.get_armour_points() << " > ";
    }

    void map::make_action(const std::string& action) {
        if (!search_for_enemy()) {
            if (action == "move left") {
                if (search_for_wearables()) {
                    delete_wearable(current_wearable);
                }
                main_player.move_x(-1);
                if (!search_for_enemy() && !search_for_wearables()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
                wearable_already_seen = false;
            }
            if (action == "move right") {
                if (search_for_wearables()) {
                    delete_wearable(current_wearable);
                }
                main_player.move_x(1);
                if (!search_for_enemy() && !search_for_wearables()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
                wearable_already_seen = false;
            }
            if (action == "move down") {
                if (search_for_wearables()) {
                    delete_wearable(current_wearable);
                }
                main_player.move_y(-1);
                if (!search_for_enemy() && !search_for_wearables()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
                wearable_already_seen = false;
            }
            if (action == "move up") {
                if (search_for_wearables()) {
                    delete_wearable(current_wearable);
                }
                main_player.move_y(1);
                if (!search_for_enemy() && !search_for_wearables()) {
                    std::cout << std::endl << "moved" << std::endl;
                }
                wearable_already_seen = false;
            }
            if (action == "pick " + current_wearable.get_type()) {
                main_player.put_on_wearable(current_wearable);
                delete_wearable(current_wearable);
                std::cout << std::endl << "clothes worn" << std::endl;
            }
            if (action.find("throw") != std::string::npos) {
                std::string throw_wearable = action.substr(6);
                std::cout << std::endl << "the " << throw_wearable << " is thrown out" << std::endl;
                main_player.throw_out_wearable(throw_wearable);
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

    void map::delete_wearable(wearable::wearable _wearable) {
        size_t wearables_size = wearables.size();
        for (size_t i = 0; i < wearables_size; ++i) {
            if (_wearable == wearables[i]) {
                wearables.erase(wearables.begin() + i);
                return;
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
