#include "map.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        return INPUT_ERR;
    }

    int map_arg_number = 0;
    for (int i = 0; i < argc; ++i) {
        if (strstr(argv[i], ".map") != nullptr) {
            map_arg_number = i;
        }
    }

    bool with_armor = argc == 4;

    try {
        map::map my_map(argv[map_arg_number], with_armor);
        std::string action;
        while (my_map.get_player_health() > 0) {
            my_map.show_info();
            if (getline(std::cin, action)) {
                my_map.make_action(action);
            } else {
                break;
            }
        }
    }
    catch(std::istream::failure& e) {
        std::cout << e.what() << std::endl;
        return MAP_ERR;
    }
    return 0;
}
