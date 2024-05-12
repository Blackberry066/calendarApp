#include "Event.h"
using namespace std;

void Event::setPeopleList(const std::set<std::string> & newPeopleList) {
    peopleList = newPeopleList;
}

void Event::addPerson (const std::string & person) {
    if (!person.empty()) {
        if (peopleList.find(person) == peopleList.end())
            peopleList.insert(person);
        else
            cout << "Person already added" << endl;
    }
    else
        cout << "Wrong person's name!" << endl;
}

void Event::printPeople() const {
    if (!peopleList.empty()){
        for (const auto& uk : peopleList) {
            cout << uk << endl;
        }
    }
}

std::set<std::string> Event::getPeople() const {
    return peopleList;
}

void Event::clearPeopleList() {
    peopleList.clear();
}