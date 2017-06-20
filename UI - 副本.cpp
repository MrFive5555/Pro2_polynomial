#include <iostream>
#include <string>
#include "UI.h"

using namespace std;

void UI::printMenu()
{
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
    cout << "" << endl;
}

bool UI::getCommand()
{
    printMenu();
    int command = 0;
    switch (command)
    {
        case 1:
            input();
            break;
        case 2:
            del();
            break;
        case 3:
            opera();
            break;
        case 4:
            seek();
            break;
        case 5:
            return false;
        default:
            cout << "" << endl;
            break;
    }

    return true;
}

void UI::input()
{
    polynomial newPoly;
    cout << "";
    double coe = 1;
    int exp = 1;
    
    while (coe != 0 && exp != 0) {

        cout << "" << endl;
        char ch = 0;
        cin >> ch;
        if (ch != '(') {
            cout << "" << endl;
            coe = 1;
        } 
        if (!cin) {
            cout << "" << endl;
            cin.clear();
        }

        cin >> coe;
        if (!cin) {
            cout << "" << endl;
            cin.clear();
        }

        cin >> ch;
        if (ch != ',') {
            cout << "" << endl;
            coe = 1;
        }
        if (!cin) {
            cout << "" << endl;
            cin.clear();
        }

        cin >> exp;
        if (!cin) {
            cout << "" << endl;
            cin.clear();
        }

        cin >> ch;
        if (ch != ',') {
            cout << "" << endl;
            coe = 1;
        }
        if (!cin) {
            cout << "" << endl;
            cin.clear();
        }

        newPoly.addTermToPoly(term(coe, exp));
    }

    cout << "" << endl;
    string name;
    cin >> name;
    cout << name;

    polyMap.insert(pair<string, polynomial>(name, newPoly));
}