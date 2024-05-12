#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include "tm_operators.h"
using namespace std;


bool operator == (const tm & x, const tm & y) {
    return x.tm_year == y.tm_year && x.tm_mon == y.tm_mon && x.tm_mday == y.tm_mday
           && x.tm_hour == y.tm_hour && x.tm_min == y.tm_min;
}
bool operator < (const tm & x, const tm & y) {
    return std::tie (x.tm_year, x.tm_mon, x.tm_mday, x.tm_hour, x.tm_min)
           < std::tie (y.tm_year, y.tm_mon, y.tm_mday, y.tm_hour, y.tm_min);
}
ostream & operator << (ostream & os, const tm & x) {
    os << x.tm_year << "-" << x.tm_mon << "-" << x.tm_mday;
    return os;
}

bool operator >= (const tm & x, const tm & y) {
    if (x.tm_year == y.tm_year) {
        if (x.tm_mon == y.tm_mon) {
            if (x.tm_mday >= y.tm_mday)
                return true;
            else
                return false;
        }
        else if (x.tm_mon < y.tm_mon)
            return false;
        else
            return true;
    }
    else if (x.tm_year < y.tm_year)
        return false;
    else
        return true;
}
bool operator <= (const tm & x, const tm & y) {
    if (x.tm_year == y.tm_year) {
        if (x.tm_mon == y.tm_mon) {
            if (x.tm_mday <= y.tm_mday)
                return true;
            else
                return false;
        }
        else if (x.tm_mon < y.tm_mon)
            return true;
        else
            return false;
    }
    else if (x.tm_year < y.tm_year)
        return true;
    else
        return false;

}



