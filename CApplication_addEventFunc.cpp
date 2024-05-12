#include "CApplication.h"
using namespace std;

void CApplication::addEventFunc(Event & y, Calendar & x) {
    bool cancel = false;
    cout << "Write name of event:" << endl;
    cin.ignore(100, '\n');
    getline(std::cin, input_str, '\n');
    y.setName(input_str);
    while(!std::cin.eof()) {
        cout << "Some other attributes?" << endl;
        cout << "1. Set place" << endl;
        cout << "2. Add person" << endl;
        cout << "3. Set tag" << endl;
        cout << "4. Set duration" << endl;
        cout << "5. Set some note" << endl;
        cout << "6. Finish creating and set date" << endl;
        cout << "7. Cancel creating" << endl;
        choose_int = checkInput();
        if (choose_int == -1)
            continue;
        if (choose_int == 1) { // if user wants to set place
            cout << "Write place of event" << endl;
            cin.ignore(100, '\n');
            getline(cin, input_str, '\n');
            y.setPlace(input_str);
        }
        else if (choose_int == 2) { // set people
            cout << "Write people, write 0 to save and return in previous menu" << endl;
            cin.ignore(100, '\n');
            while (true) {
                getline(cin, input_str, '\n');
                if (input_str == "0")
                    break;
                y.addPerson(input_str);
            }
        }
        else if (choose_int == 3) { // set tag
            cout << "Write tag for your event" << endl;
            cin.ignore(100, '\n');
            getline(cin, input_str, '\n');
            y.setTag(input_str);
        }
        else if (choose_int == 4) { // set duration
            cout << "Write event duration in minutes, max duration 1440 minutes (one day)" << endl;
            cin.ignore(100, '\n');
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            else
                y.setDuration(choose_int);
        }
        else if (choose_int == 5) { // set note
            cout << "Write your note for event (max length is 255): " << endl;
            cin.ignore(100, '\n');
            getline(cin, input_str, '\n');
            if(input_str.size() <= 255) {
                y.setNote(input_str);
            }
            else {
                cout << "Note length is more than 255!" << endl;
                continue;
            }
        }
        else if (choose_int == 6) {
            const int secondsPerDay = 24 * 60 * 60;
            cout << "How do you want to set your date?" << endl;
            cout << "1. Write date in format YYYY-mm-dd" << endl;
            cout << "2. Write days amount before event" << endl;
            cout << "3. Create repeatable event" << endl;
            cout << "4. Return to previous menu" << endl;
            cin.ignore(100, '\n');
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            if (choose_int == 1) {
                cout << "Do you want to enter hour and minutes?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "3. Back to menu" << endl;
                cin.ignore(100, '\n');
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
                if (choose_int == 1) { // if user wants hour and minutes
                    tm eventDate_tmp = inputDate(1);
                    tm check = {};
                    if (eventDate_tmp == check)
                        continue;
                    if (x.checkDate(eventDate_tmp)) {
                        cout << "You already has some event for this date! Do you want to move your date? Nearest "
                                "free date is ";
                        eventDate_tmp.tm_year-=1900;
                        eventDate_tmp.tm_mon-=1;
                        time_t timeTmp = mktime(&eventDate_tmp);
                        while (true) {
                            timeTmp+=secondsPerDay;
                            eventDate_tmp = *localtime(&timeTmp);
                            eventDate_tmp.tm_year+=1900;
                            eventDate_tmp.tm_mon+=1;
                            if (!(x.checkDate(eventDate_tmp))) {
                                cout << eventDate_tmp << endl;
                                break;
                            }
                        }
                        cout << "Do you want to set that date with your time or choose another?" << endl;
                        cout << "1. Set this date" << endl;
                        cout << "2. Return to menu and choose other date" << endl;
                        choose_int = checkInput();
                        if (choose_int == -1 || choose_int == 2)
                            continue;
                        if (choose_int == 1) {
                            y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday,
                                      eventDate_tmp.tm_hour, eventDate_tmp.tm_min);
                            y.setTimePrint(1);
                        }
                    }
                    else {
                        y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday,
                                  eventDate_tmp.tm_hour, eventDate_tmp.tm_min);
                        y.setTimePrint(1);
                    }

                }
                else if (choose_int == 2) { // if user doesnt want set hour and minutes
                    tm eventDate_tmp = inputDate();
                    tm check = {};
                    if (eventDate_tmp == check)
                        continue;
                    if (x.checkDate(eventDate_tmp)) {
                        cout << "You already has some event for this date! Do you want to move your date? Nearest "
                                "free date is ";
                        eventDate_tmp.tm_year-=1900;
                        eventDate_tmp.tm_mon-=1;
                        time_t timeTmp = mktime(&eventDate_tmp);
                        while (true) {
                            timeTmp+=secondsPerDay;
                            eventDate_tmp = *localtime(&timeTmp);
                            eventDate_tmp.tm_year+=1900;
                        	eventDate_tmp.tm_mon+=1;
                            if (!(x.checkDate(eventDate_tmp))) {
                                cout << eventDate_tmp << endl;
                                break;
                            }
                        }
                        cout << "Do you want to set that date or choose another?" << endl;
                        cout << "1. Set this date" << endl;
                        cout << "2. Return to menu and choose other date" << endl;
                        choose_int = checkInput();
                        if (choose_int == -1 || choose_int == 2)
                            continue;
                        if (choose_int == 1) {
                            y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday);
                        }
                    }
                    else
                        y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday);
                }
                else if (choose_int == 3)
                    continue;

                else {
                    cout << "Wrong choose!" << endl;
                    continue;
                }
                break;
            }
            else if (choose_int == 2) { // write days amount
                time_t currentTime;
                time (&currentTime);
                cin.ignore(100, '\n');
                int input_days = 0;
                input_days = checkInput(input_days);
        		if (input_days == -1)
            		continue;
                time_t futureTime = currentTime + input_days * secondsPerDay;
                tm eventDate_tmp = *localtime(&futureTime);
                eventDate_tmp.tm_year+=1900;
                eventDate_tmp.tm_mon+=1;
                if (x.checkDate(eventDate_tmp)) {
                    cout << "You already has some event for this date! Do you want to move your date? Nearest "
                            "free date is ";
                    eventDate_tmp.tm_year-=1900;
                    eventDate_tmp.tm_mon-=1;
                    time_t timeTmp = mktime(&eventDate_tmp);
                    while (true) {
                        timeTmp+=secondsPerDay;
                        eventDate_tmp = *localtime(&timeTmp);
                        eventDate_tmp.tm_year+=1900;
                    	eventDate_tmp.tm_mon+=1;
                        if (!(x.checkDate(eventDate_tmp))) {
                            cout << eventDate_tmp << endl;
                            break;
                        }
                    }
                    cout << "Do you want to set that date or choose another?" << endl;
                    cout << "1. Set this date" << endl;
                    cout << "2. Return to menu and choose other date" << endl;
                    choose_int = checkInput();
                    if (choose_int == -1 || choose_int == 2)
                        continue;
                    if (choose_int == 1) {
                        y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon, eventDate_tmp.tm_mday);
                    }
                }
                else
                    y.setDate(eventDate_tmp.tm_year, eventDate_tmp.tm_mon,
                              eventDate_tmp.tm_mday);
                break;
            }
            else if (choose_int == 3) { // repeatable event
                cout << "How long do you want to repeat this event?" << endl;
                cout << "1. One week" << endl;
                cout << "2. One month" << endl;
                cout << "3. One year" << endl;
                cout << "4. Other value" << endl;
                cout << "5. Return to menu" << endl;
                y.setRepeated();
                cin.ignore(100, '\n');
                choose_int = checkInput();
                if (choose_int == -1)
                    continue;
                if (choose_int == 1) { // One week
                    calculateRepeatable(x, 1, 7, y);
                }
                else if (choose_int == 2) { // One month
                    cout << "How often do you want to repeat this task?" << endl;
                    cout << "1. Everyday" << endl;
                    cout << "2. Once a week" << endl;
                    cout << "3. Another frequency" << endl;
                    cout << "4. Back to menu" << endl;
                    cin.ignore(100, '\n');
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (choose_int == 1) {
                        calculateRepeatable(x, 1, 30, y);
                    }
                    else if (choose_int == 2) {
                        calculateRepeatable(x, 7, 30, y);
                    }
                    else if (choose_int == 3) {
                        int inputDays = 0;
                        cout << "Write your frequency (in days)" << endl;
                        inputDays = checkInput(inputDays);
                        if (choose_int == -1)
                            continue;
                        if (inputDays > 30) {
                            cout << "Your frequency is bigger than days amount!" << endl;
                            continue;
                        }
                        calculateRepeatable(x, inputDays, 30, y);
                    }
                    else if (choose_int == 4)
                        continue;
                }
                else if (choose_int == 3) { // one year
                    cout << "How often do you want to repeat this task?" << endl;
                    cout << "1. Everyday" << endl;
                    cout << "2. Once a week" << endl;
                    cout << "3. Once a month" << endl;
                    cout << "4. Another frequency" << endl;
                    cout << "5. Back to menu" << endl;
                    cin.ignore(100, '\n');
                    choose_int = checkInput();
                    if (choose_int == -1)
                        continue;
                    if (choose_int == 1) {
                        calculateRepeatable(x, 1, 365, y);
                    }
                    else if (choose_int == 2) {
                        calculateRepeatable(x, 7, 365, y);
                    }
                    else if (choose_int == 3) {
                        calculateRepeatable(x, 30, 365, y);
                    }
                    else if (choose_int == 4) {
                        int inputDays = 0;
                        cout << "Write your frequency (in days)" << endl;
                        inputDays = checkInput(inputDays);
                        if (choose_int == -1)
                            continue;
                        if (inputDays > 365) {
                            cout << "Your frequency is bigger than days amount!" << endl;
                            continue;
                        }
                        calculateRepeatable(x, inputDays, 365, y);
                    }
                    else if (choose_int == 5)
                        continue;

                }
                else if (choose_int == 4) { // other days amount for repeating
                    int days_amount = 0;
                    cout << "Write your days amount for repeat event (maximum time range is 5000)" << endl;
                    cin.ignore(100, '\n');
                    days_amount = checkInput(days_amount);
                    if (days_amount == -1)
                        continue;
                    else {
                        if (days_amount < 1 || days_amount > 5000) {
                            cout << "Wrong days amount!" << endl;
                            continue;
                        }
                        cout << "How often do you want to repeat this task?" << endl;
                        cout << "1. Once a day" << endl;
                        cout << "2. Once a week" << endl;
                        cout << "3. Once a month" << endl;
                        cout << "4. Another frequency" << endl;
                        cout << "5. Return to menu" << endl;
                        choose_int = checkInput();
                        if (choose_int == -1)
                            continue;
                        if (choose_int == 1) { // once a day
                            calculateRepeatable(x, 1, days_amount, y);
                        }
                        else if (choose_int == 2 && days_amount >= 7) { // once a week
                            calculateRepeatable(x, 7, days_amount, y);
                        }
                        else if (choose_int == 3 && days_amount >= 30) { // once a month
                            calculateRepeatable(x, 30, days_amount, y);
                        }
                        else if (choose_int == 4) {
                            int inputDays = 0;
                            cout << "Write your frequency (in days)" << endl;
                            inputDays = checkInput(inputDays);
                            if (choose_int == -1)
                                continue;
                            if (inputDays > days_amount) {
                                cout << "Your frequency is bigger than days amount!" << endl;
                                continue;
                            }
                            calculateRepeatable(x, inputDays, days_amount, y);
                        }
                        else if (choose_int == 5)
                            continue;
                        else {
                            cout << "Your days amount lower than repetition rate!" << endl;
                            continue;
                        }
                    }

                }
                else if (choose_int == 5) {
                    y.unsetRepeated();
                    continue;
                }
                else {
                    cout << "Wrong choose!" << endl;
                    continue;
                }
                break;
            }
            else if (choose_int == 4)
                continue;
            else
                cout << "Wrong choose!" << endl;
        }
        else if (choose_int == 7) {
            cancel = true;
            break;
        }
        else
            cout << "Wrong choose!" << endl;
    }
    if (!cancel) {
        y.setEventID(x.getMaxId());
        if (y.checkRepeated())
            x.addRepeatableEvent(y);
        x.addEventId(y.getEventId(), y);

        x.addEvent(y);
    }
}

