#include <iostream>
#include <vector>
#include <sstream>

std::string to_string(std::vector<double> v);
std::vector<double> read_input();
std::string format_coeff(double coeff, int pwr);
std::string format_power(int pwr);
 
int main()
{
    std::vector<double> v;

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

std::string to_string(std::vector<double> v)
{
    std::string result;
    unsigned int skipped = 0;
    double coeff;
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

std::vector<double> read_input()
{
    std::string line;
    double d;
    std::vector<double> v;
    
    std::getline(std::cin, line);
    std::istringstream iss(line);     
    
    while ( iss >> d )
    {
        v.push_back(d);
    } 
    return v;
}

std::string format_coeff(double coeff, int pwr)
{
    if ( (0 != pwr) && (1 == coeff) )
    {
        return "";
    }
    else 
    {
        std::ostringstream ss;
        ss << coeff;
        return (ss.str());
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
