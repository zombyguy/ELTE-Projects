#include <iostream>
#include <string>
#include <cstring>

std::string interval_2_string(unsigned long long int num, int start, int end);

int main()
{
    double d; 
    unsigned long long int i;
    void *dp = &d;
    void *ip  = &i;
    std::string sign;
    std::string exponent;
    std::string mantissa;

    std::cin >> d;

    while (! std::cin.eof() )
    {
        memcpy( ip, dp, sizeof(d));

        sign      = interval_2_string( i, 63, 63 );
        exponent  = interval_2_string( i, 62, 52 );
        mantissa  = interval_2_string( i, 51, 0  );

        std::cout << " == "<< sign << '-' << exponent << '-' << mantissa << '\n';
        std::cin >> d;
    }

    return 0;
}

std::string interval_2_string(unsigned long long int num, int start, int end)
{
// turns a range of a number's binary representation into a string
// inclusive on start and end

    std::string out_str;
    unsigned long long int mask;

    for (int i = start; i >= end; --i)
    {
        mask = 0b1;
        mask = mask << i;
        if ( mask == (num & mask))
        {
            out_str += '1';
        }
        else
        {
            out_str += '0';
        }
    }

    return out_str;
}