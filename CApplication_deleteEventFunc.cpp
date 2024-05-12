#include "CApplication.h"
using namespace std;

void CApplication::deleteEventFunc (Calendar & x) {
    while(!std::cin.eof()) {
        if (x.eventsCount() == 0) {
            cout << "You don't have any events for delete!" << endl;
            break;
        }
        cout << "Which type of event you want to delete?" << endl;
        cout << "1. One-time event" << endl;
        cout << "2. Repeatable event" << endl;
        cout << "3. Delete all events" << endl;
        cout << "4. Return to menu" << endl;
        choose_int = checkInput();
        if (choose_int == -1)
            break;
        if (choose_int == 1) {
            if (x.printEventIDs(1) != 0) {
                cout << "Which event you want to delete? Write its id" << endl;
                cin.ignore(100, '\n');
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
            }
            else {
                cout << "You dont have any one-time events!" << endl;
                continue;
            }
            Event eventForDeletion = x.getEventByID(choose_int);
            if (!(eventForDeletion.getName().empty()) && !(eventForDeletion.checkRepeated())) {
                x.removeEvent(eventForDeletion);
                x.removeEventByID(choose_int);
            }
            else
                cout << "Wrong event ID!" << endl;

        }
        else if (choose_int == 2) {
            if(x.getRepeatableEventList().empty()) {
                cout << "You dont have any repeatable events!" << endl;
                continue;
            }
            cout << "Select repeatable event for deletion (write its id):" << endl;
            x.printRepeatable();
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            Event repeatEventForDeletion = x.getEventByID(choose_int);
            if (!(repeatEventForDeletion.getName().empty()) && repeatEventForDeletion.checkRepeated()) {
                x.removeRepeatable(repeatEventForDeletion);
            }
            else {
                cout << "Wrong event ID!" << endl;
            }


        }
        else if (choose_int == 3) {
            x.clearEventList();
        }
        else if (choose_int == 4)
            break;
        else {
            cout << "Wrong choose!" << endl;
            continue;
        }
        break;
    }
}
