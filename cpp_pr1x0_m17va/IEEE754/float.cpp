/*
A feladat megoldása során feltételezem, hogy csak a 64 bites lebegőpontos számokkal kell 
foglalkoznom, ahogy a példában látható. Ez paraméteresen van megoldva, így (elméletileg)
komolyabb probléma nélkül változatatható pl. egy hash map segítségével sizeof(d) függvényében

Megjegyzések:
- a globális változó nem egy elegáns meogldás, de még nem tudunk array-eket kezelni
- nagyon pontos számokat nem tud a kód rendesen kezelni pl (0.000000000000000000000002)
  az unsigned long long int méretkorlátai miatt. Nyilván egy ilyen problémára egy 
  BigIng típus bevezetése lenne a legegyszerűbb, de ez nem tűnik túl elegánsnak C++-ban
*/


#include <iostream>
#include <string>

std::string bits();
int find_first_one(unsigned long long int num);
unsigned long long int fract_2_int(int mantissa_len);
std::string interval_2_string(unsigned long long int num, int start, int end); 
unsigned long long int calc_exp_mask(int mantissa_len, int exponent_len);

bool d_sign; // false if positive, true if negative
unsigned long long int d_int;
unsigned long long int d_fract;
unsigned long long int d_denom;

void parse_input();

int main()
{
    
    while ( true )
    {
        parse_input();
        std::string bit_str = bits(); 
        std::cout << " == " << bit_str << '\n';
    }
    return 0;
};

std::string bits()
{
    const int mantissa_len = 52;
    const int exponent_len = 11;

    unsigned long long int result_int = 0;
    std::string result;

// decide leading bit

    if ( d_sign )
    {
        result += '1';
    }
    else
    {
        result += '0';
    }

//calculate mantissa

    int exponent_unadj;
    unsigned long long int exponent_adj;
    unsigned long long int fract_int;

    if ( d_int >= 1 )
    {
        exponent_unadj = find_first_one(d_int) ;
        result_int = d_int << (mantissa_len - exponent_unadj);

        fract_int = fract_2_int(mantissa_len);
        result_int += (fract_int >> exponent_unadj); 
    }
    else
    {
        exponent_unadj = 0;
        while (d_fract < d_denom)
        {
            --exponent_unadj;
            d_fract *= 2;
        }
        d_fract -= d_denom;
        fract_int = fract_2_int(mantissa_len);
        result_int += fract_int;
        

    }

// calculate adjusted exponent

    exponent_adj = exponent_unadj + (1 << (exponent_len-1)) - 1; 
    exponent_adj = (exponent_adj << mantissa_len);

    unsigned long long int exponent_mask = calc_exp_mask(mantissa_len, exponent_len);
    result_int = (result_int & exponent_mask);
    result_int += exponent_adj; 


// create string

    std::string exponent_str = interval_2_string(result_int, mantissa_len + exponent_len - 1, mantissa_len );
    std::string mantissa_str = interval_2_string(result_int, mantissa_len - 1, 0 );
    result += '-' + exponent_str + "-" + mantissa_str;

    return result;

}

int find_first_one(unsigned long long int num)
{
// return the index (from the left) of the first 1 (from the left) in binary representation 

    unsigned long long int mask = 0b1;
    mask = mask << (sizeof(num)*8 - 1 ); 
    int index = sizeof(num)*8-1;

    while  ( ! (mask == (num & mask)) ) 
    {
        --index;
        mask = mask >> 1;
    }

    return index; 
}

unsigned long long int fract_2_int(int mantissa_len)
{
// turns the fractal part into an integer with identical binary representation

    unsigned long long int fract_int = 0;
    unsigned long long int rem = d_fract;

    for (int i = 0; i < mantissa_len; ++i)
    {
        rem *= 2;
        if ( rem >= d_denom )
        {
            unsigned long long int shift = 0b1 ;
            shift = shift << (mantissa_len-i-1);
            fract_int += shift;
            rem -= d_denom; 
        }
    }

    return fract_int;
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

unsigned long long int calc_exp_mask(int mantissa_len, int exponent_len)
{
// calculates the appropriate binary mask for masking out any potential leftovers in the result int's exponent space

    unsigned long long int mask = 0;
    for (int i = 0; i < exponent_len; ++i)
    {
        mask += 0b1;
        mask = mask << 1;
    }

    mask = mask << (mantissa_len -1);
    mask = ~mask;
    return mask;

}

void parse_input()
{
// reads the input double and stores it in integers for more percise calculation

    std::string integer;
    std::string fraction;
    d_denom = 1;
    char ch;

    std::cin >> std::noskipws;
    std::cin >> ch;
    
    if ('-' == ch)
    {
        d_sign = true;
        std::cin >> ch;
    }
    else
    {
        d_sign = false;
    }
    
    while ( ! ('.' == ch ) ) {
        integer += ch;
        std::cin >> ch;
    }

    std::cin >> ch;
    while ( ! ('\n' == ch ) ) {
        fraction += ch;
        d_denom *= 10;
        std::cin >> ch;

    }

    d_int = std::stoll(integer, NULL, 10);
    d_fract = std::stoll(fraction, NULL, 10);
    
}
