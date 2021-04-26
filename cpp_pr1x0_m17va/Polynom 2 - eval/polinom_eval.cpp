/*
Az előző stringstream program módosított verziója. Emiatt üres bemenetre ez sem reagál.
A program a kiírandó értékeket is std::cin-ről olvassa a polinom megadása után. 
Példa: 

bemenet: 
-2 0 5 -3 8
0 4 3 15
kimenet:

P(x) = 8x^4 - 3x^3 + 5x^2 - 2
P(0) = -2
P(4) = 1934
P(3) = 610
P(15) = 395998
*/

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

std::string to_string(std::vector<int> v);
std::vector<int> read_input();
std::string format_coeff(int coeff, int pwr);
std::string format_power(int pwr);
int evaluate(std::vector<int> v, int x);
int pow(int base, int pwr);
 
int main()
{
    std::vector<int> v;
    std::vector<int> values;

    while ( ! std::cin.eof() )
    {
        v = read_input();
        if ( v.size() != 0 )
        {
            values = read_input();
            std::string s = to_string(v);
            std::cout << '\n' << "P(x) = " << s << '\n'; 

            for ( int x : values )
            {
                int p_val = evaluate(v, x);
                std::cout << "P(" << x << ") = " << p_val << '\n';  
            }
            std::cout << '\n';
        }
        /*else
        {
            std::cout << "Empty input!\n\n"; 
        }*/
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

int evaluate(std::vector<int> v, int x)
{
    int p_val = 0;
    for ( unsigned int i = 0; i < v.size(); ++i )
    {
        p_val += v[i] * pow(x,i);
    }
    return p_val;
}

int pow(int base, int pwr)
{
    int val = 1;
    for ( int i = 0; i < pwr; ++i)
    {
        val *= base;
    }
    return val;
}