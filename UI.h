#ifndef UI_H_
#define UI_H_

#include "polynomial.h"
#include <map>
#include <utility>
#include <iostream>

class UI {
public:
    UI();
    bool getCommand();
private:
    map<string, polynomial> polyMap;

    void printMenu();

    void input();
    void del();

    //polynomial operation
    void add();
    void subtraction();
    void multiply();
    void derivative();
    void evalueAtAPoint();
    void isEqual();

    //seek the polynomial which has been inputed
    void seek();

    bool insertPoly(const polynomial poly);

    /* check whether the string is the polynomial name 
     * or can change to a polynomial 
     */
    bool canGetPoly(string str);

    /* warning :
     * the arg str must has pass the check "canGetPoly"
     */
    polynomial getPoly(string str);

    /* check whether the string can be convert to double
    */
    bool canGetDouble(string str);

    //string getName();
    bool getYesNo();

    //refresh the record file
    void refreshFile();
};

#endif // !UI_H_