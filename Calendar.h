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
#ifndef CAL
#define CAL

#include "Display.h"

//! This class is using for all actions with events: Add, print, check...
class Calendar {
public:
	Calendar();
	//! Method to get max added id of events
	int getMaxId();
	//! Method for find event by string, which used for looking by name, place etc.
    std::set<Event> findEvent (const int key, const std::string & someString,
                               const std::set<Event> & eventsForSearch = {}) const;
   	//! Same as previous method, but used for look by int-formatted attributes
    std::set<Event> findEvent (const int key, const int someInt, const std::set<Event> & eventsForSearch = {}) const;
    //! This method adds repeatable events in separate database, we need this database to fast deletion of repeatable events
    void addRepeatableEvent (const Event & someRepeatableEvent);
   	//! Here we print repeatable events in special format
    void printRepeatable() const;
    //! Same as two previous findEvent methods, but used for looking by date
    std::set<Event> findEvent (const int key, const tm someDate, const std::set<Event> & eventsForSearch = {}) const;
    //! This method save our eventID in separate map. Its necessary for fast events deletion
    bool addEventId (const int eventID, const Event & someEvent);
    //! This is method for delete IDs, we added before
    bool removeEventByID (const int eventID);
    //! This method checks if day available for new event or not
    void checkDayAvailable (const tm & someDate) const;
    //! Here we can search for some event by its ID
    Event getEventByID (const int eventID) const;
    //! Method for printEvent IDs, it has key for different situations
    size_t printEventIDs (const int key=0) const;
    //! Method to get amount of events in our database
    int eventsCount () const;
    //! Method to check if date is available to use
    bool checkDate(const tm someDate) const;
    //! Same method as checkDate, but also check time
    bool checkDateTime (const tm someDateTime) const;
    //! One of main methods, delete event from our database
    void removeEvent (const Event & someEvent);
    //! Special method to remove some repeatable event
    void removeRepeatable(const Event & someRepeatableEvent, const int key = 0);
    //! This method is used to add event in database
    void addEvent(const Event & someEvent);
    //! This method clear our database
    void clearEventList ();
    //! Method for export event database in file
    void exportEvents (std::ofstream & file, const std::set<Event> & listForExport = {});
    //! Method to get database and work with it later
    std::set<Event> getEventList() const;
    //! Same as previous method, but with repeatable database
    std::set<Event> getRepeatableEventList() const;

private:
	//! Our main database of events
    std::set<Event> eventList;
    //! Repeatable events database
    std::set<Event> repeatableEventList;
    //! Database of eventIDs
    std::map<int, Event> eventIdMap;
    //! Variable for save last added event ID
    int maxEventID;
};

#endif
