#include <iostream>
#include <vector>
#include <string>
#include "n_polynom.h"

/*
TODO::
- _degree törlése, mert felesleges gyakorlatilag
*/

namespace
{
    int pow(int base, int pwr)
    {
        int val = 1;
        for ( int i = 0; i < pwr; ++i)
        {
            val *= base;
        }
        return val;
    }
}


Polynom::Polynom(std::vector<int> v)
{
    _coeff_vector = v;
    _degree = v.size() - 1;
}
Polynom::Polynom(int c)
{
    _coeff_vector = {c};
    _degree = 0;
}


int Polynom::eval(int x) const 
{
    int p_val = 0;
    for ( unsigned int i = 0; i < _coeff_vector.size(); ++i )
    {
        p_val += _coeff_vector[i] * pow(x,i);
    }
    return p_val;
}

std::string Polynom::to_string() const
{
    std::string result;
    unsigned int skipped = 0;
    bool first = true;

    for ( int i = _coeff_vector.size() - 1; i >= 0 ; --i )
    {   
        if ( _coeff_vector[i] != 0 )
        {
            if ( _coeff_vector[i] < 0 )
            {
                result += std::to_string(_coeff_vector[i]);
            }
            else
            {
                if ( ! first )
                    result += "+";
                
                result += std::to_string(_coeff_vector[i]);
            }

            first = false;

            switch (i) 
            {
                case 0: result += ""; break;
                case 1: result += "X"; break;
                default: result += "X^" + std::to_string(i); break;
            }
        }
        else
        {
            ++skipped;
        }
    }

    if ( _coeff_vector.size() == skipped )
    {
        result += '0';
    }

    return result;
}


int Polynom::deg() const
{
    return _degree;
}

int Polynom::coeff(unsigned int n) const 
{
    if (_coeff_vector.size() > n)
        return _coeff_vector[n];
    return 0;
}
