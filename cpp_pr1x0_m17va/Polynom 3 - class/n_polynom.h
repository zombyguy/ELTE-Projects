#ifndef POLYNOM_H
#define POLYNOM_H

#include <iostream>
#include <vector>
#include <string>

class Polynom
{
private:
    std::vector<int> _coeff_vector;
    int _degree;

public:
    Polynom(std::vector<int> v = {0});
    Polynom(int c);

    int coeff(unsigned int n) const;
    int deg() const;

    int eval(int x) const;
    std::string to_string() const;

};


#endif //POLYNOM_H