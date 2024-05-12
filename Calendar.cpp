#include "Calendar.h"
using namespace std;

Calendar::Calendar() {
	maxEventID = 0;
}

int Calendar::getMaxId () {
	maxEventID++;
	return maxEventID;
}

std::set<Event> Calendar::findEvent (const int key, const std::string & someString,
                                     const std::set<Event> & eventsForSearch) const {
    std::set<Event> result;
    if (eventsForSearch.empty()) {
        for (const auto &ptr : eventList) {
            if ((key == 1 && ptr.getName() == someString) || // search by name
                (key == 2 && ptr.getPlace() == someString) || // search by place
                (key == 3 && ptr.getTag() == someString)) { //  search by tag
                result.insert(ptr);
            }
            else if (key == 4) {
                std::set<std::string> resultPeople = ptr.getPeople();
                if (resultPeople.find(someString) !=  resultPeople.end())
                    result.insert(ptr);
            }
        }
    }
    else {
        for (const auto &ptr : eventsForSearch) {
            if ((key == 1 && ptr.getName() == someString) || // search by name
                (key == 2 && ptr.getPlace() == someString) || // search by place
                (key == 3 && ptr.getTag() == someString)) { //  search by tag
                result.insert(ptr);
            }
            else if (key == 4) { // search by person
                std::set<std::string> resultPeople = ptr.getPeople();
                if (resultPeople.find(someString) !=  resultPeople.end())
                    result.insert(ptr);
            }
        }
    }
    return result;
}

std::set<Event> Calendar::findEvent (const int key, const int someInt, const std::set<Event> & eventsForSearch) const {
    std::set<Event> result;
    if (eventsForSearch.empty()) {
        for (const auto &ptr : eventList) {
            if (key == 5 && ptr.getDuration() == someInt) // search by duration
                result.insert(ptr);
        }
    }
    else {
        for (const auto &ptr : eventsForSearch) {
            if (key == 5 && ptr.getDuration() == someInt) // search by duration
                result.insert(ptr);
        }
    }
    return result;
}

std::set<Event> Calendar::findEvent (const int key, const tm someDate, const std::set<Event> & eventsForSearch) const {
    std::set<Event> result;
    if (eventsForSearch.empty()) {
        for (const auto &ptr : eventList) {
            if (ptr.getDate().tm_year == someDate.tm_year
                && ptr.getDate().tm_mon == someDate.tm_mon
                && ptr.getDate().tm_mday == someDate.tm_mday ) {
                result.insert(ptr);
            }
        }
    }
    else {
        for (const auto &ptr : eventsForSearch) {
            if (ptr.getDate().tm_year == someDate.tm_year
                && ptr.getDate().tm_mon == someDate.tm_mon
                && ptr.getDate().tm_mday == someDate.tm_mday ) {
                result.insert(ptr);
            }
        }
    }
    return result;
}

bool Calendar::addEventId (const int eventID, const Event & someEvent) {
    if (eventIdMap.find(eventID) == eventIdMap.end()) {
        eventIdMap[eventID] = someEvent;
        return true;
    }
    else {
        cout << "This id already added!" << endl;
        return false;
    }
}

bool Calendar::removeEventByID (const int eventID) {
    auto ptr = eventIdMap.find(eventID);
    if (ptr != eventIdMap.end()) {
        eventIdMap.erase(ptr);
        return true;
    }
    else {
        cout << "Invalid event ID" << endl;
        return false;
    }
}

void Calendar::checkDayAvailable (const tm & someDate) const {
    int result = 0;
    for (const auto & event : eventList) {
        tm ptrEventDate = event.getDate();
        /*
         * result = 0 - day is free
         * result = 1 - day has some repeatable event, but free for one-time event
         * result = 2 - day has other one-time event or both one-time and repeatable event
         * user can get description of the event by date and check it
         */
        if (ptrEventDate.tm_year == someDate.tm_year &&
            ptrEventDate.tm_mon == someDate.tm_mon &&
            ptrEventDate.tm_mday == someDate.tm_mday) {
            if (event.checkRepeated()) { // if repeatable event
                result = 1;
            }
            else {
                result = 2;
                break;
            }
        }
    }
    if (result == 0)
        cout << "Day is free!" << endl;
    else if (result == 1)
        cout << "Day has some repeatable events" << endl;
    else if (result == 2)
        cout << "Day is not available!" << endl;

}

Event Calendar::getEventByID (const int eventID) const {
    auto uk = eventIdMap.find(eventID);
    if (uk != eventIdMap.end()) {
        return uk->second;
    }
    else {
        Event wrong;
        return wrong;
    }
}

