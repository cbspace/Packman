#pragma once

//#include "playable_character.h"
#include "LibCB/Error.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <algorithm>
#include <utility>

using std::vector;
using std::optional;
using std::nullopt;
using std::string;
using std::ifstream;
using std::ios;
using std::getline;
using std::for_each;
using std::pair;

namespace Packman {

enum class MapPoint {
    WallFull,
    WallAbove,
    WallBelow,
    WallLeft,
    WallRight,
    CornerTopLeftInside,
    CornerTopRightInside,
    CornerBottomLeftInside,
    CornerBottomRightInside,
    CornerTopLeftOutside,
    CornerTopRightOutside,
    CornerBottomLeftOutside,
    CornerBottomRightOutside,
    Space,
    Fence,
    LeftOpening,
    RightOpening,
    NotValid
};

enum class MapObject {
    Dot,
    PowerPellet,
    Fruit,
    Nothing
};

class GameMap {

    public:
        GameMap();
        optional<Error> load_map_from_file(string const &path);
        int get_player_start_x();
        int get_player_start_y();
        int get_left_tunnel_location_x();
        int get_right_tunnel_location_x();

        vector<vector<MapPoint>> map_points;
        vector<vector<MapObject>> map_objects;
        int dots_remaining;

    private:
        pair<int, int> player_start;
        pair<int, int> left_tunnel_location;
        pair<int, int> right_tunnel_location;
};

}

using namespace Packman;