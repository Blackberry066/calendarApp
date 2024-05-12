#include "CApplication.h"
using namespace std;

std::set<Event> CApplication::searchEventFunc(Calendar &x, const int key, const int keysCount, const int searchMode) {
    std::set<Event> searchResult;
    cin.ignore(100, '\n');
    getline(cin, input_str, '\n');
    if (keysCount == 1) {
        searchResult = x.findEvent(key, input_str);
    }
    else if (keysCount > 1 && searchMode == 1) {
        std::set<Event> otherSearchResult = x.findEvent(key, input_str);
        std::set_union (searchResult.begin(), searchResult.end(), otherSearchResult.begin(),
                        otherSearchResult.end(), std::inserter(searchResult, searchResult.begin()));
    }
    else {
        searchResult = x.findEvent(key, input_str, searchResult);
    }
    return searchResult;
}
