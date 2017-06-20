#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class term {
public:
    term(double coe, int exp);
    term(const term& otherTerm);
    bool operator()(term& other);

    term operator*(const term& otherTerm) const;
    term operator*(double num) const;
    bool operator==(const term& otherTerm) const;

    friend class polynomial;
    friend bool termSort(const term& term1, const term& term2);

private:
    double coefficient;
    int exponential;
};

class polynomial {
public:
    polynomial() {};
    polynomial(const polynomial& srcPoly);

    polynomial(const string& polystr); 
    //change the string like "(3,3)(2,1)(4,0)" to a polynomial "3x^3 + 2x + 4"

    double evalue(double x);
    polynomial derivative() const;
    polynomial operator+(const polynomial& otherPoly) const;
    polynomial operator-(const polynomial& otherPoly) const;
    polynomial operator*(const polynomial& otherPoly) const;
    polynomial& operator=(const polynomial& otherPoly);
    bool operator==(const polynomial& otherPoly);

    void display() const;
    void display(ostream& out) const;

    friend ostream& operator<<(ostream& out, const polynomial& poly);

    void addTermToPoly(const term& theTerm);
    void subTermToPoly(const term& theTerm);

    //change a polynomial "3x^3 + 2x + 4"  to the string like "(3,3)(2,1)(4,0)"
    string storeFormat(); 

private:
    vector<term> termVec;
};

bool isStrValid(const string& polyStr);
//check if the specified string "polyStr" can be changed to a polynomial

#endif // !POLYNOMIAL_H_

