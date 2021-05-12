#include <iostream>
#include "o_polynom.h"

int main()
{
    Polynom<double> p1{ {42, 0, 5, 0, 8, 9} };
    Polynom<double> p2{ {3, 14} }; 
   
    int t1 =  0;
    int t2 =  1;
    int t3 =  6;

    auto poly = p1 * p2;  
    std::cout << "p1    = " << p1.to_string() << '\n';
    std::cout << "p2    = " << p2.to_string() << '\n';
    std::cout << "p1*p2 = " << poly.to_string() << '\n';

    std::cout << "\n(p1*p2) foka: " << poly.deg() << '\n';
    std::cout <<   "(-p1) foka:   " << (-p1).deg() << '\n';

    std::cout << "\np1(" << t1 << ") == " << p1(t1);
    std::cout << "\tp1(" << t2 << ") == " << p1(t2);
    std::cout << "\tp1(" << t3 << ") == " << p1(t3);
    std::cout << "\np2(" << t1 << ") == " << p2(t1);
    std::cout << "\tp2(" << t2 << ") == " << p2(t2);
    std::cout << "\tp2(" << t3 << ") == " << p2(t3);
    std::cout << "\n(p1*p2)(" << t1 << ") == " << poly(t1);
    std::cout << "\t(p1*p2)(" << t2 << ") == " << poly(t2);
    std::cout << "\t(p1*p2)(" << t3 << ") == " << poly(t3) 
                                                << '\n';

    return 0;
}