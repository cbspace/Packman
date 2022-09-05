#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "character.h"
#include "lib/Error.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <algorithm>

using std::vector;
using std::optional;
using std::nullopt;
using std::string;
using std::ifstream;
using std::ios;
using std::getline;
using std::for_each;

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
    Dot,
    PowerPellet,
    PlayerStart,
    NotValid
};

class GameMap {

    public:
        GameMap();

        optional<Error> load_map_from_file(string const &path);

        vector<vector<MapPoint>> map_vec;
        
    private:
        

};

}

using namespace Packman;

#endif // GAME_MAP_H