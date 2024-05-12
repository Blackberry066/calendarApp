#include "CApplication.h"
using namespace std;

tm CApplication::inputDate(const int key) {
    /*
     * This method check our date formats and wrong symbols in date inputs
     */
    time_t now_time = time(nullptr);
    if (key == 0)
        cout << "Enter your date in format YYYY-mm-dd" << endl;
    else if (key == 1)
        cout << "Enter your date in format YYYY-mm-dd hh:mm" << endl;
    tm eventDate_tmp = *localtime(&now_time);
    cin.ignore(1, '\n');
    choose_int = checkInput();
    if (choose_int == -1)
    	return eventDate_tmp = {};
    if (choose_int >= 2023)
        eventDate_tmp.tm_year=choose_int;
    else {
        cout << "Wrong year!!" << endl;
        return eventDate_tmp = {};
    }

    cin.ignore(100, '-');
    choose_int = checkInput();
    if (choose_int == -1)
    	return eventDate_tmp = {};
    if (choose_int > 0 && choose_int <= 12)
        eventDate_tmp.tm_mon=choose_int;
    else {
        cout << "Wrong month!!" << endl;
        return eventDate_tmp = {};
    }


    cin.ignore(100, '-');
    choose_int = checkInput();
    if (choose_int == -1)
    	return eventDate_tmp = {};
    if (choose_int > 0 && choose_int <= 31)
        eventDate_tmp.tm_mday=choose_int;
    else {
        cout << "Wrong day!!" << endl;
        return eventDate_tmp = {};
    }

    if (key == 1) {
        cin.ignore(100, ' ');
        choose_int = checkInput();
    	if (choose_int == -1)
    		return eventDate_tmp = {};
        if (choose_int >= 0 && choose_int <= 23)
            eventDate_tmp.tm_hour = choose_int;
        else {
            cout << "Wrong hour!!" << endl;
            return eventDate_tmp = {};
        }
        cin.ignore(100, ':');
        choose_int = checkInput();
    	if (choose_int == -1)
    		return eventDate_tmp = {};
        if (choose_int >= 0 && choose_int <= 59)
            eventDate_tmp.tm_min = choose_int;
        else {
            cout << "Wrong minutes amount!!" << endl;
            return eventDate_tmp = {};
        }
    }
    return eventDate_tmp;

}
