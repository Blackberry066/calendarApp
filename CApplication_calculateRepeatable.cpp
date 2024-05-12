#include "CApplication.h"
using namespace std;

void CApplication::calculateRepeatable(Calendar & x, const int frequency, const int timeRange, Event & y) {
    const int secondsPerDay = 24 * 60 * 60;
    time_t curTime_uk = time(nullptr);
    time_t futureTime_uk = curTime_uk + secondsPerDay * timeRange;
    while (!std::cin.eof()) {
        curTime_uk+=secondsPerDay*frequency;
        if (futureTime_uk < curTime_uk)
            break;
        tm curTime = *localtime(&curTime_uk);
        curTime.tm_year+=1900;
        curTime.tm_mon+=1;
        if(x.checkDate(curTime)) {
            cout << "You already have event for date " << curTime << endl;
            continue;
        }
        y.setDate(curTime.tm_year, curTime.tm_mon, curTime.tm_mday);
        if (frequency == 1) {
            if (futureTime_uk >= curTime_uk) {
                y.setEventID(x.getMaxId());
                x.addRepeatableEvent(y);
                x.addEventId(y.getEventId(), y);
                x.addEvent(y);
            }
            else
                break;
        }
        else {
            if (futureTime_uk > (curTime_uk+secondsPerDay*frequency)) {
                y.setEventID(x.getMaxId());
                x.addRepeatableEvent(y);
                x.addEventId(y.getEventId(), y);
                x.addEvent(y);
            }
            else
                break;
        }
    }
}
