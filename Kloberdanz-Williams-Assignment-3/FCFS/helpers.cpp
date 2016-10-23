#include <iostream>
#include <string>

#include "helpers.hpp"

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

/*
 * Splits a std::string on delim, returns a std::vector
 */
std::vector<std::string> split(std::string s, char delim) {
    std::vector<std::string> return_v;
    std::string tmp_str = "";
    for (const char& c : s) {
        if (c == delim) {
            if (tmp_str != "" ) {
                return_v.push_back(tmp_str);
            }
            tmp_str = "";
        } else {
            tmp_str += c;
        }
    }
    return return_v;
}
