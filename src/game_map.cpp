#include "game_map.h"

GameMap::GameMap() {}

optional<Error> GameMap::load_map_from_file(string const &path) {
    ifstream ifs;
    string str;

    ifs.open(path, ios::in);
    if (!ifs) { return Error("Could not open map file"); }

    getline(ifs,str);
    int map_width = (str.find_first_not_of("0123456789") == string::npos && !str.empty()) ? stoi(str) : 0;
    getline(ifs,str);
    int map_height = (str.find_first_not_of("0123456789") == string::npos && !str.empty()) ? stoi(str) : 0;
    if (!map_width || !map_height || !(map_width + map_height < 200)) { return Error("Invalid map size"); }

    while(!ifs.eof()) {
        vector<MapPoint> current_row_map_point(map_width);
        vector<MapObject> current_row_map_object(map_width);
        getline(ifs, str);
        int x = 0;
        int y = 0;

        for (const auto c : str) {
            switch (c) {
                case '*':
                    current_row_map_point[x] = MapPoint::WallFull;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'A':
                    current_row_map_point[x] = MapPoint::WallAbove;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'B':
                    current_row_map_point[x] = MapPoint::WallBelow;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'L':
                    current_row_map_point[x] = MapPoint::WallLeft;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'R':
                    current_row_map_point[x] = MapPoint::WallRight;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '1':
                    current_row_map_point[x] = MapPoint::CornerTopLeftInside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '2':
                    current_row_map_point[x] = MapPoint::CornerTopRightInside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '3':
                    current_row_map_point[x] = MapPoint::CornerBottomRightInside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '4':
                    current_row_map_point[x] = MapPoint::CornerBottomLeftInside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '5':
                    current_row_map_point[x] = MapPoint::CornerTopLeftOutside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '6':
                    current_row_map_point[x] = MapPoint::CornerTopRightOutside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '7':
                    current_row_map_point[x] = MapPoint::CornerBottomRightOutside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case '8':
                    current_row_map_point[x] = MapPoint::CornerBottomLeftOutside;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'E':
                    current_row_map_point[x] = MapPoint::Space;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case ' ':
                    current_row_map_point[x] = MapPoint::Space;
                    current_row_map_object[x] = MapObject::Dot;
                    break;
                case '[':
                    current_row_map_point[x] = MapPoint::LeftOpening;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case ']':
                    current_row_map_point[x] = MapPoint::RightOpening;
                    current_row_map_object[x] = MapObject::Nothing;
                    break;
                case 'P':
                    current_row_map_point[x] = MapPoint::Space;
                    current_row_map_object[x] = MapObject::PowerPellet;
                    break;
                case 'S':
                    current_row_map_point[x] = MapPoint::Space;
                    current_row_map_object[x] = MapObject::Nothing;
                    player_start = {x,y};
                    break;
                default:
                    current_row_map_point[x] = MapPoint::NotValid;
                    current_row_map_object[x] = MapObject::Nothing;
                    //cout << "Invalid character: '" << c << "' found in map file" << endl;
            }
            x++;
        }

        this->map_points.push_back(current_row_map_point);
        this->map_objects.push_back(current_row_map_object);
        y++;
    }
    
    ifs.close();

    return nullopt;
}