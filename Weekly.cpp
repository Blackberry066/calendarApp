#include "Weekly.h"

Weekly::Weekly() {
    dayCount = 7;
    setMinMax(dayCount);
}

void Weekly::show (const std::set<Event> & eventList) const {
    if (!eventList.empty()) {
        cout << "Display time is between " << minTime << " and " << maxTime << endl;
        cout << "Your events for this week: " << endl;
        cout << "==========================" << endl;
        for (const auto & uk : eventList) {
            if (uk.getDate() >= minTime && uk.getDate() <= maxTime) {
                tm eventTime = uk.getDate();
                if (uk.getTimePrint()) {
                    cout << "Week day is " << eventTime.tm_wday << endl;
                    if (eventTime.tm_min < 10)
                        cout << uk.getName() << " " << eventTime << " " << eventTime.tm_hour << ":0" << eventTime.tm_min << endl;
                    else
                        cout << uk.getName() << " " << eventTime << " " << eventTime.tm_hour << ":" << eventTime.tm_min << endl;
                    cout << "--------------------------" << endl;
                }
                else {
                	cout << "Week day is " << eventTime.tm_wday << endl;
                    cout << eventTime << endl;
                    cout << "--------------------------" << endl;
                }
            }
        }
    }
    else {
        cout << "You dont have any events!" << endl;
    }
}

void Weekly::next () {
    if (wasPrev) {
        displayTime+=dayCount*secondsPerDay;
        wasPrev = false;
    }
    setMinMax(dayCount);
    wasNext = true;
}

void Weekly::prev () {
    if (wasNext) {
        displayTime-=7*secondsPerDay;
        wasNext = false;
    }
    setMinMax(dayCount, 1);
 	wasPrev = true;
}
