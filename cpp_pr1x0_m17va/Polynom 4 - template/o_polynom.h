#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>


template <typename T> class Polynom;
template <typename T> std::ostream& operator<<(std::ostream&, const Polynom<T>& P);
//template <typename T> void operator>>(std::istream& is, Polynom<T> P); 
template <typename T> Polynom<T> operator+(const Polynom<T>& P1,const Polynom<T>& P2);
template <typename T> Polynom<T> operator*(const Polynom<T>& P1,const Polynom<T>& P2);

namespace
{
    typedef unsigned int uint;

    template <typename T>
    std::string num_to_string(T num)
    {
        std::stringstream ss;
        ss << num;
        return ss.str();
    }

    template <typename T>
    T pow(T base, uint pwr)
    {
        T val = 1;
        for ( uint i = 0; i < pwr; ++i)
        {
            val *= base;
        }
        return val;
    }

    template <typename T>
    std::string format_coeff(T coeff, int pwr)
    {
        if ( (0 != pwr) && (1 == coeff) )
        {
            return "";
        }
        else 
        {
            return num_to_string(coeff);
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


template <typename T>
struct Term
{
public:
    Term(T val = 0, uint d = 0)
    {
        deg = d;
        coeff = val;
    };

    operator T() const { return coeff; };
    Term operator-() const { return Term(-coeff, deg); }
    friend class Polynom<T>;
    friend Polynom<T> operator+<T>(const Polynom<T>& P1, const Polynom<T>& P2);
    friend Polynom<T> operator*<T>(const Polynom<T>& P1, const Polynom<T>& P2);

    uint deg;
    T coeff;

};

template <typename T>
class Polynom
{
public:
    Polynom(const std::vector<T>& v = {0});
    //Polynom(const std::map<uint, T>& m);
    Polynom(T c);
    //Polynom(const char * line); 

    T coeff(uint n) const;
    uint deg() const;

    T eval(T x) const;
    std::string to_string() const;

    T operator()(T x) const;
    T operator[](uint n) const;
    Polynom& operator=(const std::string& line);
    Polynom operator-() const;

    friend Polynom operator+<T>(const Polynom& P1, const Polynom& P2);
    friend Polynom operator*<T>(const Polynom& P1, const Polynom& P2);

private:
    std::vector<Term<T>> _coeffVector;
    uint _degree;

    void _assign_new_from_vector(const std::vector<T>& v);
    void _assign_new_from_map(const std::map<uint, T>& m);
    //void _assign_new_from_string(const std::string& line); 
};

template <typename T>
Polynom<T>::Polynom(const std::vector<T>& v)
{
    _assign_new_from_vector(v);
}

/*template <typename T>
Polynom<T>::Polynom(const std::map<uint, T>& m)
{
    _assign_new_from_map(m);
}*/

template <typename T>
Polynom<T>::Polynom(T c)
{
    _coeffVector.push_back(Term<T>(c, 0));
    _degree = 0;
};

/*template <typename T>
Polynom<T>::Polynom(const char * line)
{
    _assign_new_from_string(line);
}*/

template <typename T>
T Polynom<T>::coeff(uint n) const
{
    //binary search megfelelőbb lenne nagy polinomok miatt eshetősége miatt
    for ( Term<T> term : _coeffVector )
    {
        if ( n == term.deg )
        {
            return term.coeff;
        } 
    }
    return 0;
}

template <typename T>
uint Polynom<T>::deg() const
{
    return _degree;
}

template <typename T>
T Polynom<T>::eval(T x) const
{
    T p_val = 0;
    if (0 == _coeffVector.size())
        return p_val;
    if (1 == _coeffVector.size())
    {
        const Term<T>& current_term = _coeffVector[0];
        p_val = current_term.coeff * pow(x,current_term.deg);
        return p_val;
    } 

    for (uint i = _coeffVector.size()-1; i >= 1; --i)
    {
        const Term<T>& current_term = _coeffVector[i];
        const Term<T>& prev_term = _coeffVector[i-1];

        p_val += current_term.coeff;
        p_val *= pow(x, current_term.deg-prev_term.deg);
    }
    const Term<T>& current_term = _coeffVector[0];
    p_val += current_term.coeff;
    p_val *= pow(x, current_term.deg);
    return p_val;
}

template <typename T>
std::string Polynom<T>::to_string() const
{
    std::string result;
    Term<T> current_term;
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

template <typename T>
T Polynom<T>::operator()(T x) const
{
    return eval(x);
}

template <typename T>
T Polynom<T>::operator[](uint n) const
{
    return coeff(n);
}

template <typename T>
Polynom<T>& Polynom<T>::operator=(const std::string& line)
{
    //_assign_new_from_string(line);
    return *this;
}

template <typename T>
Polynom<T> Polynom<T>::operator-() const
{
    Polynom<T> result;
    for ( uint i = 0; i < _coeffVector.size(); ++i)
    {
        const Term<T>& coeff = _coeffVector[i];
        result._coeffVector.push_back(-coeff);
    }
    result._degree = _degree;
    return result;
}

template <typename T>
void Polynom<T>::_assign_new_from_vector(const std::vector<T>& v)
{
    _degree = 0;
    for (uint i = 0; i < v.size(); ++i )
    {
        if ( v[i] != 0 )
        {
            _coeffVector.push_back(Term<T>(v[i], i));
            _degree = i;
        }
    }
}

template <typename T>
void Polynom<T>::_assign_new_from_map(const std::map<uint, T>& m)
{
    _degree = 0;
    auto it = m.cbegin();
    while ( it != m.cend() )
    {
        if (it->second != 0)
        {
            _coeffVector.push_back( Term<T>( it->second, it->first ) );
            _degree = it->first;
        }
        ++it;
    }
}

/*
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
*/

template <typename T>
std::ostream& operator<<(std::ostream& out, const Polynom<T>& P)
{
    out << P.to_string();
    return out;
}

/*template <typename T>
void operator>>(std::istream& is, Polynom<T>& P)
{
    std::string line;
    std::getline(is, line);
    P = line;
    //talán lesz majd return is
}*/

template <typename T>
Polynom<T> operator+(const Polynom<T>& P1, const Polynom<T>& P2)
{
    Polynom<T> P_res = {};
    uint i1 = 0;
    uint i2 = 0;
    
    while ( (i1 < (P1._coeffVector.size())) && (i2 < (P2._coeffVector.size()))) 
    {
        const Term<T> term_P1 = P1._coeffVector[i1];
        const Term<T> term_P2 = P2._coeffVector[i2];

        if (term_P1.deg < term_P2.deg)
        {
            P_res._coeffVector.push_back(term_P1);
            P_res._degree = term_P1.deg;
            ++i1;
        }
        else if (term_P1.deg == term_P2.deg)
        {
            T val = term_P1.coeff + term_P2.coeff;
            if ( val != 0 )
            {
                P_res._coeffVector.push_back(Term<T>(val, term_P1.deg));
                P_res._degree = term_P1.deg;
            }
            ++i1;
            ++i2;
        }
        else // term_P2.deg < term_P1.deg
        {
            P_res._coeffVector.push_back(term_P2);
            P_res._degree = term_P2.deg;
            ++i2;
        }
    
    }

    // if which vector has remaining elements
    while (P1._coeffVector.size() > i1)
    {
        const Term<T>& current_term = P1._coeffVector[i1];
        P_res._coeffVector.push_back(current_term);
        P_res._degree = current_term.deg;
        ++i1;
    }
    while (P2._coeffVector.size() > i2)
    {
        const Term<T>& current_term = P1._coeffVector[i2];
        P_res._coeffVector.push_back(current_term);
        P_res._degree = current_term.deg;
        ++i2;
    } 
    

    return P_res;
}

template <typename T>
Polynom<T> operator-(const Polynom<T>& P1, const Polynom<T>& P2)
{
    return (P1 + (-P2));
}

template <typename T>
Polynom<T> operator*(const Polynom<T>& P1, const Polynom<T>& P2)
{
    std::map<uint, T> coeffMap;
    
    for ( Term<T> term1 : P1._coeffVector ) { for ( Term<T> term2 : P2._coeffVector )
    {
        uint deg = term1.deg + term2.deg;
        T val = term1.coeff * term2.coeff;
        if (coeffMap.count(deg) == 1)
        {
            coeffMap[deg] += val;
        }
        else
        {
            coeffMap.insert( { deg, val } );
        }
    
    }}
    Polynom<T> result;
    result._assign_new_from_map(coeffMap);
    return result;
}

#endif //POLYNOM_H