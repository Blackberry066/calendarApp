#include "Daily.h"
using namespace std;

Daily::Daily() {
    day = *localtime(&displayTime);
    day.tm_year+=1900;
    day.tm_mon+=1;
}

void Daily::show (const std::set<Event> & eventList) const {
    if (!eventList.empty()) {
        cout << "Display date is " << day << endl;
        cout << "Your events for today: " << endl;
        cout << "======================" << endl;
        int dayTasks = 0;
        for (const auto & uk : eventList) {
            tm tmpDate = uk.getDate();
            if (tmpDate.tm_year == day.tm_year && tmpDate.tm_mon == day.tm_mon &&
                tmpDate.tm_mday == day.tm_mday) {
                tm eventTime = uk.getDate();
                dayTasks++;
                if (uk.getTimePrint())
                    if (eventTime.tm_min < 10)
                        cout << uk.getName() << " " << eventTime.tm_hour << ":0" << eventTime.tm_min << endl;
                    else
                        cout << uk.getName() << " " << eventTime.tm_hour << ":" << eventTime.tm_min << endl;
                else
                	cout << uk.getName() << endl;
            }
        }
        if (dayTasks == 0)
        	cout << "Today no events!" << endl;
        
    }
    else {
        cout << "You dont have any events!" << endl;
    }
}
void Daily::next () {
    displayTime+=secondsPerDay;
    day = *localtime(&displayTime);
    day.tm_year+=1900;
    day.tm_mon+=1;
}
void Daily::prev () {
    displayTime-=secondsPerDay;
    day = *localtime(&displayTime);
    day.tm_year+=1900;
    day.tm_mon+=1;
}

