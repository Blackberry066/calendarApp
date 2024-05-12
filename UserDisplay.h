#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <memory>
#include <ctime>
#include <fstream>

#ifndef usrDISP
#define usrDISP
#include "Display.h"

//! This class is used for user display mode
class UserDisplay : public Display {
public:
    UserDisplay();
    //! Constructor for create user display with some amount of days range
    UserDisplay(const int someAmountOfDays);
    void show(const std::set<Event> & eventList) const override;
    void next() override;
    void prev() override;
    void setTimeSpread(const int spread);
};




#endif
