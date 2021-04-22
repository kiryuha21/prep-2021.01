#include "map.h"

int main(int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "--map") != 0) {
        return INPUT_ERR;
    }

    try {
        map::map my_map("map_ex.txt");
        my_map.show_info();
        std::string action;
        while (my_map.get_player_health() > 0 && getline(std::cin, action)) {
            my_map.make_action(action);
            my_map.show_info();
        }
    }
    catch(std::istream::failure& e) {
        std::cout << e.what() << std::endl;
        return MAP_ERR;
    }
    return 0;
}
