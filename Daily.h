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
#ifndef DAILY
#define DAILY
#include "Display.h"

//! This class is used for daily display mode
class Daily : public Display {
public:
    Daily();
    //! show events in time range
    void show (const std::set<Event> & eventList) const override;
    //! next time range
    void next() override;
    //! previous time range
    void prev() override;

private:
    tm day;
};

#endif
