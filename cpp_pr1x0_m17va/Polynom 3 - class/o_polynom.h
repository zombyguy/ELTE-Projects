#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <vector>
#include <string>

namespace
{
    typedef unsigned int uint;
}

class Polynom;
std::ostream& operator<<(std::ostream&, const Polynom P);
void operator>>(std::istream& is, Polynom& P); 
Polynom operator+(const Polynom& P1,const Polynom& P2);

class Term
{
public:
    Term(int val = 0, uint d = 0)
    {
        deg = d;
        coeff = val;
    };

    operator int() const { return coeff; };

    friend class Polynom;
    friend Polynom operator+(const Polynom& P1, const Polynom& P2);

private:

    uint deg;
    int coeff;

};

class Polynom
{
public:
    Polynom(const std::vector<int>& v = {0});
    Polynom(int c);
    Polynom(const char * line); 

    int coeff(uint n) const;
    int deg() const;

    int eval_old(int x) const;
    int eval(int x) const; 
    std::string to_string() const;

    int operator()(int x) const;
    int operator[](uint n) const;
    Polynom& operator=(std::string line);

    friend Polynom operator+(const Polynom& P1, const Polynom& P2);

private:
    std::vector<Term> _coeffVector;
    uint _degree;

    void _assign_new_from_vector(const std::vector<int>& v);
    void _assign_new_from_string(const std::string& line);
    
};

#endif //POLYNOM_H