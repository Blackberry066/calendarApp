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

#ifndef ALL
#define ALL
#include "Display.h"


//! This is simple class, used to show all events in database
class DisplayAll{
public:
	//! Method to show events
    void printEvents(const std::set<Event> &eventList) const;
};

#endif
