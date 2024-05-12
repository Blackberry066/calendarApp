#include "CApplication.h"
using namespace std;

bool CApplication::importEventsFunc(Calendar &x, std::string readedLine) {
    Event importedEvent;
    cout << readedLine << endl;
    std::istringstream iss(readedLine);
    std::string someString;
    int someInt;
    getline(iss, someString, ':');
    importedEvent.setName(someString);
    if (getline(iss, someString, ':'))
        importedEvent.setPlace(someString);
    else {
        cout << "Wrong file format!" << endl;
        return false;
    }
    if (getline(iss, someString, ':'))
        importedEvent.setTag(someString);
    else {
        cout << "Wrong file format!" << endl;
        return false;
    }
    if (getline(iss, someString, ':')) {
        std::istringstream peopleList(someString);
        while(getline(peopleList, someString, ','))
            importedEvent.addPerson(someString);
    }
    else {
        cout << "Wrong file format!" << endl;
        return false;
    }
    if (iss >> someInt)
        importedEvent.setDuration(someInt);
    else {
        cout << "Wrong file format" << endl;
        return false;
    }
    getline(iss, someString, ':');
    if (getline(iss, someString, ':')) {
        std::istringstream date(someString);
        time_t now_time = time(nullptr);
        tm eventDate_tmp = *localtime(&now_time);
        int iterationCounter = 1;
        while (date >> someInt) {
            if(iterationCounter == 1)
                eventDate_tmp.tm_year = someInt;
            else if (iterationCounter == 2)
                eventDate_tmp.tm_mon = someInt;
            else if (iterationCounter == 3)
                eventDate_tmp.tm_mday = someInt;
            else {
                cout << "Wrong file format!" << endl;
            }
            date.ignore(100,'-');
            iterationCounter++;
        }
        if (iterationCounter < 3) {
            cout << "Wrong time format!" << endl;
            return false;
        }
        if (!(x.checkDate(eventDate_tmp))) {
            importedEvent.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon,
                                  eventDate_tmp.tm_mday);
        }

    }
    else {
        cout << "Wrong file format!" << endl;
        return false;
    }
    if (getline(iss, someString, ':')) {
        importedEvent.setNote(someString);
    }
    else {
        cout << "Wrong file format!" << endl;
        return false;
    }
    if (getline(iss, someString, ':')) {
        cout << "Wrong file format!" << endl;
        return false;
    }

    importedEvent.setEventID(x.getMaxId());
    x.addEventId(importedEvent.getEventId(), importedEvent);
    x.addEvent(importedEvent);
    return true;
  

}
