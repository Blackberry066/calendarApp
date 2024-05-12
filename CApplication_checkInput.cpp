#include "CApplication.h"
using namespace std;

int CApplication::checkInput(int anotherIntVar) {
    /*
     * this method check our input for wrong symbols and clear it.
     * Example error: input = string, but variable = int
     * */
    if (anotherIntVar == 0) {
        if (!(cin >> choose_int) || choose_int == EOF) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong choose!" << endl;
            return -1;
        }
        return choose_int;
    }
    else {
        if (!(cin >> anotherIntVar) || choose_int == EOF) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Wrong choose!" << endl;
            return -1;
        }
        return anotherIntVar;
    }

}
