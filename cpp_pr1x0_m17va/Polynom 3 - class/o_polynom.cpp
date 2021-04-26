#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "o_polynom.h"

namespace
{
    typedef unsigned int uint;

    int pow(int base, uint pwr)
    {
        int val = 1;
        for ( uint i = 0; i < pwr; ++i)
        {
            val *= base;
        }
        return val;
    }

    std::string format_coeff(int coeff, int pwr)
    {
        if ( (0 != pwr) && (1 == coeff) )
        {
            return "";
        }
        else 
        {
            return std::to_string(coeff);
        }
    }

    std::string format_power(int pwr)
    {
        switch (pwr) 
        {
            case 0: return ""; break;
            case 1: return "x"; break;
            default: return "x^" + std::to_string(pwr); break;
        }
    }

}

Polynom::Polynom(const std::vector<int>& v)
{
    _assign_new_from_vector(v);
}

Polynom::Polynom(int c)
{
    _coeffVector.push_back(Term(c, 0));
    _degree = 0;
};

Polynom::Polynom(const char * line)
{
    _assign_new_from_string(line);
}

int Polynom::coeff(uint n) const
{
    //binary search megfelelőbb lenne nagy polinomok miatt eshetősége miatt
    for ( Term term : _coeffVector )
    {
        if ( n == term.deg )
        {
            return term.coeff;
        } 
    }
    return 0;
}

int Polynom::deg() const
{
    return _degree;
}

int Polynom::eval(int x) const
{
    int p_val = 0;
    for ( uint i = 0; i < _coeffVector.size(); ++i )
    {
        const Term& current_term = _coeffVector[i];
        p_val += current_term.coeff * pow(x, current_term.deg);
    }
    return p_val;
}

std::string Polynom::to_string() const
{
    std::string result;
    uint skipped = 0;
    uint coeff;
    std::string sign;
    bool first = true;

    for ( int i = _degree; i >= 0 ; --i )
    {   
        if ( _coeffVector[i] != 0 )
        {
            if ( _coeffVector[i] < 0 )
            {
                if ( first )
                {
                    sign = "-";
                    first = false;
                }
                else 
                    sign = " - ";
                
                coeff = -_coeffVector[i];
            }
            else
            {
                if ( first )
                {
                    sign = "";
                    first = false;
                }
                else 
                    sign = " + ";
                
                coeff = _coeffVector[i];
            }

            result += sign + format_coeff(coeff, i)  + format_power(i);
        }
        else
        {
            ++skipped;
        }
    }

    if ( (_degree + 1)  == skipped )
    {
        result += '0';
    }
    return result;
}

std::string Polynom::to_string_2() const
{
    std::string result;
    Term current_term;
    std::string sign;
    bool first = true;

    for ( int i = _coeffVector.size()-1; i >= 0; --i )
    {   
        if ( _coeffVector[i] < 0 )
        {
            if ( first )
            {
                sign = "-";
                first = false;
            }
            else 
                sign = " - ";
            
            current_term = -_coeffVector[i];
        }
        else
        {
            if ( first )
            {
                sign = "";
                first = false;
            }
            else 
                sign = " + ";
            
            current_term = _coeffVector[i];
        }

        result += sign 
                  + format_coeff(current_term.coeff, current_term.deg)
                  + format_power(current_term.deg);
    }

    if ( _coeffVector.size()  == 0 )
    {
        result += '0';
    }
    return result;
}

int Polynom::operator()(int x) const
{
    return eval(x);
}

int Polynom::operator[](uint n) const
{
    return coeff(n);
}

Polynom& Polynom::operator=(std::string line)
{
    _assign_new_from_string(line);
    return *this;
}

void Polynom::_assign_new_from_vector(const std::vector<int>& v)
{
    for (uint i = 0; i < v.size(); ++i )
    {
        if ( v[i] != 0 )
        {
            _coeffVector.push_back(Term(v[i], i));
            _degree = i;
        }
    }
}

void Polynom::_assign_new_from_string(const std::string& line)
{
    std::istringstream iss(line);     
    _degree = 0;
    int coeff;
    
    while ( iss >> coeff )
    {
        if ( 0 != coeff )
        {
            _coeffVector.push_back( Term(coeff, _degree) );
        }

        ++_degree;
    }
}

std::ostream& operator<<(std::ostream& out, const Polynom P)
{
    out << P.to_string_2();
    return out;
}

void operator>>(std::istream& is, Polynom& P)
{
    std::string line;
    std::getline(is, line);
    P = line;
    //talán lesz majd return is
}

Polynom operator+(const Polynom& P1, const Polynom& P2)
{
    Polynom P_res = {};
    uint i1 = 0;
    uint i2 = 0;
    
    while ( (i1 < (P1._coeffVector.size())) && (i2 < (P2._coeffVector.size()))) 
    {
        const Term term_P1 = P1._coeffVector[i1];
        const Term term_P2 = P2._coeffVector[i2];

        if (term_P1.deg < term_P2.deg)
        {
            P_res._coeffVector.push_back(term_P1);
            ++i1;
        }
        else if (term_P1.deg == term_P2.deg)
        {
            int val = term_P1.coeff + term_P2.coeff;
            if ( val != 0 )
            {
                P_res._coeffVector.push_back(Term(val, term_P1.deg));
            }
            ++i1;
            ++i2;
        }
        else // term_P2.deg < term_P1.deg
        {
            P_res._coeffVector.push_back(term_P2);
            ++i2;
        }
    
    }

    // if which vector has remaining elements
    while (P1._coeffVector.size() > i1)
    {
        Term current_term = P1._coeffVector[i1];
        P_res._coeffVector.push_back(current_term);
        ++i1;
    }
    while (P2._coeffVector.size() > i2)
    {
        Term current_term = P1._coeffVector[i2];
        P_res._coeffVector.push_back(current_term);
        ++i2;
    } 
    

    return P_res;
}

