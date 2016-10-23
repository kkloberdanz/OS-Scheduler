#include <iostream>
#include <string>

bool is_num(std::string s) {
    if (s == "") {
        return false;
    }
    for (const char& c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

int as_int(std::string s) {
    return atoi(s.c_str());
}

