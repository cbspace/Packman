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
        vector<MapPoint> current_row(map_width);
        getline(ifs, str);
        int i = 0;

        for_each(str.begin(), str.end(), [&current_row, &i] (char const &c) {
            switch (c) {
                case '*':
                    current_row[i++] = MapPoint::WallFull;
                    break;
                case 'A':
                    current_row[i++] = MapPoint::WallAbove;
                    break;
                case 'B':
                    current_row[i++] = MapPoint::WallBelow;
                    break;
                case 'L':
                    current_row[i++] = MapPoint::WallLeft;
                    break;
                case 'R':
                    current_row[i++] = MapPoint::WallRight;
                    break;
                case '1':
                    current_row[i++] = MapPoint::CornerTopLeftInside;
                    break;
                case '2':
                    current_row[i++] = MapPoint::CornerTopRightInside;
                    break;
                case '3':
                    current_row[i++] = MapPoint::CornerBottomRightInside;
                    break;
                case '4':
                    current_row[i++] = MapPoint::CornerBottomLeftInside;
                    break;
                case '5':
                    current_row[i++] = MapPoint::CornerTopLeftOutside;
                    break;
                case '6':
                    current_row[i++] = MapPoint::CornerTopRightOutside;
                    break;
                case '7':
                    current_row[i++] = MapPoint::CornerBottomRightOutside;
                    break;
                case '8':
                    current_row[i++] = MapPoint::CornerBottomLeftOutside;
                    break;
                case 'E':
                    current_row[i++] = MapPoint::Space;
                    break;
                case ' ':
                    current_row[i++] = MapPoint::Dot; //temp
                    break;
                case '[':
                    current_row[i++] = MapPoint::LeftOpening;
                    break;
                case ']':
                    current_row[i++] = MapPoint::RightOpening;
                    break;
                case 'P':
                    current_row[i++] = MapPoint::PowerPellet; //temp
                    break;
                case 'S':
                    current_row[i++] = MapPoint::PlayerStart;
                    break;
                default:
                    current_row[i++] = MapPoint::NotValid;
                    //cout << "Invalid character: '" << c << "' found in map file" << endl;
            } 
        });

        this->map_vec.push_back(current_row);
    }
    
    ifs.close();

    return nullopt;
}