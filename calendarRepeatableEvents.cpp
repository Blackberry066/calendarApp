#include "Calendar.h"
using namespace std;

void Calendar::addRepeatableEvent (const Event & someRepeatableEvent) {
    repeatableEventList.insert(someRepeatableEvent);
}

void Calendar::printRepeatable() const {
    std::set<string> printedEvents;
    for (const auto & uk : repeatableEventList) {
        if (printedEvents.find(uk.getName()) != printedEvents.end())
            continue;
        else {
            cout << uk.getEventId() << " : " << uk.getName() << endl;
            printedEvents.insert(uk.getName());
        }
    }
}

void Calendar::removeRepeatable(const Event & someRepeatableEvent, const int key) {
    const std::string tmpEventName = someRepeatableEvent.getName();
    auto ptr = repeatableEventList.find(someRepeatableEvent);
    if (key == 0) {
        bool firstIteration = true;
        for (const auto & it : repeatableEventList) {
            if (it.getName() == tmpEventName) {
                if (!firstIteration)
                    repeatableEventList.erase(ptr);
                auto uk = eventList.find(it);
                eventIdMap.erase(uk->getEventId());
                eventList.erase(uk);
                ptr = repeatableEventList.find(it);
                firstIteration = false;
                continue;
            }
        }
        repeatableEventList.erase(ptr);
    }
    else if (key == 1)
        repeatableEventList.erase(ptr);
}

std::set<Event> Calendar::getRepeatableEventList() const {
    return repeatableEventList;
}