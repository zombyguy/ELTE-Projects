/*
Funkciók:
- Ha minden együttható 0, akkor 0 íródik ki, ezzel jelölve a nullpolinomot.
- Üres bemenetre nem íródik ki semmi.
- A 0 együtthatójú tagok nem íródnak ki.
- 1 vagy -1 együttható esetén az együttható nem íródik ki, csak x megfelelő hatvánnyal és előjellel (kivéve konstans tag esetén).
- A kimenet tagolva van, azaz a műveleti jelek és a tagok szóközzel el vannak választva.
- A program std::cin-ről olvassa be az együtthatókat, amiket szóközzel elválasztva fogad. eof-ig folyamatosan fogad bemenetet.
  (igaz, hogy a stringstream még számunkra ismeretlen anyagrész, viszont a program így összhangban van az eddigi projektekkel)
- Ha üres a bemenet, akkor nem íródik ki semmi.

Példa: 
bemenet: 
-2 0 5 -3 8
kimenet:

    8x^4 - 3x^3 + 5x^2 - 2

*/

#include <iostream>
#include <vector>
#include <sstream>

std::string to_string(std::vector<int> v);
std::vector<int> read_input();
std::string format_coeff(int coeff, int pwr);
std::string format_power(int pwr);
 
int main()
{
    std::vector<int> v;

    while ( ! std::cin.eof() )
    {
        v = read_input();
        if ( v.size() != 0 )
        {
            std::string s = to_string(v);
            std::cout << '\n' <<'\t' << s << '\n' << '\n';
        }
    }
    
    return 0;
}

std::string to_string(std::vector<int> v)
{
    std::string result;
    unsigned int skipped = 0;
    unsigned int coeff;
    std::string sign;
    bool first = true;

    for ( int i = v.size() - 1; i >= 0 ; --i )
    {   
        if ( v[i] != 0 )
        {
            if ( v[i] < 0 )
            {
                if ( first )
                {
                    sign = "-";
                    first = false;
                }
                else 
                    sign = " - ";
                
                coeff = -v[i];
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
                
                coeff = v[i];
            }

            result += sign + format_coeff(coeff, i)  + format_power(i);
        }
        else
        {
            ++skipped;
        }
    }

    if ( v.size() == skipped )
    {
        result += '0';
    }

    return result;
}

std::vector<int> read_input()
{
    std::string line;
    int d;
    std::vector<int> v;
    
    std::getline(std::cin, line);
    std::istringstream iss(line);     
    
    while ( iss >> d )
    {
        v.push_back(d);
    } 
    return v;
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
