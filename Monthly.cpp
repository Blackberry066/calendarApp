#include "Monthly.h"


Monthly::Monthly() {
    dayCount = 30;
    setMinMax(dayCount);
}

void Monthly::show (const std::set<Event> & eventList) const {
    if (!eventList.empty()) {
        cout << "Display time is between " << minTime << " and " << maxTime << endl;
        cout << "Your events for this month: " << endl;
        for (const auto & uk : eventList) {
            if (uk.getDate() >= minTime && uk.getDate() <= maxTime) {
                tm eventTime = uk.getDate();
                if (uk.getTimePrint())
                    if (eventTime.tm_min >= 10)
                        cout << uk.getName() << " " << eventTime.tm_year << "-" << eventTime.tm_mon << "-" << eventTime.tm_mday
                             << " " << eventTime.tm_hour << ":" << eventTime.tm_min << endl;
                    else
                        cout << uk.getName() << " " << eventTime.tm_year << "-" << eventTime.tm_mon << "-" << eventTime.tm_mday
                             << " " << eventTime.tm_hour << ":0" << eventTime.tm_min << endl;
                else
                    cout << uk.getName() << " " << eventTime.tm_year << "-" << eventTime.tm_mon << "-" << eventTime.tm_mday << endl;
            }
        }
    }
    else {
        cout << "You dont have any events!" << endl;
    }
}



void Monthly::next () {
    if (wasPrev) {
        displayTime+=dayCount*secondsPerDay;
        wasPrev = false;
    }
    setMinMax(dayCount);
    wasNext = true;
}


void Monthly::prev () {
    if (wasNext) {
        displayTime-=30*secondsPerDay;
        wasNext = false;
    }
    setMinMax(dayCount, 1);
    wasPrev = true;
}
