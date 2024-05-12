#include "UserDisplay.h"


UserDisplay::UserDisplay() {
    dayCount = 1; // one day by default
    setMinMax(dayCount);
}

UserDisplay::UserDisplay(const int someAmountOfDays) {
	cout << "days are " << someAmountOfDays << endl;
    dayCount = someAmountOfDays;
    setMinMax(dayCount);
}

void UserDisplay::show(const std::set<Event> &eventList) const {
    if (!eventList.empty()) {
        cout << "Display time is between " << minTime << " and " << maxTime << endl;
        cout << "Your time range (in days): " << dayCount << endl;
        cout << "Your events for this range: " << endl;
        for (const auto & uk : eventList) {
            if (uk.getDate() >= minTime && uk.getDate() <= maxTime) {
                cout << uk.getName() << endl;
                tm eventTime = uk.getDate();
                if (uk.getTimePrint()) {
                	if (eventTime.tm_min >= 10)
                    	cout << eventTime << " " << eventTime.tm_hour << ":" << eventTime.tm_min << endl;
                    else
                    	cout << eventTime << " " << eventTime.tm_hour << ":0" << eventTime.tm_min << endl;
                }
                else
                    cout << eventTime << endl;
            }
        }
    }
    else {
        cout << "You dont have any events!" << endl;
    }
}

void UserDisplay::next() {
    if (wasPrev) {
        displayTime+=dayCount*secondsPerDay;
        wasPrev = false;
    }
    setMinMax(dayCount);
    wasNext = true;
}

void UserDisplay::prev() {
    if (wasNext) {
        displayTime-=dayCount*secondsPerDay;
        wasNext = false;
    }
    setMinMax(dayCount, 1);
    wasPrev = true;
}

void UserDisplay::setTimeSpread(const int spread) {
    dayCount = spread;
}
