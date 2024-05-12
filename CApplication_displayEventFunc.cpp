#include "CApplication.h"
using namespace std;

void CApplication::displayEventFunc(const Calendar &x) {
    while (!std::cin.eof()) {
        cout << "Choose display mode:" << endl;
        cout << "1. Daily" << endl;
        cout << "2. Weekly" << endl;
        cout << "3. Monthly" << endl;
        cout << "4. Choose other time range" << endl;
        cout << "5. All events" << endl;
        cout << "6. Return to menu" << endl;
        choose_int = checkInput();
        std::map<int, Display*> types {
                {1, new Daily()},
                {2, new Weekly()},
                {3, new Monthly()}
        };

        if (choose_int == -1)
            break;
        cin.ignore(100, '\n');
        if (choose_int == 4) {
            cout << "Write days amount for time range (maximum time range is 5000): " << endl;
            int indexInt = 1;
            indexInt = checkInput(indexInt);
            if (indexInt < 1 || indexInt > 5000) {
                cout << "Wrong range!" << endl;
                break;
            }
            types[4] = new UserDisplay(indexInt);
        }
        else if (choose_int == 5) {
            DisplayAll someDisp;
            someDisp.printEvents(x.getEventList());
            break;
        }
        else if (choose_int == 6)
            break;
        else if ((types.find(choose_int) == types.end())) {
            cout << "Wrong choose!" << endl;
            break;
        }
        Display* someDisplay = types.at(choose_int);
        if (someDisplay == nullptr) {
            cout << "Not enough memory or some error happened, try again!" << endl;
            break;
        }
        cout << "Write: 1 for next day, 2 for previous day, 3 for stop displaying and return to menu" << endl;
        while (!std::cin.eof()) {
            someDisplay->show(x.getEventList());
            choose_int = checkInput();
            if (choose_int == -1)
                continue;
            if (choose_int == 1)
                someDisplay->next();
            else if (choose_int == 2)
                someDisplay->prev();
            else if (choose_int == 3)
                break;
            else {
                cout << "Wrong choose!" << endl;
                continue;
            }
        }
        for (const auto & ptr : types) {
            delete ptr.second;
        }
    }


}
