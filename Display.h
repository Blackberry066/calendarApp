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

#ifndef DISP
#define DISP
#include "Event.h"

using namespace std;
//! This is an abstract class for other display modes
class Display {
public:
	virtual ~Display() = default;
	//! Method for display events in time range
    virtual void show(const std::set<Event> & eventList) const = 0;
    //! Method to get next time range
    virtual void next() = 0;
    //! Method to get previous time range
    virtual void prev() = 0;
    //! Method to get max and min display time
    void setMinMax(const int someDaysCount, const int direction=0);
    
protected:
    //! Variable, which controls time range
    time_t displayTime = time(nullptr);
    //! Maximum time of time range
    tm maxTime;
    //! Minimum time of time range
    tm minTime;
    //! Variable for additions and subtractions
    const int secondsPerDay = 24 * 60 * 60;
    //! This flag checks if next function was used before working function
    bool wasNext = false;
    //! This flag checks if prev function was used before working function
    bool wasPrev = false;
    //! Variable to control day count for next range
    int dayCount;
};
#endif
