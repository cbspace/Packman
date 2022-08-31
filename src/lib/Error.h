#ifndef ERROR_H
#define ERROR_H

#include <string>

using namespace std;

namespace Packman {

class Error {
    public:
        Error(const string &error_string = "Undefined Error");
        string get_error_text();
    private:
        string error_text;
};

}

using namespace Packman;

#endif // ERROR_H