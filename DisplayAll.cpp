#include "DisplayAll.h"
using namespace std;



void DisplayAll::printEvents(const std::set<Event> &eventList) const {
    if (!eventList.empty()) {
        cout << "Your events: " << endl;
        for (const auto &uk: eventList) {
            cout << "Name: " << uk.getName() << endl;
            tm eventTime = uk.getDate();
            cout << "Event ID: " << uk.getEventId() << endl;
            if (uk.getTimePrint()) {
            	if (eventTime.tm_min < 10)
            		cout << eventTime << " " << eventTime.tm_hour << ":0" << eventTime.tm_min << endl;
            	else
            		cout << eventTime << " " << eventTime.tm_hour << ":" << eventTime.tm_min << endl;
            }
            else
                cout << eventTime.tm_year << "-" << eventTime.tm_mon << "-" << eventTime.tm_mday << endl;
        }
    } else {
        cout << "You dont have any added events!" << endl;
    }
}
