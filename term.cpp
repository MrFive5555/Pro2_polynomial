#include "polynomial.h"

term::term(double coe, int exp)
{
    coefficient = coe;
    exponential = exp;
}

term::term(const term& otherTerm)
{
    coefficient = otherTerm.coefficient;
    exponential = otherTerm.exponential;
}

bool term::operator()(term& other)
{
    if (exponential == other.exponential) {
        return true;
    } else {
        return false;
    }
}

term term::operator*(const term& otherTerm) const
{
    return term(this->coefficient*otherTerm.coefficient, this->exponential + otherTerm.exponential);
}

term term::operator*(double num) const
{
    return term(this->coefficient * num, this->exponential);
}

bool term::operator==(const term& otherTerm) const
{
    return (this->coefficient == otherTerm.coefficient
        && this->exponential == otherTerm.exponential);
}

bool termSort(const term& term1, const term& term2) {
    return term1.exponential > term2.exponential;
}