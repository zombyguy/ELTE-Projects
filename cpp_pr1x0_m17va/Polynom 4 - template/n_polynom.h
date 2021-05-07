#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

typedef unsigned int uint;

template <typename T> class Polynom;
template <typename T> Polynom<T> operator+(const Polynom<T>& p1, const Polynom<T>& p2);

namespace
{
    template <typename T>
    std::string num_to_string(T num)
    {
        std::stringstream ss;
        ss << num;
        return ss.str();
    }
}

template <typename T>
class Polynom
{
private:
    std::vector<T> _coeff_vector;
    unsigned int _degree;

public:
    Polynom(std::vector<T> v = {0});

    T coeff(unsigned int n) const;
    unsigned int deg() const;

    T eval(T x) const;
    std::string to_string() const;

    friend Polynom operator+<T>(const Polynom& p1, const Polynom& p2);

    T operator()(T x) {return eval(x);}
};

template <typename T>
Polynom<T>::Polynom(std::vector<T> v)
{
    _coeff_vector = v;
    _degree = v.size() - 1;
}

/* Megjegyzés:
A függvény feltételezi, hogy a hely, ahol ki akarjuk számolni a függvényértéket, az 
azonos típusú a polinom együtthatóival. Ez pontatlanságkat okozhat, ha mondjuk egy int
polinom értékét egy double helyen próbáljuk meghatározni.
Azért döntöttem emellet a megoldás mellet, mivel nem igazán találtam c++-ban olyan
megoldást, amivel osztályok közötti hierarchiát lehetne definiálni, illetve 
ellenőrizni.  
*/
template <typename T>
T Polynom<T>::eval(T x) const
{
    T p_val = 0;
    for (int i = _degree; i >= 0; --i)
    {
        p_val *= x;
        p_val += _coeff_vector[i];
    }
    return p_val;
    /*T p_val = 0;
    for ( unsigned int i = 0; i < _coeff_vector.size(); ++i )
    {
        p_val += _coeff_vector[i] * pow(x,i);
    }
    return p_val;
    */
}

/* Megjegyzás:
Az std::to_string() függvény sajnos csak int és float számadatokra, illetve ezek
származékaira van definiálva, így komplex számosztály esetén itt a program 
hibát adna. Komplexekre ugyanígy nem működne az elsőjel meghatározása relációval,
mivel matematikailag ez nincs értelmezve rajtuk.
*/
template <typename T>
std::string Polynom<T>::to_string() const
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
                result += num_to_string(_coeff_vector[i]);
            }
            else
            {
                if ( ! first )
                    result += "+";
                
                result += num_to_string(_coeff_vector[i]);
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

template <typename T>
unsigned int Polynom<T>::deg() const
{
    return _degree;
}

template <typename T>
T Polynom<T>::coeff(unsigned int n) const 
{
    if (_coeff_vector.size() > n)
        return _coeff_vector[n];
    return 0;
}

template <typename T>
Polynom<T> operator+(const Polynom<T>& p1, const Polynom<T>& p2)
{
    if (p1.deg() >= p2.deg())
    {
        std::vector<T> p_vec = p1._coeff_vector;
        for (uint i = 0; i<p2._coeff_vector.size(); i++)
        {
            p_vec[i] += p2._coeff_vector[i];
        }
        while ((p_vec.back() == 0) && (p_vec.size() != 1))
        {
            p_vec.pop_back();
        }
        return Polynom<T>{p_vec};
    }
    else
    {
        return (p2 + p1);
    }
}


#endif //POLYNOM_H