size_t Calendar::printEventIDs (const int key) const {
    size_t oneTimeEventsCount = 0;
    for (const auto & uk : eventList) {
        if (!(uk.checkRepeated()) || key == 0) {
            if (!uk.getTimePrint())
                cout << uk.getEventId() << " : " << uk.getName() << " " << uk.getDate() << endl;
            else {
            	if (uk.getDate().tm_min < 10) 
            		cout << uk.getEventId() << " : " << uk.getName() << " " << uk.getDate()<< " "<<
                     uk.getDate().tm_hour << ":0" << uk.getDate().tm_min << endl;
            	else
            		cout << uk.getEventId() << " : " << uk.getName() << " " << uk.getDate()<< " "<<
                     uk.getDate().tm_hour << ":" << uk.getDate().tm_min << endl;
            }
            oneTimeEventsCount++;
        }
    }
    return oneTimeEventsCount;
}

int Calendar::eventsCount () const {
    return eventList.size();
}

bool Calendar::checkDate(const tm someDate) const {
    auto uk = find_if(eventList.begin(), eventList.end(),
                      [someDate](const Event &event) {return event.getDate().tm_year == someDate.tm_year
                                                             && event.getDate().tm_mon == someDate.tm_mon && event.getDate().tm_mday == someDate.tm_mday;});
    if (uk == eventList.end())
        return false;
    else
        return true;
}

bool Calendar::checkDateTime (const tm someDateTime) const {
    auto uk = find_if(eventList.begin(), eventList.end(),
                      [someDateTime](const Event &event) {return event.getDate().tm_year == someDateTime.tm_year
                                                                 && event.getDate().tm_mon == someDateTime.tm_mon && event.getDate().tm_mday == someDateTime.tm_mday
                                                                 && event.getDate().tm_hour == someDateTime.tm_hour && event.getDate().tm_min==someDateTime.tm_min;});
    if (uk == eventList.end())
        return false;
    else
        return true;
}

void Calendar::removeEvent (const Event & someEvent) {
    auto uk = eventList.find(someEvent);
    if (uk != eventList.end()) {
        eventList.erase(uk);
    }
    else {
        cout << "Can't find event!" << endl;
    }
}

void Calendar::addEvent(const Event & someEvent) {
    auto uk = eventList.find(someEvent);
    if (uk == eventList.end()) {
        eventList.insert(someEvent);
    }
    else
        cout << "Event already added!" << endl;
}

void Calendar::clearEventList () {
    repeatableEventList.clear();
    eventList.clear();
    eventIdMap.clear();
}

void Calendar::exportEvents (std::ofstream & file, const std::set<Event> & listForExport) {
    if (listForExport.empty()) {
        file << "Events count: " << eventList.size() << endl;
        file << "=========================" << endl;
        for (const auto & ptr : eventList) {
            file << "Name: " << ptr.getName() << endl;
            file << "Place: " << ptr.getPlace() << endl;
            file << "Tag: " << ptr.getTag() << endl;
            file << "People: {" << endl;
            for (const auto & it : ptr.getPeople()) {
                file << it << endl;
            }
            file << "}" << endl;
            file << "Duration: " << ptr.getDuration() << endl;
            
            if (ptr.getTimePrint())
                file << "Date: " << ptr.getDate() << ptr.getDate().tm_hour << ptr.getDate().tm_min << endl;
            else
                file << "Date: " << ptr.getDate() << endl;
            file << "Note: " << ptr.getNote() << endl;
            file << "---------------------------" << endl;
        }
    }
    else {
        file << "Events count: " << listForExport.size() << endl;
        file << "=========================" << endl;
        for (const auto & ptr : listForExport) {
            file << "Name: " << ptr.getName() << endl;
            file << "Place: " << ptr.getPlace() << endl;
            file << "Tag: " << ptr.getTag() << endl;
            file << "People: {" << endl;
            for (const auto & it : ptr.getPeople()) {
                file << it << endl;
            }
            file << "}" << endl;
            file << "Duration: " << ptr.getDuration() << endl;
            if (ptr.getTimePrint())
                file << "Date: " << ptr.getDate() << ptr.getDate().tm_hour << ptr.getDate().tm_min << endl;
            else
                file << "Date: " << ptr.getDate() << endl;
            file << "Note: " << ptr.getNote() << endl;
            file << "---------------------------" << endl;
        }
    }
}

std::set<Event> Calendar::getEventList() const {
    return eventList;
}

