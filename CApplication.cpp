#include "CApplication.h"
using namespace std;

//! This is the main class of application, using is simple. Make user choose something!
void CApplication::run() {
    Calendar x;
    while (!std::cin.eof()) {
        cout << endl;
        cout << "Hello! You have: " << x.eventsCount() << " events." << endl;
        cout << "Menu: " << endl;
        cout << "1. Add event." << endl;
        cout << "2. Display events." << endl;
        cout << "3. Change event." << endl;
        cout << "4. Delete event." << endl;
        cout << "5. Find events with some attributes" << endl;
        cout << "6. Get event description." << endl;
        cout << "7. Check day for availability." << endl;
        cout << "8. Import/Export events" << endl;
        cout << "9. Exit." << endl;
        choose_int = checkInput();
        if (choose_int == -1)
            continue;
        if (choose_int == 1) { // if user wants to add new Event
            Event y;
            addEventFunc(y, x);
        }
        else if (choose_int == 2) {
            displayEventFunc(x);
        }
        else if (choose_int == 3) { // change event
            changeEventFunc(x);
        }
        else if (choose_int == 4) { // delete event
            deleteEventFunc(x);
        }
        else if (choose_int == 5) { // find event with attributes
            int keysCount = 1;
            int searchMode = 0;
            /*
             *  search mode = 0 - use AND search
             *  search mode = 1 - use OR search
             */
            std::set<Event> searchResult;
            while(true) {
                if (keysCount > 1) {
                    cout << "How do you want to search next attribute?" << endl;
                    cout << "1. And" << endl;
                    cout << "2. OR" << endl;
                    cout << "3. Finish search" << endl;
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (choose_int == 1)
                        searchMode = 0;
                    if (choose_int == 2)
                        searchMode = 1;
                    else if (choose_int == 3)
                        break;
                }
                cout << "Choose attribute to search. You can choose them several times." << endl;
                cout << "1. Name" << endl;
                cout << "2. Place" << endl;
                cout << "3. Tag" << endl;
                cout << "4. Person" << endl;
                cout << "5. Duration" << endl;
                cout << "6. Date" << endl;
                cout << "0. Finish search" << endl;
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
                if (choose_int == 1) { // by name
                    cout << "Write your event's name:" << endl;
                    cin.ignore(100, '\n');
                    getline(cin, input_str, '\n');
                    if (keysCount == 1) {
                        searchResult = x.findEvent(1, input_str);
                    }
                    else if (keysCount > 1 && searchMode == 1) {
                        std::set<Event> otherSearchResult = x.findEvent(1, input_str);
                        std::set_union (searchResult.begin(), searchResult.end(), otherSearchResult.begin(),
                                        otherSearchResult.end(), std::inserter(searchResult, searchResult.begin()));
                    }
                    else {
                        searchResult = x.findEvent(1, input_str, searchResult);
                    }
                }
                else if (choose_int == 2) { // by place
                    cout << "Write your event's place:" << endl;
                    searchResult = searchEventFunc(x, 2, keysCount, searchMode);
                }
                else if (choose_int == 3) { // by tag
                    cout << "Write your event's tag:" << endl;
                    searchResult = searchEventFunc(x, 3, keysCount, searchMode);
                }
                else if (choose_int == 4) { // by person
                    cout << "Write person for search" << endl;
                    searchResult = searchEventFunc(x, 4, keysCount, searchMode);
                }
                else if (choose_int == 5) { // by duration
                    cout << "Write your event's duration:" << endl;
                    cin.ignore(100, '\n');
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (keysCount == 1) {
                        searchResult = x.findEvent(5, choose_int);
                    }
                    else if (keysCount > 1 && searchMode == 1) {
                        std::set<Event> otherSearchResult = x.findEvent(5, choose_int);
                        std::set_union (searchResult.begin(), searchResult.end(), otherSearchResult.begin(),
                                        otherSearchResult.end(), std::inserter(searchResult, searchResult.begin()));
                    }
                    else {
                        searchResult = x.findEvent(5, choose_int, searchResult);
                    }
                }
                else if (choose_int == 6) { // by date
                    tm eventDate_tmp = inputDate();
                    tm check = {};
                    if (eventDate_tmp == check)
                        continue;
                    cout << "Date: " << eventDate_tmp << endl;
                    if (keysCount == 1) {
                        searchResult = x.findEvent(6, eventDate_tmp);
                    }
                    else if (keysCount > 1 && searchMode == 1) {
                        std::set<Event> otherSearchResult = x.findEvent(6, eventDate_tmp);
                        std::set_union (searchResult.begin(), searchResult.end(), otherSearchResult.begin(),
                                        otherSearchResult.end(), std::inserter(searchResult, searchResult.begin()));
                    }
                    else {
                        searchResult = x.findEvent(6, eventDate_tmp, searchResult);
                    }
                }
                else if (choose_int == 0)
                    break;
                keysCount++;
            }
            if (!searchResult.empty()) {
                cout << "Your events: " << endl;
                for (const auto & ptr : searchResult) {
                    cout << "Event with ID " << ptr.getEventId() << "." << endl;
                    ptr.printDescription();
                }
                cout << "Do you want to export these events?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
                while(true)
                    if (choose_int == 1) {
                        std::ofstream file("Export.txt");
                        if (file.is_open()) {
                            x.exportEvents(file, searchResult);
                            file.close();
                        }
                        else
                            cout << "Can't open file. Error." << endl;
                        break;
                    }
                    else if (choose_int == 2)
                        break;
                    else {
                        cout << "Wrong choose!7" << endl;
                        continue;
                    }
            }
            else {
                cout << "Can't find any event with these attributes!" << endl;
            }
        }
        else if (choose_int == 6) { // get description
            cout << "Write event id from list below to get it description: " << endl;
            x.printEventIDs();
            cin.ignore(100, '\n');
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            Event result = x.getEventByID(choose_int);
            if (!(result.getName().empty()))
                result.printDescription();
            else
                cout << "Wrong event ID!" << endl;

        }
        else if (choose_int == 7) { // check day for events
            tm eventDate_tmp = inputDate();
            tm check = {};
            if (eventDate_tmp == check)
                continue;
            x.checkDayAvailable(eventDate_tmp);
        }
        else if (choose_int == 8) {
            cout << "What do you want to do?" << endl;
            cout << "1. Import events" << endl;
            cout << "2. Export events" << endl;
            cout << "3. Return to menu" << endl;
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            if (choose_int == 1) {
                cout << "Write your file name with file type." << endl;
                cout << "For import data should be in format "
                        "Name:Place:Tag:Person1,Person2...:Duration:Date(YYYY-mm-dd):Note" << endl;
                std::string readedLine;
                cin.ignore(100, '\n');
                getline(cin, input_str, '\n');
                std::ifstream file(input_str);
                if (file.is_open()) {
                    while (std::getline(file,readedLine)) {
                        if (!(importEventsFunc(x, readedLine)))
                            continue;
                    }
                    file.close();
                }
                else {
                    cout << "Can't open file!" << endl;
                    continue;
                }
            }
            else if (choose_int == 2) {
                std::ofstream file("Export.txt");
                if (file.is_open()) {
                    x.exportEvents(file);
                    file.close();
                }
                else
                    cout << "Can't open file. Error." << endl;
                continue;
            }
            else if (choose_int == 3)
                continue;
            else {
                cout << "Wrong choose!5" << endl;
                continue;
            }

        }
        else if (choose_int == 9)
            break;
        else
            cout << "Wrong choose!6" << endl;
    }
}



