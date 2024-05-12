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
#ifndef EVENT
#define EVENT
#include "tm_operators.h"

//! This is main class for our event objects
class Event {
public:
	//! Set starting date for our program
    Event();
    //! Set name of event
    void setName (const std::string & name);
    //! Set place of event
    void setPlace (const std::string & place);
    //! Set tag of event
    void setTag (const std::string & tag);
    //! Set duration of event
    void setDuration(const int & duration);
    //! Set date of event (without minutes)
    void setDate (const int year, const int month, const int day);
    //! Set not for event
    void setNote(const std::string & someNote);
    //! Set new people list (which was before that processed and corrected)
    void setPeopleList(const std::set<std::string> & newPeopleList);
    //! Set name of event (with minutes)
    void setDate (const int year, const int month, const int day, const int hour, const int minutes);
    //! Adds person in our people database
    void addPerson (const std::string & person);
    //! Operator to check if 2 events are equal
    bool operator == (const Event & other) const;
    //! Operator to sort events in set container
    bool operator < (const Event & other) const;
    //! Get name of event
    std::string getName() const;
    //! Get place of event
    std::string getPlace() const;
    //! Get event note
    std::string getNote() const;
    //! Get event tag
    std::string getTag() const;
    //! Get event duration
    int getDuration() const;
    //! Get event date
    tm getDate() const;
    //! Print event description by user request
    void printDescription () const;
    //! Print list of event participants
    void printPeople() const;
    //! Returns people list
    std::set<std::string> getPeople() const;
    //! Clears people database
    void clearPeopleList();
    //! Set new event ID. Without argument sets random ID, if has argument - set sended id
    void setEventID(const int eventID);
    //! Set flag for event if its necessary for it to print time with date
    void setTimePrint(const int & key);
    //! Returns flag about need to print time
    bool getTimePrint() const;
    //! Returns event ID
    int getEventId() const;
    //! Set event flag for repeat. Now this is repeatable event.
    void setRepeated();
    //! Unset event flag for repeat.
    void unsetRepeated();
    //! Check repeat flag of the event.
    bool checkRepeated() const;
private:
	//! Our people list
    std::set<std::string> peopleList;
    //! Our event's name
    std::string eventName;
    //! Our event's place
    std::string eventPlace;
    //! Event's duration
    int eventDuration=0;
    //! Event's tag
    std::string eventTag;
    //! Variable to get time
    time_t now_time;
    //! Date of the event
    tm eventDate;
    //! Print time flag
    bool printTime = false;
    //! Repeatable event flag
    bool isRepeated = false;
    //! Event's id
    int event_id;
    //! Event's note
    std::string eventNote;
};

#endif

