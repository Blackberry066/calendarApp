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

#ifndef WEEKLY
#define WEEKLY
#include "Display.h"


//! Class to display events weekly
class Weekly : public Display {
public:
	//! Set starting time for display
    Weekly();
    //! Shows events in time range
    void show (const std::set<Event> & eventList) const override;
    //! Get next time range
    void next () override;
    //! Get previous time range
    void prev () override;
};

#endif
