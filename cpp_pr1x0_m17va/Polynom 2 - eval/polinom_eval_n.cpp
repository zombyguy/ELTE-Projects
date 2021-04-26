#include <iostream>
#include <vector>
#include <string>

std::string to_string(std::vector<int> v);
int evaluate( std::vector<int> v, int x);

int main()
{
  // task 1
  std::vector<int> v = { -2, 0, 5, -3, 8};
  std::string s = to_string(v);
  std::cout << s << '\n';
  // task 2
  std::cout << "P(-2) == "  << evaluate( v, -2);
  std::cout << "\tP(0) == " << evaluate( v,  0);
  std::cout << "\tP(42) == " << evaluate( v, 42); 
  return 0;
}

std::string to_string(std::vector<int> v)
{
    std::string result;
    unsigned int skipped = 0;
    bool first = true;

    for ( int i = v.size() - 1; i >= 0 ; --i )
    {   
        if ( v[i] != 0 )
        {
            if ( v[i] < 0 )
            {
                result += std::to_string(v[i]);
            }
            else
            {
                if ( ! first )
                    result += "+";
                
                result += std::to_string(v[i]);
            }

            first = false;

            switch (i) 
            {
                case 0: result += ""; break;
                case 1: result += "x"; break;
                default: result += "x^" + std::to_string(i); break;
            }
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

int pow(int base, int pwr)
{
// tudom, hogy a függvény nem lett fent dektalárlva, ez csak azért van
// hogy a példakód tökéletesen ugyanaz maradjon
    int val = 1;
    for ( int i = 0; i < pwr; ++i)
    {
        val *= base;
    }
    return val;
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