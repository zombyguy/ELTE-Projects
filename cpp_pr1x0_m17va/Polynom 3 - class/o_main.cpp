/*
Polnomok beolvasása std::cin-ről az együtthatók felsorolásával történik,
szóközzel elválasztva. Pl:
0 123 41 43
eredménye
43x^3 + 41x^2 + 123x
A polinomosztály () operátorra úgy reagál, mintha polinom függvény lenne,
[] operátorra pedig úgy, mint ha az együtthatók egy vektora volna.
Az összeadás polinomok összeadásának szabályai szerint működik.
*/

#include <iostream>
#include <string>
#include <vector>
#include "o_polynom.h"

int main()
{
    Polynom P_1 = std::vector<int> {1,0,13,2};
    Polynom P_2 = P_1 + 15;
    Polynom P_3 = "2 0 3";
    Polynom P_4;
    std::cin >> P_4;

    std::cout << "P_1(x) == " << P_1 << '\n' << 
                 "P_2(x) == " << P_2 << '\n' <<
                 "P_3(x) == " << P_3 << '\n' <<
                 "P_4(x) == " << P_4 << '\n' <<
                 '\n' <<
                 "P_1 x=6 helyen: " << P_1(6) << '\n' <<
                 "x^3 egyutthatoja P_2-ben: " << P_2[3] << 
                 std::endl;

    return 0;
}