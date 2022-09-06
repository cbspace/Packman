#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "playable_character.h"
#include "lib/Error.h"
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


        vector<vector<MapPoint>> map_points;
        vector<vector<MapObject>> map_objects;
        
    private:
        pair<int, int> player_start;

};

}

using namespace Packman;

#endif // GAME_MAP_H