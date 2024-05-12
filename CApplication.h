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
#include <sstream>
#ifndef CAPP
#define CAPP
#include "Calendar.h"
#include "Daily.h"
#include "Weekly.h"
#include "Monthly.h"
#include "DisplayAll.h"
#include "UserDisplay.h"


/*! \mainpage Main Page
 * \section intro_sec Description
 *
 * With this calendar you can manipulate with some events. \n
 * First, you can add, delete, change them as you wish, \n
 * Every event has some attributes like name, place, date, people etc. \n
 * Every event also has its own ID (random generated) \n
 * You can change events by this ID, find them with some of their attributes \n
 * Also there is export and import functions. \n
 * You can export all events into file, for sure you can find some events and then export them. \n
 * There is also function of check days for availability to create new event. \n
 * Events could be one-time or repeatable. \n
 * And for sure display, which show you all events in some range! \n
 *
 */


//! This is the main class of calendar app. Work with inputs from user
class CApplication {
public:
	//! In this constructor happens all output
	void run();
    CApplication() = default;

private:
	//! Method for add function of the program. Adds the events in our database.
    void addEventFunc(Event & y, Calendar & x);
    //! Method for change events in database.
    void changeEventFunc (Calendar & x);
    //! Method for delete events in database.
    void deleteEventFunc (Calendar & x);
    //! Method for check date format when its input.
    tm inputDate(const int key = 0);
    //! This method checks our input for wrong symbols. For example: if program trying to write some string into int variable
    int checkInput(int someOtherVar=0);
    void displayEventFunc(const Calendar & x);
    bool importEventsFunc(Calendar & x, std::string readedLine);
    void calculateRepeatable(Calendar & x, const int frequency, const int timeRange, Event & y);
    std::set<Event> searchEventFunc(Calendar & x, const int key, const int keysCount, const int searchMode);
    //! This int program is using for make choises. Always set by user.
    int choose_int;
    //! Same as choose_int, some string for other variables, which always set by user.
    std::string input_str;

};

#endif
