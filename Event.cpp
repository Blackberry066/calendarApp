#include "Event.h"
using namespace std;

Event::Event() {
    now_time = time(nullptr);
    eventDate = *localtime(&now_time);
    eventDate.tm_year += 1900;
    eventDate.tm_mon +=1;
}

void Event::setName (const std::string & name) {
    if (!name.empty()) {
        if (name != eventName)
            eventName = name;
        else
            cout << "Same name of event!" << endl;
    }

    else
        cout << "Wrong event name!" << endl;
}

void Event::setPlace (const std::string & place) {
    if (!place.empty()) {
        if (place != eventName)
            eventPlace = place;
        else
            cout << "Same place of event!" << endl;
    }

    else
        cout << "Wrong place!" << endl;
}

void Event::setTag (const std::string & tag) {
    if (!tag.empty()) {
        if (tag != eventName)
            eventTag = tag;
        else
            cout << "Same tag of event!" << endl;
    }

    else
        cout << "Wrong tag!" << endl;
}

void Event::setDuration(const int & duration) {
    if (duration > 0 && duration <= 1440) { // not greater than minutes in one day
        eventDuration = duration;
    }
    else
        cout << "Wrong duration!" << endl;
}

void Event::setDate (const int year, const int month, const int day) {
    eventDate.tm_year = year;
    eventDate.tm_mon = month;
    eventDate.tm_mday = day;
}

void Event::setNote(const std::string & someNote) {
    eventNote = someNote;
}

void Event::setDate (const int year, const int month, const int day, const int hour, const int minutes) {
    eventDate.tm_year = year;
    eventDate.tm_mon = month;
    eventDate.tm_mday = day;
    eventDate.tm_hour = hour;
    eventDate.tm_min = minutes;
}

bool Event::operator == (const Event & other) const {
    if (this->eventDate == other.eventDate && this->eventName == other.eventName
        && this->eventDuration == other.eventDuration && this->eventTag == other.eventTag
        && this-> eventPlace == other.eventPlace)
        return true;
    else
        return false;
}

bool Event::operator < (const Event & other) const {
    return std::tie(this->eventName, this->eventPlace, this->eventTag, this->eventDuration, this->eventDate)
           < std::tie (other.eventName, other.eventPlace, other.eventTag, other.eventDuration, other.eventDate);
}

std::string Event::getName() const {
    return eventName;
}

std::string Event::getPlace() const {
    return eventPlace;
}

std::string Event::getNote() const {
    return eventNote;
}

std::string Event::getTag() const {
    return eventTag;
}

int Event::getDuration() const {
    return eventDuration;
}

tm Event::getDate() const {
    return eventDate;
}

void Event::printDescription () const {
    cout << "Description of event:" << endl;
    cout << "---------------------" << endl;
    cout << "Name of event: " << eventName << endl;
    if (peopleList.empty()) {
        cout << "You dont have any added person for this event!" << endl;
    }
    else {
        cout << "Number of people: " << peopleList.size() << endl;
        cout << "They are: " << endl;
        int counter = 1;
        for (const auto & uk : peopleList) {
            cout << counter << ". " << uk << endl;
            counter++;
        }
    }
    if (eventPlace.empty())
        cout << "Your event place isn't assigned!" << endl;
    else
        cout << "Place of event: " << eventPlace << endl;
    if (eventTag.empty())
        cout << "Your tag for this event is empty!" << endl;
    else
        cout << "Event tag: " << eventTag << endl;
    if (this->printTime)
        cout << "Event date: " << eventDate << " " <<  eventDate.tm_hour << ":" << eventDate.tm_min << endl;
    else
        cout << "Event date: " << eventDate << endl;
    if (eventDuration == 0)
        cout << "Your event duration isn't assigned!" << endl;
    else
        cout << "Event duration: " << eventDuration << " minutes" << endl;
    if (eventNote.empty())
        cout << "You dont have any note for this event!" << endl;
    else
        cout << "Your note for this event: " << eventNote << endl;
    cout << "---------------------" << endl;
}

void Event::setEventID(const int eventID) {
    event_id = eventID;
}

void Event::setTimePrint(const int & key) {
    if (key == 1)
        printTime = true;
    else if (key == 2)
        printTime = false;
    else
        cout << "Wrong key!" << endl;
}

bool Event::getTimePrint() const {
    return printTime;
}

int Event::getEventId() const {
    return event_id;
}

void Event::setRepeated() {
    isRepeated = true;
}

void Event::unsetRepeated() {
    isRepeated = false;
}

bool Event::checkRepeated() const {
    return isRepeated;
}
