#include "CApplication.h"
using namespace std;

void CApplication::changeEventFunc (Calendar & x) {
    while (!std::cin.eof()) {
        if (x.eventsCount() == 0) {
            cout << "You don't have any events for change!" << endl;
            break;
        }
        cout << "Which event ID of the event you want to config:" << endl;
        x.printEventIDs();
        cin.ignore(100, '\n');
        choose_int = checkInput();
        if (choose_int == -1)
            break;
        Event original = x.getEventByID(choose_int);
        Event result = original;
        if (result.getName().empty()) {
            cout << "Wrong event ID!" << endl;
            break;
        }
        else {
            while (!std::cin.eof()) {
                cout << "Which attribute you want to change?" << endl;
                cout << "1. Name" << endl;
                cout << "2. Place" << endl;
                cout << "3. Tag" << endl;
                cout << "4. Add/delete person" << endl;
                cout << "5. Duration" << endl;
                cout << "6. Date" << endl;
                cout << "7. Abort changes" << endl;
                cout << "8. Save and return to menu" << endl;
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
                if (choose_int == 1) { // Set name
                    cout << "Write new name of this event:" << endl;
                    cin.ignore(100, '\n');
                    getline(cin, input_str, '\n');
                    result.setName(input_str);
                }
                else if (choose_int == 2) { // Set place
                    cout << "Write new place of this event:" << endl;
                    cin.ignore(100, '\n');
                    getline(cin, input_str, '\n');
                    result.setPlace(input_str);
                }
                else if (choose_int == 3) { // Set Tag
                    cout << "Write new tag of this event:" << endl;
                    cin.ignore(100, '\n');
                    getline(cin, input_str, '\n');
                    result.setTag(input_str);
                }
                else if (choose_int == 4) { // Add/Delete person
                    cout << "What do you want to do?" << endl;
                    cout << "1. Add person to event" << endl;
                    cout << "2. Delete person from event" << endl;
                    cout << "3. Clear people list" << endl;
                    cout << "4. Return to previous menu" << endl;
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (choose_int == 1) {
                        cout << "Write names of people you want to add. Write 1 to save and return"
                                " or write 0 to abort changes and return in menu" << endl;
                        std::set<std::string> tmpPeopleList = result.getPeople();
                        cin.ignore(100, '\n');
                        while (!std::cin.eof()) {
                            getline(cin, input_str, '\n');
                            if (input_str == "1") {
                                result.setPeopleList(tmpPeopleList);
                                break;
                            } else if (input_str == "0")
                                break;
                            else
                                tmpPeopleList.insert(input_str);
                        }
                    }
                    else if (choose_int == 2) {
                        std::set<std::string> tmpPeopleList = result.getPeople();
                        if (tmpPeopleList.empty()) {
                            cout << "You dont have any added person for this event!" << endl;
                            break;
                        }
                        cout << "Choose a person you want to remove (Write 0 to finish):" << endl;
                        result.printPeople();
                        cin.ignore(100, '\n');
                        while (!std::cin.eof()) {
                            getline(cin, input_str, '\n');
                            if (input_str == "0")
                                break;
                            auto uk = tmpPeopleList.find(input_str);
                            if (uk != tmpPeopleList.end()) {
                                tmpPeopleList.erase(uk);
                            } else {
                                cout << "Wrong person's name!" << endl;
                                continue;
                            }
                        }
                        result.setPeopleList(tmpPeopleList);
                    } else if (choose_int == 3) {
                        result.clearPeopleList();
                    } else if (choose_int == 4)
                        continue;
                    else {
                        cout << "Wrong choose!" << endl;
                        continue;
                    }

                }
                else if (choose_int == 5) {
                    cout << "Write new duration of this event:" << endl;
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    result.setDuration(choose_int);
                }
                else if (choose_int == 6) {
                    time_t now_time = time(nullptr);
                    cout << "Do you want to enter hour and minutes?" << endl;
                    cout << "1. Yes" << endl;
                    cout << "2. No" << endl;
                    cout << "3. Back to menu" << endl;
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (choose_int == 1) { // if user wants hour and minutes
                        tm eventDate_tmp = inputDate(1);
                        tm check = {};
                        if (eventDate_tmp == check)
                            continue;
                        if (x.checkDateTime(eventDate_tmp))
                            cout << "You already have event for this date!" << endl;
                        else {
                            result.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday,
                                           eventDate_tmp.tm_hour, eventDate_tmp.tm_min);
                            result.setTimePrint(1);
                        }

                    }
                    else if (choose_int == 2) { // if user doesnt want hour and minutes
                        tm eventDate_tmp = *localtime(&now_time);
                        cin.ignore(1, '\n');
                        if (!(cin >> choose_int) || cin.gcount() > 1) {
                            cout << "Wrong date format!" << endl;
                            std::cin.clear();
                            std::cin.ignore(10, '\n');
                            continue;
                        }
                        if (choose_int >= 2023)
                            eventDate_tmp.tm_year = choose_int;
                        else {
                            cout << "Wrong year!!" << endl;
                            continue;
                        }
                        cin.ignore(100, '-');
                        if (!(cin >> choose_int) || cin.gcount() > 1) {
                            cout << "Wrong date format!" << endl;
                            std::cin.clear();
                            std::cin.ignore(10, '\n');
                            continue;
                        }
                        if (choose_int > 0 && choose_int <= 12)
                            eventDate_tmp.tm_mon = choose_int;
                        else {
                            cout << "Wrong month!!" << endl;
                            continue;
                        }
                        cin.ignore(100, '-');
                        if (!(cin >> choose_int) || cin.gcount() > 1) {
                            cout << "Wrong date format!" << endl;
                            std::cin.clear();
                            std::cin.ignore(10, '\n');
                            continue;
                        }
                        if (choose_int > 0 && choose_int <= 31)
                            eventDate_tmp.tm_mday = choose_int;
                        else {
                            cout << "Wrong day!!" << endl;
                            continue;
                        }
                        if (x.checkDate(eventDate_tmp))
                            cout << "You already have event for this date!" << endl;
                        else {
                            result.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday);
                            result.setTimePrint(2);
                        }
                    } else if (choose_int == 3)
                        continue;
                    else {
                        cout << "Wrong choose!" << endl;
                        continue;
                    }
                }
                else if (choose_int == 7)
                    break;
                else if (choose_int == 8) {
                    if (result == original)
                        break;
                    if (original.checkRepeated()) {
                        x.removeRepeatable(original, 1);
                        result.unsetRepeated();
                    }
                    x.removeEvent(original);
                    result.setEventID(original.getEventId());
                    x.removeEventByID(original.getEventId());
                    x.addEvent(result);
                    x.addEventId(result.getEventId(), result);
                    break;
                } else {
                    cout << "Wrong choose!" << endl;
                    continue;
                }
            }
            break;
        }
    }
}
