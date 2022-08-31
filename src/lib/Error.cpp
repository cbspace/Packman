#include "Error.h"

Error::Error(const string &error_string) {
    error_text = error_string;
}

string Error::get_error_text() {
    return error_text;
}