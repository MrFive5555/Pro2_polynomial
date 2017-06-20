#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

#include "polynomial.h"

using namespace std;

polynomial::polynomial(const polynomial& srcPoly)
{
    termVec = srcPoly.termVec;
}

polynomial::polynomial(const string& polystr)
{
    stringstream stream(polystr);

    double coe = DBL_MAX;
    int exp = INT_MIN;
    char ch = 0;

    stream >> ch >> coe >> ch >> exp >> ch;

    while (stream) {
        addTermToPoly(term(coe, exp));
        stream >> ch >> coe >> ch >> exp >> ch;
    }

    sort(termVec.begin(), termVec.end(), termSort);
}

bool isStrValid(const string& polyStr)
{
    stringstream stream(polyStr);

    double coe = DBL_MAX;
    int exp = INT_MIN;
    char ch = 0;

    while (stream) {
        stream >> ch;
        if (stream.eof()) {
            return true;
        }

        if (ch != '(' && ch != '£¨') {
            return false;
        }

        stream >> coe;
        if (coe == DBL_MAX) {
            return false;
        }

        stream >> ch;
        if (ch != ',' && ch != '£¬') {
            return false;
        }

        stream >> exp;
        if (exp == INT_MIN) {
            return false;
        }

        stream >> ch;
        if (ch != ')' && ch != '£©') {
            return false;
        }
    }

    return true;
}


double polynomial::evalue(double x)
{
    double sum = 0;
    for (vector<term>::iterator iter = termVec.begin(); iter != termVec.end(); ++iter) {
        sum += iter->coefficient * pow(x, iter->exponential);
    }
    return sum;
}

polynomial polynomial::derivative() const
{
    polynomial newPoly;
    for (vector<term>::const_iterator iter = termVec.begin(); iter != termVec.end(); ++iter) {
        term newTerm(iter->coefficient, iter->exponential);
        newTerm.coefficient *= newTerm.exponential;
        if (newTerm.exponential != 0) {
            --newTerm.exponential;
        }
        newPoly.termVec.push_back(newTerm);
    }
    return newPoly;
}

polynomial polynomial::operator+(const polynomial& otherPoly) const
{
    polynomial newPoly(otherPoly);
    for (vector<term>::const_iterator iter = this->termVec.begin(); iter != this->termVec.end(); ++iter) {
        newPoly.addTermToPoly(*iter);
    }
    return newPoly;
}

polynomial polynomial::operator-(const polynomial& otherPoly) const
{
    polynomial newPoly(*this);
    for (vector<term>::const_iterator iter = otherPoly.termVec.begin(); iter != otherPoly.termVec.end(); ++iter) {
        newPoly.subTermToPoly(*iter);
    }
    return newPoly;
}

polynomial polynomial::operator*(const polynomial& otherPoly) const
{
    polynomial newPoly;
    for (vector<term>::const_iterator iter1 = this->termVec.begin(); iter1 != this->termVec.end(); ++iter1) {
        for (vector<term>::const_iterator iter2 = otherPoly.termVec.begin(); iter2 != otherPoly.termVec.end(); ++iter2) {
            newPoly.addTermToPoly(*iter1 * *iter2);
        }
    }
    return newPoly;
}

polynomial& polynomial::operator=(const polynomial& otherPoly)
{
    this->termVec = otherPoly.termVec;
    return *this;
}

bool polynomial::operator==(const polynomial& otherPoly)
{
    return this->termVec == otherPoly.termVec;
}

void polynomial::display() const
{
    display(cout);
}

void polynomial::display(ostream& out) const
{
    if (termVec.size() == 0) {
        cout << 0;
        return;
    }
    bool isFirst = true;
    for (vector<term>::const_iterator iter = this->termVec.begin(); iter != this->termVec.end(); ++iter) {
        if (iter->coefficient == 0) {
            continue;
        }

        if (iter->coefficient < 0) {
            out << " - ";
        } else if (iter->coefficient > 0 && isFirst == false) {
            out << " + ";
        }

        if (iter->exponential >= 0) {
            if (fabs(iter->coefficient) != 1) {
                out << fabs(iter->coefficient);
            }

            if (iter->exponential > 1) {
                out << "x^" << iter->exponential;
            } else if (iter->exponential == 1) {
                out << "x";
            } else if (fabs(iter->coefficient) == 1) {
                out << fabs(iter->coefficient);
            }
        } else {
            out << fabs(iter->coefficient);
            if (iter->exponential != -1) {
                out << "/x^" << fabs(iter->exponential) << "";
            } else {
                out << "/x";
            }
        }
        

        isFirst = false;
    }
}

ostream& operator<<(ostream& out, const polynomial& poly)
{
    poly.display(out);
    return out;
}



void polynomial::addTermToPoly(const term& theTerm)
{
    vector<term>::iterator sameTerm = find_if(termVec.begin(), termVec.end(), term(theTerm));
    if (sameTerm == termVec.end()) {
        termVec.push_back(theTerm);
    } else {
        sameTerm->coefficient += theTerm.coefficient;
        if (sameTerm->coefficient == 0) {
            termVec.erase(sameTerm);
        }
    }

    sort(termVec.begin(), termVec.end(), termSort);
}

void polynomial::subTermToPoly(const term& theTerm)
{
    vector<term>::iterator sameTerm = find_if(termVec.begin(), termVec.end(), term(theTerm));
    if (sameTerm == termVec.end()) {
        termVec.push_back(term(-theTerm.coefficient, theTerm.exponential));
    } else {
        sameTerm->coefficient -= theTerm.coefficient;
        if (sameTerm->coefficient == 0) {
            termVec.erase(sameTerm);
        }
    }

    sort(termVec.begin(), termVec.end(), termSort);
}

string polynomial::storeFormat()
{
    stringstream strstream;

    for (vector<term>::iterator iter = termVec.begin(); iter != termVec.end(); ++iter) {
        strstream << "(" << iter->coefficient << "," << iter->exponential << ")";
    }

    string ret;
    strstream >> ret;

    return ret;
}